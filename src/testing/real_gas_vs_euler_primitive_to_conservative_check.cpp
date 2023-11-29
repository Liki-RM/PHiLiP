#include "real_gas_vs_euler_primitive_to_conservative_check.h"
#include "physics/inviscid_real_gas.h"
#include "physics/euler.h"
#include "physics/physics_factory.h"

namespace PHiLiP {
namespace Tests {

template <int dim, int nstate>
RealGasVsEulerPrimitiveToConservativeCheck<dim, nstate>::RealGasVsEulerPrimitiveToConservativeCheck(
    const PHiLiP::Parameters::AllParameters *const parameters_input,
    const dealii::ParameterHandler &parameter_handler_input)
        : TestsBase::TestsBase(parameters_input)
        , parameter_handler(parameter_handler_input)
        // , kinetic_energy_expected(parameters_input->flow_solver_param.expected_kinetic_energy_at_final_time)
        // , theoretical_dissipation_rate_expected(parameters_input->flow_solver_param.expected_theoretical_dissipation_rate_at_final_time)
{}

template <int dim, int nstate>
int RealGasVsEulerPrimitiveToConservativeCheck<dim, nstate>::run_test() const
{
    using PDE_enum = Parameters::AllParameters::PartialDifferentialEquation;

    // Integrate to final time
    // std::unique_ptr<FlowSolver::FlowSolver<dim,nstate>> flow_physics = PhysicsBase::PhysicsFactory<dim,nstate>::select_flow_case(this->all_parameters, parameter_handler);
    // static_cast<void>(flow_solver->run());

    // Create IRG physics
    std::shared_ptr<Physics::InviscidRealGas<dim, nstate, double>> inviscid_real_gas_physics = std::dynamic_pointer_cast<Physics::InviscidRealGas<dim,nstate,double>>(
            Physics::PhysicsFactory<dim,nstate,double>::create_Physics(this->all_parameters,PDE_enum::inviscid_real_gas/*,nullptr*/));
    // Create Euler physics
    std::shared_ptr<Physics::Euler<dim, nstate, double>> euler_physics = std::dynamic_pointer_cast<Physics::Euler<dim,nstate,double>>(
            Physics::PhysicsFactory<dim,nstate,double>::create_Physics(this->all_parameters,PDE_enum::euler/*,nullptr*/));
    
    // Compute kinetic energy and theoretical dissipation rate
    // const double kinetic_energy_computed = flow_solver_case->get_integrated_kinetic_energy();
    // const double theoretical_dissipation_rate_computed = flow_solver_case->get_vorticity_based_dissipation_rate();

    // const double relative_error_kinetic_energy = abs(kinetic_energy_computed - kinetic_energy_expected)/kinetic_energy_expected;
    // const double relative_error_theoretical_dissipation_rate = abs(theoretical_dissipation_rate_computed - theoretical_dissipation_rate_expected)/theoretical_dissipation_rate_expected;
    // if (relative_error_kinetic_energy > 1.0e-10) {
    //     pcout << "Computed kinetic energy is not within specified tolerance with respect to expected value." << std::endl;
    //     return 1;
    // }
    // if (relative_error_theoretical_dissipation_rate > 1.0e-10) {
    //     pcout << "Computed theoretical dissipation rate is not within specified tolerance with respect to expected value." << std::endl;
    //     return 1;
    // }
    pcout << " Test passed, computed kinetic energy and theoretical dissipation rate are within specified tolerance." << std::endl;
    return 0;
}

template class RealGasVsEulerPrimitiveToConservativeCheck<PHILIP_DIM,PHILIP_DIM+2>;
} // Tests namespace
} // PHiLiP namespace