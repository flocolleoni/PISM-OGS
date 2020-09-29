// Copyright (C) 2004-2020 Jed Brown, Ed Bueler and Constantine Khroulev
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

#ifndef __iceModel_hh
#define __iceModel_hh

//! \file IceModel.hh Definition of class IceModel.
/*! \file IceModel.hh
  IceModel is a big class which is an ice flow model.  It contains all parts that
  are not well-defined, separated components.  Such components are better places
  to put sub-models that have a clear, general interface to the rest of an ice
  sheet model.

  IceModel has pointers to well-defined components, when they exist.

  IceModel generally interprets user options, and initializes components based on
  such options.  It manages the initialization sequences (%e.g. a restart from a
  file containing a complete model state, versus bootstrapping).
*/

#include <map>
#include <set>
#include <string>
#include <vector>
#include <memory>

// IceModel owns a bunch of fields, so we have to include this.
#include "pism/util/iceModelVec.hh"
#include "pism/util/IceModelVec2CellType.hh"
#include "pism/util/ConfigInterface.hh"
#include "pism/util/Context.hh"
#include "pism/util/Logger.hh"
#include "pism/util/Time.hh"
#include "pism/util/Diagnostic.hh"
#include "pism/util/MaxTimestep.hh"
#include "pism/geometry/Geometry.hh"
#include "pism/geometry/GeometryEvolution.hh"
#include "pism/stressbalance/StressBalance.hh"
#include "pism/basalstrength/YieldStress.hh"

namespace pism {

namespace ocean {
class OceanModel;
namespace sea_level {
class SeaLevel;
}
}

namespace surface {
class SurfaceModel;
}

namespace hydrology {
class Hydrology;
}

namespace calving {
class EigenCalving;
class vonMisesCalving;
class FloatKill;
class HayhurstCalving;
class CalvingAtThickness;
class IcebergRemover;
}

class FractureDensity;

namespace energy {
class BedThermalUnit;
class Inputs;
class EnergyModelStats;
class EnergyModel;
}

namespace frontalmelt {
  class FrontalMelt;
}

namespace bed {
class BedDef;
}

class IceGrid;
class AgeModel;
class IceModelVec2CellType;
class IceModelVec2T;
class Component;
class FrontRetreat;
class PrescribedRetreat;

//! The base class for PISM. Contains all essential variables, parameters, and flags for modelling
//! an ice sheet.
class IceModel {
public:
  IceModel(IceGrid::Ptr g, Context::Ptr context);

  // the destructor must be virtual merely because some members are virtual
  virtual ~IceModel();

  IceGrid::Ptr grid() const;
  Context::Ptr ctx() const;

  void init();

  /** Run PISM in the "standalone" mode. */
  virtual void run();

  /** Advance the current PISM run to a specific time */
  virtual void run_to(double time);

  virtual void save_results();

  void list_diagnostics() const;
  void list_diagnostics_json() const;
  std::map<std::string, std::vector<VariableMetadata>> describe_diagnostics() const;
  std::map<std::string, std::vector<VariableMetadata>> describe_ts_diagnostics() const;

  const IceModelVec2S &calving() const;
  const IceModelVec2S &frontal_melt() const;
  const IceModelVec2S &forced_retreat() const;

  double ice_volume_temperate(double thickness_threshold) const;
  double ice_volume_cold(double thickness_threshold) const;
  double ice_area_temperate(double thickness_threshold) const;
  double ice_area_cold(double thickness_threshold) const;

  const stressbalance::StressBalance* stress_balance() const;
  const ocean::OceanModel* ocean_model() const;
  const frontalmelt::FrontalMelt* frontalmelt_model() const;
  const bed::BedDef* bed_model() const;
  const energy::BedThermalUnit* bedrock_thermal_model() const;
  const energy::EnergyModel* energy_balance_model() const;

  const Geometry& geometry() const;
  const GeometryEvolution& geometry_evolution() const;

  double dt() const;

protected:
  virtual void allocate_submodels();
  virtual void allocate_stressbalance();
  virtual void allocate_age_model();
  virtual void allocate_bed_deformation();
  virtual void allocate_bedrock_thermal_unit();
  virtual void allocate_energy_model();
  virtual void allocate_subglacial_hydrology();
  virtual void allocate_basal_yield_stress();
  virtual void allocate_couplers();
  virtual void allocate_geometry_evolution();
  virtual void allocate_iceberg_remover();

  virtual stressbalance::Inputs stress_balance_inputs();

  virtual energy::Inputs energy_model_inputs();

  virtual YieldStressInputs yield_stress_inputs();

  virtual void time_setup();
  virtual void model_state_setup();
  virtual void misc_setup();
  virtual void init_diagnostics();
  virtual void init_calving();
  virtual void init_frontal_melt();
  virtual void init_front_retreat();
  virtual void prune_diagnostics();
  virtual void update_diagnostics(double dt);
  virtual void reset_diagnostics();

  virtual void step(bool do_mass_continuity, bool do_skip);
  virtual void pre_step_hook();
  virtual void post_step_hook();

  void reset_counters();

  // see iMbootstrap.cc
  virtual void bootstrap_2d(const File &input_file);

  // see iMoptions.cc
  virtual void process_options();
  virtual std::set<std::string> output_variables(const std::string &keyword);

  virtual void compute_lat_lon();

  // see iMIO.cc
  virtual void restart_2d(const File &input_file, unsigned int record);
  virtual void initialize_2d();

  enum OutputKind {INCLUDE_MODEL_STATE = 0, JUST_DIAGNOSTICS};
  virtual void save_variables(const File &file,
                              OutputKind kind,
                              const std::set<std::string> &variables,
                              double time,
                              IO_Type default_diagnostics_type = PISM_FLOAT);

  virtual void define_model_state(const File &file);
  virtual void write_model_state(const File &file);

  enum HistoryTreatment {OVERWRITE_HISTORY = 0, PREPEND_HISTORY};
  enum MappingTreatment {WRITE_MAPPING = 0, SKIP_MAPPING};
  virtual void write_metadata(const File &file, MappingTreatment mapping_flag,
                              HistoryTreatment history_flag);

  virtual void write_mapping(const File &file);
  virtual void write_run_stats(const File &file);


  virtual void define_diagnostics(const File &file,
                                  const std::set<std::string> &variables,
                                  IO_Type default_type);
  virtual void write_diagnostics(const File &file,
                                 const std::set<std::string> &variables);

  //! Computational grid
  const IceGrid::Ptr m_grid;
  //! Configuration flags and parameters
  const Config::Ptr m_config;
  //! Execution context
  const Context::Ptr m_ctx;
  //! Unit system
  const units::System::Ptr m_sys;
  //! Logger
  const Logger::Ptr m_log;
  //! Time manager
  const Time::Ptr m_time;

  //! stores global attributes saved in a PISM output file
  VariableMetadata m_output_global_attributes;

  //! run statistics
  VariableMetadata m_run_stats;

  //! the list of sub-models, for writing model states and obtaining diagnostics
  std::map<std::string,const Component*> m_submodels;

  std::unique_ptr<hydrology::Hydrology> m_subglacial_hydrology;
  std::shared_ptr<YieldStress> m_basal_yield_stress_model;

  std::shared_ptr<IceModelVec2T> m_surface_input_for_hydrology;

  energy::BedThermalUnit *m_btu;
  energy::EnergyModel *m_energy_model;

  std::shared_ptr<AgeModel> m_age_model;

  std::shared_ptr<calving::IcebergRemover>     m_iceberg_remover;
  std::shared_ptr<calving::FloatKill>          m_float_kill_calving;
  std::shared_ptr<calving::CalvingAtThickness> m_thickness_threshold_calving;
  std::shared_ptr<calving::EigenCalving>       m_eigen_calving;
  std::shared_ptr<calving::HayhurstCalving>    m_hayhurst_calving;
  std::shared_ptr<calving::vonMisesCalving>    m_vonmises_calving;
  std::shared_ptr<PrescribedRetreat>           m_prescribed_retreat;

  std::shared_ptr<FrontRetreat> m_front_retreat;

  std::shared_ptr<surface::SurfaceModel>      m_surface;
  std::shared_ptr<ocean::OceanModel>          m_ocean;
  std::shared_ptr<frontalmelt::FrontalMelt>   m_frontal_melt;
  std::shared_ptr<ocean::sea_level::SeaLevel> m_sea_level;

  bed::BedDef *m_beddef;

  // state variables and some diagnostics/internals

  Geometry m_geometry;
  std::unique_ptr<GeometryEvolution> m_geometry_evolution;
  bool m_new_bed_elevation;

  //! ghosted
  IceModelVec2S m_basal_yield_stress;
  //! rate of production of basal meltwater (ice-equivalent); no ghosts
  IceModelVec2S m_basal_melt_rate;
  //! temperature at the top surface of the bedrock thermal layer
  IceModelVec2S m_bedtoptemp;

  std::shared_ptr<FractureDensity> m_fracture;

  //! mask to determine Dirichlet boundary locations
  IceModelVec2Int m_ssa_dirichlet_bc_mask;
  //! Dirichlet boundary velocities
  IceModelVec2V m_ssa_dirichlet_bc_values;

  // parameters
  //! mass continuity time step, s
  double m_dt;
  //! time of last update for enthalpy/temperature
  double t_TempAge;
  //! enthalpy/temperature and age time-steps
  double dt_TempAge;

  unsigned int m_skip_countdown;

  std::string m_adaptive_timestep_reason;

  std::string m_stdout_flags;

  // see iceModel.cc
  virtual void allocate_storage();

  virtual MaxTimestep max_timestep_diffusivity();
  virtual void max_timestep(double &dt_result, unsigned int &skip_counter);
  virtual unsigned int skip_counter(double input_dt, double input_dt_diffusivity);

  // see energy.cc
  virtual void bedrock_thermal_model_step();
  virtual void energy_step();

  virtual void hydrology_step();

  virtual void combine_basal_melt_rate(const Geometry &geometry,
                                       const IceModelVec2S &shelf_base_mass_flux,
                                       const IceModelVec2S &grounded_basal_melt_rate,
                                       IceModelVec2S &result);

  enum ConsistencyFlag {REMOVE_ICEBERGS, DONT_REMOVE_ICEBERGS};
  void enforce_consistency_of_geometry(ConsistencyFlag flag);

  virtual void front_retreat_step();

  void compute_geometry_change(const IceModelVec2S &thickness,
                               const IceModelVec2S &Href,
                               const IceModelVec2S &thickness_old,
                               const IceModelVec2S &Href_old,
                               bool add_values,
                               IceModelVec2S &output);

  // see iMIO.cc
  virtual void regrid();

  // see iMfractures.cc
  virtual void update_fracture_density();

  // see iMreport.cc
  virtual double compute_temperate_base_fraction(double ice_area);
  virtual double compute_original_ice_fraction(double ice_volume);
  virtual void print_summary(bool tempAndAge);
  virtual void print_summary_line(bool printPrototype, bool tempAndAge,
                                  double delta_t,
                                  double volume, double area,
                                  double meltfrac, double max_diffusivity);


  // see iMutil.cc
  virtual int process_signals();
  virtual void prepend_history(const std::string &string);
  virtual void update_run_stats();

  // working space (a convenience)
  static const int m_n_work2d = 3;
  mutable IceModelVec2S m_work2d[m_n_work2d];

  std::shared_ptr<stressbalance::StressBalance> m_stress_balance;

  struct ThicknessChanges {
    ThicknessChanges(IceGrid::ConstPtr grid);

    // calving during the last time step
    IceModelVec2S calving;

    // frontal melt during the last time step
    IceModelVec2S frontal_melt;

    // parameterized retreat
    IceModelVec2S forced_retreat;
  };

  ThicknessChanges m_thickness_change;

  /*!
   * The set of variables that the "state" of IceModel consists of.
   */
  std::set<IceModelVec*> m_model_state;
  //! Requested spatially-variable diagnostics.
  std::map<std::string,Diagnostic::Ptr> m_diagnostics;
  //! Requested scalar diagnostics.
  std::map<std::string,TSDiagnostic::Ptr> m_ts_diagnostics;

  // Set of variables to put in the output file:
  std::set<std::string> m_output_vars;

  // This is related to the snapshot saving feature
  std::string m_snapshots_filename;
  bool m_save_snapshots, m_snapshots_file_is_ready, m_split_snapshots;
  std::vector<double> m_snapshot_times;
  std::set<std::string> m_snapshot_vars;
  unsigned int m_current_snapshot;
  void init_snapshots();
  void write_snapshot();
  MaxTimestep save_max_timestep(double my_t);

  //! file to write scalar time-series to
  std::string m_ts_filename;
  //! requested times for scalar time-series
  std::shared_ptr<std::vector<double>> m_ts_times;
  std::set<std::string> m_ts_vars;
  void init_timeseries();
  void flush_timeseries();
  MaxTimestep ts_max_timestep(double my_t);

  // spatially-varying time-series
  bool m_save_extra, m_extra_file_is_ready, m_split_extra;
  std::string m_extra_filename;
  std::vector<double> m_extra_times;
  unsigned int m_next_extra;
  double m_last_extra;
  std::set<std::string> m_extra_vars;
  TimeBoundsMetadata m_extra_bounds;
  std::unique_ptr<File> m_extra_file;
  void init_extras();
  void write_extras();
  MaxTimestep extras_max_timestep(double my_t);

  // automatic backups
  std::string m_backup_filename;
  double m_last_backup_time;
  std::set<std::string> m_backup_vars;
  void init_backups();
  void write_backup();

  // last time at which PISM hit a multiple of X years, see the configuration parameter
  // time_stepping.hit_multiples
  double m_timestep_hit_multiples_last_time;

  // diagnostic viewers; see iMviewers.cc
  virtual void update_viewers();
  virtual void view_field(const IceModelVec *field);
  std::map<std::string,petsc::Viewer::Ptr> m_viewers;

private:
  TimeseriesMetadata m_timestamp;
  double m_start_time;    // this is used in the wall-clock-time backup code
};

MaxTimestep reporting_max_timestep(const std::vector<double> &times, double t,
                                   const std::string &description);

void check_minimum_ice_thickness(const IceModelVec2S &ice_thickness);
bool check_maximum_ice_thickness(const IceModelVec2S &ice_thickness);

void bedrock_surface_temperature(const IceModelVec2S &sea_level,
                                 const IceModelVec2CellType &cell_type,
                                 const IceModelVec2S &bed_topography,
                                 const IceModelVec2S &ice_thickness,
                                 const IceModelVec2S &basal_enthalpy,
                                 const IceModelVec2S &ice_surface_temperature,
                                 IceModelVec2S &result);

} // end of namespace pism

#endif /* __iceModel_hh */
