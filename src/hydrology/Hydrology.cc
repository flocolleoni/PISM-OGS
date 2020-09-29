// Copyright (C) 2012-2020 PISM Authors
//
// This file is part of PISM.
//
// PISM is free software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation; either version 3 of the License, or (at your option) any later
// version.
//
// PISM is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License
// along with PISM; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#include "Hydrology.hh"
#include "pism/util/Mask.hh"
#include "pism/util/Vars.hh"
#include "pism/util/error_handling.hh"
#include "pism/util/iceModelVec2T.hh"
#include "pism/util/io/File.hh"
#include "pism/util/pism_options.hh"
#include "pism/util/pism_utilities.hh"
#include "pism/util/IceModelVec2CellType.hh"
#include "pism/geometry/Geometry.hh"

namespace pism {
namespace hydrology {

namespace diagnostics {

class TendencyOfWaterMass : public DiagAverageRate<Hydrology>
{
public:
  TendencyOfWaterMass(const Hydrology *m)
    : DiagAverageRate<Hydrology>(m, "tendency_of_subglacial_water_mass", TOTAL_CHANGE) {

    m_vars = {SpatialVariableMetadata(m_sys, "tendency_of_subglacial_water_mass")};
    m_accumulator.metadata().set_string("units", "kg");

    set_attrs("rate of change of the total mass of subglacial water", "",
              "kg second-1", "Gt year-1", 0);
    m_vars[0].set_string("cell_methods", "time: mean");

    m_vars[0].set_number("_FillValue", to_internal(m_fill_value));
    m_vars[0].set_string("comment", "positive flux corresponds to water gain");
  }

protected:
  const IceModelVec2S& model_input() {
    return model->mass_change();
  }
};

/*! @brief Report water input rate from the ice surface into the subglacial water system.
 */
class TotalInputRate : public DiagAverageRate<Hydrology>
{
public:
  TotalInputRate(const Hydrology *m)
    : DiagAverageRate<Hydrology>(m, "subglacial_water_input_rate_from_surface", RATE) {

    m_vars = {SpatialVariableMetadata(m_sys, "subglacial_water_input_rate_from_surface")};
    m_accumulator.metadata().set_string("units", "m");

    set_attrs("water input rate from the ice surface into the subglacial water system",
              "", "m second-1", "m year-1", 0);
    m_vars[0].set_string("cell_methods", "time: mean");

    m_vars[0].set_number("_FillValue", to_internal(m_fill_value));
    m_vars[0].set_string("comment", "positive flux corresponds to water gain");
  }

protected:
  const IceModelVec2S& model_input() {
    return model->surface_input_rate();
  }
};

/*! @brief Report water flux due to input (basal melt and drainage from the surface). */
class WaterInputFlux : public DiagAverageRate<Hydrology>
{
public:
  WaterInputFlux(const Hydrology *m)
    : DiagAverageRate<Hydrology>(m, "tendency_of_subglacial_water_mass_due_to_input",
                                 TOTAL_CHANGE) {

    m_vars = {SpatialVariableMetadata(m_sys,
                                      "tendency_of_subglacial_water_mass_due_to_input")};
    m_accumulator.metadata().set_string("units", "kg");

    set_attrs("subglacial water flux due to input", "",
              "kg second-1", "Gt year-1", 0);
    m_vars[0].set_string("cell_methods", "time: mean");

    m_vars[0].set_number("_FillValue", to_internal(m_fill_value));
    m_vars[0].set_string("comment", "positive flux corresponds to water gain");
  }

protected:
  const IceModelVec2S& model_input() {
    return model->mass_change_due_to_input();
  }
};

/*! @brief Report advective subglacial water flux. */
class SubglacialWaterFlux : public DiagAverageRate<Hydrology>
{
public:
  SubglacialWaterFlux(const Hydrology *m)
    : DiagAverageRate<Hydrology>(m, "subglacial_water_flux", RATE),
      m_flux_magnitude(m_grid, "flux_magnitude", WITHOUT_GHOSTS){

    m_vars = {SpatialVariableMetadata(m_sys, "subglacial_water_flux")};
    m_accumulator.metadata().set_string("units", "m2");

    set_attrs("magnitude of the subglacial water flux", "",
              "m2 second-1", "m2 year-1", 0);
    m_vars[0].set_string("cell_methods", "time: mean");

    m_vars[0].set_number("_FillValue", to_internal(m_fill_value));

    m_flux_magnitude.set_attrs("internal", "magnitude of the subglacial water flux",
                               "m2 s-1", "m2 s-1", "", 0);
  }

protected:
  void update_impl(double dt) {
    m_flux_magnitude.set_to_magnitude(model->flux());

    m_accumulator.add(dt, m_flux_magnitude);

    m_interval_length += dt;
  }

  IceModelVec2S m_flux_magnitude;
};


/*! @brief Report water flux at the grounded margin. */
class GroundedMarginFlux : public DiagAverageRate<Hydrology>
{
public:
  GroundedMarginFlux(const Hydrology *m)
    : DiagAverageRate<Hydrology>(m, "tendency_of_subglacial_water_mass_at_grounded_margins",
                                 TOTAL_CHANGE) {

    m_vars = {SpatialVariableMetadata(m_sys,
                                      "tendency_of_subglacial_water_mass_at_grounded_margins")};
    m_accumulator.metadata().set_string("units", "kg");

    set_attrs("subglacial water flux at grounded ice margins", "",
              "kg second-1", "Gt year-1", 0);
    m_vars[0].set_string("cell_methods", "time: mean");

    m_vars[0].set_number("_FillValue", to_internal(m_fill_value));
    m_vars[0].set_string("comment", "positive flux corresponds to water gain");
  }

protected:
  const IceModelVec2S& model_input() {
    return model->mass_change_at_grounded_margin();
  }
};

/*! @brief Report subglacial water flux at grounding lines. */
class GroundingLineFlux : public DiagAverageRate<Hydrology>
{
public:
  GroundingLineFlux(const Hydrology *m)
    : DiagAverageRate<Hydrology>(m, "tendency_of_subglacial_water_mass_at_grounding_line", TOTAL_CHANGE) {

    m_vars = {SpatialVariableMetadata(m_sys, "tendency_of_subglacial_water_mass_at_grounding_line")};
    m_accumulator.metadata().set_string("units", "kg");

    set_attrs("subglacial water flux at grounding lines", "",
              "kg second-1", "Gt year-1", 0);
    m_vars[0].set_string("cell_methods", "time: mean");

    m_vars[0].set_number("_FillValue", to_internal(m_fill_value));
    m_vars[0].set_string("comment", "positive flux corresponds to water gain");
  }

protected:
  const IceModelVec2S& model_input() {
    return model->mass_change_at_grounding_line();
  }
};

/*! @brief Report subglacial water conservation error flux (mass added to preserve non-negativity). */
class ConservationErrorFlux : public DiagAverageRate<Hydrology>
{
public:
  ConservationErrorFlux(const Hydrology *m)
    : DiagAverageRate<Hydrology>(m, "tendency_of_subglacial_water_mass_due_to_conservation_error",
                                 TOTAL_CHANGE) {

    m_vars = {SpatialVariableMetadata(m_sys,
                                      "tendency_of_subglacial_water_mass_due_to_conservation_error")};
    m_accumulator.metadata().set_string("units", "kg");

    set_attrs("subglacial water flux due to conservation error (mass added to preserve non-negativity)", "",
              "kg second-1", "Gt year-1", 0);
    m_vars[0].set_string("cell_methods", "time: mean");

    m_vars[0].set_number("_FillValue", to_internal(m_fill_value));
    m_vars[0].set_string("comment", "positive flux corresponds to water gain");
  }

protected:
  const IceModelVec2S& model_input() {
    return model->mass_change_due_to_conservation_error();
  }
};

/*! @brief Report subglacial water flux at domain boundary (in regional model configurations). */
class DomainBoundaryFlux : public DiagAverageRate<Hydrology>
{
public:
  DomainBoundaryFlux(const Hydrology *m)
    : DiagAverageRate<Hydrology>(m, "tendency_of_subglacial_water_mass_at_domain_boundary", TOTAL_CHANGE) {

    m_vars = {SpatialVariableMetadata(m_sys, "tendency_of_subglacial_water_mass_at_domain_boundary")};
    m_accumulator.metadata().set_string("units", "kg");

    set_attrs("subglacial water flux at domain boundary (in regional model configurations)", "",
              "kg second-1", "Gt year-1", 0);
    m_vars[0].set_string("cell_methods", "time: mean");

    m_vars[0].set_number("_FillValue", to_internal(m_fill_value));
    m_vars[0].set_string("comment", "positive flux corresponds to water gain");
  }

protected:
  const IceModelVec2S& model_input() {
    return model->mass_change_at_domain_boundary();
  }
};

/*! @brief Report water flux at the grounded margin. */
class TendencyOfWaterMassDueToFlow : public DiagAverageRate<Hydrology>
{
public:
  TendencyOfWaterMassDueToFlow(const Hydrology *m)
    : DiagAverageRate<Hydrology>(m, "tendency_of_subglacial_water_mass_due_to_flow",
                                 TOTAL_CHANGE) {

    m_vars = {SpatialVariableMetadata(m_sys,
                                      "tendency_of_subglacial_water_mass_due_to_flow")};
    m_accumulator.metadata().set_string("units", "kg");

    set_attrs("rate of change subglacial water mass due to lateral flow", "",
              "kg second-1", "Gt year-1", 0);
    m_vars[0].set_string("cell_methods", "time: mean");

    m_vars[0].set_number("_FillValue", to_internal(m_fill_value));
    m_vars[0].set_string("comment", "positive flux corresponds to water gain");
  }

protected:
  const IceModelVec2S& model_input() {
    return model->mass_change_due_to_lateral_flow();
  }
};

} // end of namespace diagnostics

Inputs::Inputs() {
  geometry           = nullptr;
  surface_input_rate = nullptr;
  basal_melt_rate    = nullptr;
  ice_sliding_speed  = nullptr;
  no_model_mask      = nullptr;
}

Hydrology::Hydrology(IceGrid::ConstPtr g)
  : Component(g),
    m_Q(m_grid, "water_flux", WITHOUT_GHOSTS),
    m_Wtill(m_grid, "tillwat", WITHOUT_GHOSTS),
    m_W(m_grid, "bwat", WITH_GHOSTS, 1),
    m_Pover(m_grid, "overburden_pressure", WITHOUT_GHOSTS),
    m_surface_input_rate(m_grid, "water_input_rate_from_surface", WITHOUT_GHOSTS),
    m_basal_melt_rate(m_grid, "water_input_rate_due_to_basal_melt", WITHOUT_GHOSTS),
    m_flow_change_incremental(m_grid, "water_thickness_change_due_to_flow", WITHOUT_GHOSTS),
    m_conservation_error_change(m_grid, "conservation_error_change", WITHOUT_GHOSTS),
    m_grounded_margin_change(m_grid, "grounded_margin_change", WITHOUT_GHOSTS),
    m_grounding_line_change(m_grid, "grounding_line_change", WITHOUT_GHOSTS),
    m_input_change(m_grid, "water_mass_change_due_to_input", WITHOUT_GHOSTS),
    m_no_model_mask_change(m_grid, "no_model_mask_change", WITHOUT_GHOSTS),
    m_total_change(m_grid, "water_mass_change", WITHOUT_GHOSTS),
    m_flow_change(m_grid, "water_mass_change_due_to_flow", WITHOUT_GHOSTS) {

  m_surface_input_rate.set_attrs("internal",
                                 "hydrology model workspace for water input rate from the ice surface",
                                 "m s-1", "m s-1", "", 0);

  m_basal_melt_rate.set_attrs("internal",
                              "hydrology model workspace for water input rate due to basal melt",
                              "m s-1", "m s-1", "", 0);

  // *all* Hydrology classes have layer of water stored in till as a state variable
  m_Wtill.set_attrs("model_state",
                    "effective thickness of subglacial water stored in till",
                    "m", "m", "", 0);
  m_Wtill.metadata().set_number("valid_min", 0.0);

  m_Pover.set_attrs("internal", "overburden pressure",
                    "Pa", "Pa", "", 0);
  m_Pover.metadata().set_number("valid_min", 0.0);

  // needs ghosts in Routing and Distributed
  m_W.set_attrs("diagnostic",
                "thickness of transportable subglacial water layer",
                "m", "m", "", 0);
  m_W.metadata().set_number("valid_min", 0.0);

  m_Q.set_attrs("diagnostic", "advective subglacial water flux",
                "m2 s-1", "m2 day-1", "", 0);
  m_Q.set(0.0);

  // storage for water conservation reporting quantities
  m_total_change.set_attrs("internal",
                           "total change in water mass over one time step",
                           "kg", "kg", "", 0);

  m_input_change.set_attrs("internal",
                           "change in water mass over one time step due to the input "
                           "(basal melt and surface drainage)",
                           "kg", "kg", "", 0);


  m_flow_change.set_attrs("internal",
                          "change in water mass due to lateral flow (over one time step)",
                          "kg", "kg", "", 0);

  m_grounded_margin_change.set_attrs("diagnostic",
                                     "changes in subglacial water thickness at the grounded margin",
                                     "kg", "kg", "", 0);
  m_grounding_line_change.set_attrs("diagnostic",
                                    "changes in subglacial water thickness at the grounding line",
                                    "kg", "kg", "", 0);

  m_no_model_mask_change.set_attrs("diagnostic",
                                   "changes in subglacial water thickness at the edge of the modeling domain"
                                   " (regional models)",
                                   "kg", "kg", "", 0);

  m_conservation_error_change.set_attrs("diagnostic",
                                        "changes in subglacial water thickness required "
                                        "to preserve non-negativity or "
                                        "keep water thickness within bounds",
                                        "kg", "kg", "", 0);
}

Hydrology::~Hydrology() {
  // empty
}

void Hydrology::restart(const File &input_file, int record) {
  initialization_message();
  this->restart_impl(input_file, record);
}

void Hydrology::bootstrap(const File &input_file,
                          const IceModelVec2S &ice_thickness) {
  initialization_message();
  this->bootstrap_impl(input_file, ice_thickness);
}

void Hydrology::init(const IceModelVec2S &W_till,
                           const IceModelVec2S &W,
                           const IceModelVec2S &P) {
  initialization_message();
  this->init_impl(W_till, W, P);
}

void Hydrology::restart_impl(const File &input_file, int record) {
  m_Wtill.read(input_file, record);

  // whether or not we could initialize from file, we could be asked to regrid from file
  regrid("Hydrology", m_Wtill);
}

void Hydrology::bootstrap_impl(const File &input_file,
                               const IceModelVec2S &ice_thickness) {
  (void) ice_thickness;

  double tillwat_default = m_config->get_number("bootstrapping.defaults.tillwat");
  m_Wtill.regrid(input_file, OPTIONAL, tillwat_default);

  // whether or not we could initialize from file, we could be asked to regrid from file
  regrid("Hydrology", m_Wtill);
}

void Hydrology::init_impl(const IceModelVec2S &W_till,
                                const IceModelVec2S &W,
                                const IceModelVec2S &P) {
  (void) W;
  (void) P;
  m_Wtill.copy_from(W_till);
}

void Hydrology::update(double t, double dt, const Inputs& inputs) {

  // reset water thickness changes
  {
    m_grounded_margin_change.set(0.0);
    m_grounding_line_change.set(0.0);
    m_conservation_error_change.set(0.0);
    m_no_model_mask_change.set(0.0);
    m_flow_change.set(0.0);
    m_input_change.set(0.0);
  }

  compute_overburden_pressure(inputs.geometry->ice_thickness, m_Pover);

  compute_surface_input_rate(inputs.geometry->cell_type,
                             inputs.surface_input_rate,
                             m_surface_input_rate);
  compute_basal_melt_rate(inputs.geometry->cell_type,
                          *inputs.basal_melt_rate,
                          m_basal_melt_rate);

  IceModelVec::AccessList list{&m_W, &m_Wtill, &m_total_change};

  for (Points p(*m_grid); p; p.next()) {
    const int i = p.i(), j = p.j();

    m_total_change(i, j) = m_W(i, j) + m_Wtill(i, j);
  }

  this->update_impl(t, dt, inputs);

  // compute total change in meters
  for (Points p(*m_grid); p; p.next()) {
    const int i = p.i(), j = p.j();
    m_total_change(i, j) = (m_W(i, j) + m_Wtill(i, j)) - m_total_change(i, j);
  }

  // convert from m to kg
  // kg = m * (kg / m^3) * m^2

  double
    water_density = m_config->get_number("constants.fresh_water.density"),
    kg_per_m      = water_density * m_grid->cell_area();

  list.add({&m_flow_change, &m_input_change});
  for (Points p(*m_grid); p; p.next()) {
    const int i = p.i(), j = p.j();
    m_total_change(i, j) *= kg_per_m;
    m_input_change(i, j) *= kg_per_m;
    m_flow_change(i, j)  *= kg_per_m;
  }
}

DiagnosticList Hydrology::diagnostics_impl() const {
  using namespace diagnostics;
  DiagnosticList result = {
    {"bwat",                                                        Diagnostic::wrap(m_W)},
    {"tillwat",                                                     Diagnostic::wrap(m_Wtill)},
    {"subglacial_water_input_rate",                                 Diagnostic::Ptr(new TotalInputRate(this))},
    {"tendency_of_subglacial_water_mass_due_to_input",              Diagnostic::Ptr(new WaterInputFlux(this))},
    {"tendency_of_subglacial_water_mass_due_to_flow",               Diagnostic::Ptr(new TendencyOfWaterMassDueToFlow(this))},
    {"tendency_of_subglacial_water_mass_due_to_conservation_error", Diagnostic::Ptr(new ConservationErrorFlux(this))},
    {"tendency_of_subglacial_water_mass",                           Diagnostic::Ptr(new TendencyOfWaterMass(this))},
    {"tendency_of_subglacial_water_mass_at_grounded_margins",       Diagnostic::Ptr(new GroundedMarginFlux(this))},
    {"tendency_of_subglacial_water_mass_at_grounding_line",         Diagnostic::Ptr(new GroundingLineFlux(this))},
    {"tendency_of_subglacial_water_mass_at_domain_boundary",        Diagnostic::Ptr(new DomainBoundaryFlux(this))},
    {"subglacial_water_flux_mag",                                   Diagnostic::Ptr(new SubglacialWaterFlux(this))},
  };

  return result;
}

void Hydrology::define_model_state_impl(const File &output) const {
  m_Wtill.define(output);
}

void Hydrology::write_model_state_impl(const File &output) const {
  m_Wtill.write(output);
}

//! Update the overburden pressure from ice thickness.
/*!
  Uses the standard hydrostatic (shallow) approximation of overburden pressure,
  \f[ P_0 = \rho_i g H \f]
*/
void Hydrology::compute_overburden_pressure(const IceModelVec2S &ice_thickness,
                                            IceModelVec2S &result) const {
  // FIXME issue #15

  const double
    ice_density      = m_config->get_number("constants.ice.density"),
    standard_gravity = m_config->get_number("constants.standard_gravity");

  IceModelVec::AccessList list{&ice_thickness, &result};

  for (Points p(*m_grid); p; p.next()) {
    const int i = p.i(), j = p.j();

    result(i, j) = ice_density * standard_gravity * ice_thickness(i, j);
  }
}

const IceModelVec2S& Hydrology::overburden_pressure() const {
  return m_Pover;
}

//! Return the effective thickness of the water stored in till.
const IceModelVec2S& Hydrology::till_water_thickness() const {
  return m_Wtill;
}

//! Return the effective thickness of the transportable basal water layer.
const IceModelVec2S& Hydrology::subglacial_water_thickness() const {
  return m_W;
}

/*!
 * Return subglacial water flux (time-average over the time step requested at the time of
 * the update() call).
 */
const IceModelVec2V& Hydrology::flux() const {
  return m_Q;
}

const IceModelVec2S& Hydrology::surface_input_rate() const {
  return m_surface_input_rate;
}

const IceModelVec2S& Hydrology::mass_change_at_grounded_margin() const {
  return m_grounded_margin_change;
}

const IceModelVec2S& Hydrology::mass_change_at_grounding_line() const {
  return m_grounding_line_change;
}

const IceModelVec2S& Hydrology::mass_change_due_to_conservation_error() const {
  return m_conservation_error_change;
}

const IceModelVec2S& Hydrology::mass_change_at_domain_boundary() const {
  return m_no_model_mask_change;
}

const IceModelVec2S& Hydrology::mass_change() const {
  return m_total_change;
}

const IceModelVec2S& Hydrology::mass_change_due_to_input() const {
  return m_input_change;
}

const IceModelVec2S& Hydrology::mass_change_due_to_lateral_flow() const {
  return m_flow_change;
}

/*!
  Checks @f$ 0 \le W \le W^{max} @f$.
*/
void check_bounds(const IceModelVec2S& W, double W_max) {

  std::string name = W.metadata().get_string("long_name");

  IceGrid::ConstPtr grid = W.grid();

  IceModelVec::AccessList list(W);
  ParallelSection loop(grid->com);
  try {
    for (Points p(*grid); p; p.next()) {
      const int i = p.i(), j = p.j();

      if (W(i,j) < 0.0) {
        throw RuntimeError::formatted(PISM_ERROR_LOCATION,
                                      "Hydrology: negative %s of %.6f m at (i, j) = (%d, %d)",
                                      name.c_str(), W(i, j), i, j);
      }

      if (W(i,j) > W_max) {
        throw RuntimeError::formatted(PISM_ERROR_LOCATION,
                                      "Hydrology: %s of %.6f m exceeds the maximum value %.6f at (i, j) = (%d, %d)",
                                      name.c_str(), W(i, j), W_max, i, j);
      }
    }
  } catch (...) {
    loop.failed();
  }
  loop.check();
}


//! Compute the surface water input rate into the basal hydrology layer in the ice-covered
//! region.
/*!
  This method ignores the input rate in the ice-free region.

  @param[in] mask cell type mask
  @param[in] surface_input_rate surface input rate (kg m-2 s-1); set to NULL to ignore
  @param[out] result resulting input rate (water thickness per time)
*/
void Hydrology::compute_surface_input_rate(const IceModelVec2CellType &mask,
                                           const IceModelVec2S *surface_input_rate,
                                           IceModelVec2S &result) {

  if (not surface_input_rate) {
    result.set(0.0);
    return;
  }

  IceModelVec::AccessList list{surface_input_rate, &mask, &result};

  const double
    water_density = m_config->get_number("constants.fresh_water.density");

  for (Points p(*m_grid); p; p.next()) {
    const int i = p.i(), j = p.j();

    if (mask.icy(i, j)) {
      result(i,j) = (*surface_input_rate)(i, j) / water_density;
    } else {
      result(i,j) = 0.0;
    }
  }
}

//! Compute the input rate into the basal hydrology layer in the ice-covered
//! region due to basal melt rate.
/*!
  This method ignores the input in the ice-free region.

  @param[in] mask cell type mask
  @param[in] basal_melt_rate basal melt rate (ice thickness per time)
  @param[out] result resulting input rate (water thickness per time)
*/
void Hydrology::compute_basal_melt_rate(const IceModelVec2CellType &mask,
                                        const IceModelVec2S &basal_melt_rate,
                                        IceModelVec2S &result) {

  IceModelVec::AccessList list{&basal_melt_rate, &mask, &result};

  const double
    ice_density   = m_config->get_number("constants.ice.density"),
    water_density = m_config->get_number("constants.fresh_water.density"),
    C             = ice_density / water_density;

  for (Points p(*m_grid); p; p.next()) {
    const int i = p.i(), j = p.j();

    if (mask.icy(i, j)) {
      result(i,j) = C * basal_melt_rate(i, j);
    } else {
      result(i,j) = 0.0;
    }
  }
}

//! Correct the new water thickness based on boundary requirements.
/*! At ice free locations and ocean locations we require that water thicknesses (i.e. both
  the transportable water thickness \f$W\f$ and the till water thickness \f$W_{till}\f$)
  be zero at the end of each time step. Also we require that any negative water
  thicknesses be set to zero (i.e. we do projection to enforce lower bound).

  This method should be called once for each thickness field which needs to be processed.
  This method alters the field water_thickness in-place.

  @param[in] cell_type cell type mask
  @param[in] no_model_mask (optional) mask of zeros and ones, zero within the modeling
                           domain, one outside
  @param[in] max_thickness maximum allowed water thickness (use a zero or a negative value
                           to disable)
  @param[in,out] water_thickness adjusted water thickness (till storage or the transport system)
  @param[in,out] grounded_margin_change change in water thickness at the grounded margin
  @param[in,out] grounding_line_change change in water thickness at the grounding line
  @param[in,out] conservation_error_change change in water thickness due to mass conservation errors
  @param[in,out] no_model_mask_change change in water thickness outside the modeling domain (regional models)
*/
void Hydrology::enforce_bounds(const IceModelVec2CellType &cell_type,
                               const IceModelVec2Int *no_model_mask,
                               double max_thickness,
                               IceModelVec2S &water_thickness,
                               IceModelVec2S &grounded_margin_change,
                               IceModelVec2S &grounding_line_change,
                               IceModelVec2S &conservation_error_change,
                               IceModelVec2S &no_model_mask_change) {

  bool include_floating = m_config->get_flag("hydrology.routing.include_floating_ice");

  IceModelVec::AccessList list{&water_thickness, &cell_type,
      &grounded_margin_change, &grounding_line_change, &conservation_error_change,
      &no_model_mask_change};

  double
    fresh_water_density = m_config->get_number("constants.fresh_water.density"),
    kg_per_m            = m_grid->cell_area() * fresh_water_density; // kg m-1

  for (Points p(*m_grid); p; p.next()) {
    const int i = p.i(), j = p.j();

    if (water_thickness(i, j) < 0.0) {
      conservation_error_change(i, j) += -water_thickness(i, j) * kg_per_m;
      water_thickness(i, j) = 0.0;
    }

    if (max_thickness > 0.0 and water_thickness(i, j) > max_thickness) {
      double excess = water_thickness(i, j) - max_thickness;

      conservation_error_change(i, j) += -excess * kg_per_m;
      water_thickness(i, j) = max_thickness;
    }

    if (cell_type.ice_free_land(i, j)) {
      grounded_margin_change(i, j) += -water_thickness(i, j) * kg_per_m;
      water_thickness(i, j) = 0.0;
    }

    if ((include_floating and cell_type.ice_free_ocean(i, j)) or
        (not include_floating and cell_type.ocean(i, j))) {
      grounding_line_change(i, j) += -water_thickness(i, j) * kg_per_m;
      water_thickness(i, j) = 0.0;
    }
  }

  if (no_model_mask) {
    const IceModelVec2Int &M = *no_model_mask;

    list.add(M);

    for (Points p(*m_grid); p; p.next()) {
      const int i = p.i(), j = p.j();

      if (M(i, j)) {
        no_model_mask_change(i, j) += -water_thickness(i, j) * kg_per_m;

        water_thickness(i, j) = 0.0;
      }
    }
  }
}

} // end of namespace hydrology
} // end of namespace pism
