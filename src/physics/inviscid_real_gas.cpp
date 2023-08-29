#include <cmath>
#include <vector>

#include "ADTypes.hpp"

#include "physics.h"
#include "euler.h"
#include "inviscid_real_gas.h"

namespace PHiLiP {
namespace Physics {

template <int dim, int nstate, typename real>
InviscidRealGas<dim,nstate,real>::InviscidRealGas ( 
    const Parameters::AllParameters *const                    parameters_input,
    std::shared_ptr< ManufacturedSolutionFunction<dim,real> > manufactured_solution_function,
    const bool                                                has_nonzero_diffusion,
    const bool                                                has_nonzero_physical_source)
    : PhysicsBase<dim,nstate,real>(parameters_input, has_nonzero_diffusion,has_nonzero_physical_source,manufactured_solution_function)
    , mach_inf(parameters_input->euler_param.mach_inf)
    , mach_inf_sqr(mach_inf*mach_inf)
    , two_point_num_flux_type(parameters_input->two_point_num_flux_type)
{
    static_assert(nstate==dim+2, "Physics::InviscidRealGas() should be created with nstate=dim+2"); // TO DO: UPDATE THIS with nspecies
}

// template <int dim, int nstate, typename real>
// std::array<dealii::Tensor<1,dim,real>,nstate> InviscidRealGas<dim,nstate,real>
// ::convective_flux (const std::array<real,nstate> &/*conservative_soln*/) const
// {
//     std::array<dealii::Tensor<1,dim,real>,nstate> conv_flux;

//     for (int flux_dim=0; flux_dim<dim; ++flux_dim) {
//         // Density equation
//         conv_flux[0][flux_dim] = 0.0;
//         // Momentum equation
//         for (int velocity_dim=0; velocity_dim<dim; ++velocity_dim){
//             conv_flux[1+velocity_dim][flux_dim] = 0.0;
//         }
//         conv_flux[1+flux_dim][flux_dim] += 0.0;
//         // Energy equation
//         conv_flux[nstate-1][flux_dim] = 0.0;
//         // TO DO: now loop over nspecies
//     }
//     return conv_flux;
// }

template <int dim, int nstate, typename real>
std::array<real,nstate> InviscidRealGas<dim, nstate, real>
::compute_entropy_variables (
    const std::array<real,nstate> &conservative_soln) const
{
    std::cout<<"Entropy variables for InviscidRealGas hasn't been done yet."<<std::endl;
    std::abort();
    return conservative_soln;
}

template <int dim, int nstate, typename real>
std::array<real,nstate> InviscidRealGas<dim, nstate, real>
::compute_conservative_variables_from_entropy_variables (
    const std::array<real,nstate> &entropy_var) const
{
    std::cout<<"Entropy variables for InviscidRealGas hasn't been done yet."<<std::endl;
    std::abort();
    return entropy_var;
}

template <int dim, int nstate, typename real>
std::array<real,nstate> InviscidRealGas<dim,nstate,real>
::convective_eigenvalues (
    const std::array<real,nstate> &/*conservative_soln*/,
    const dealii::Tensor<1,dim,real> &/*normal*/) const
{
    // TO DO: define this
    std::array<real,nstate> eig;
    eig.fill(0.0);
    return eig;
}

template <int dim, int nstate, typename real>
real InviscidRealGas<dim,nstate,real>
::max_convective_eigenvalue (const std::array<real,nstate> &/*conservative_soln*/) const
{
    // TO DO: define this
    const real max_eig = 0.0;
    return max_eig;
}

template <int dim, int nstate, typename real>
real InviscidRealGas<dim,nstate,real>
::max_viscous_eigenvalue (const std::array<real,nstate> &/*conservative_soln*/) const
{
    // zero because inviscid
    const real max_eig = 0.0;
    return max_eig;
}

template <int dim, int nstate, typename real>
std::array<dealii::Tensor<1,dim,real>,nstate> InviscidRealGas<dim,nstate,real>
::dissipative_flux (
    const std::array<real,nstate> &/*conservative_soln*/,
    const std::array<dealii::Tensor<1,dim,real>,nstate> &/*solution_gradient*/,
    const dealii::types::global_dof_index /*cell_index*/) const
{
     std::array<dealii::Tensor<1,dim,real>,nstate> diss_flux;
    // No dissipative flux (i.e. viscous terms) for InviscidRealGas
    for (int i=0; i<nstate; i++) {
        diss_flux[i] = 0;
    }
    return diss_flux;
}

template <int dim, int nstate, typename real>
std::array<real,nstate> InviscidRealGas<dim,nstate,real>
::source_term (
    const dealii::Point<dim,real> &/*pos*/,
    const std::array<real,nstate> &/*conservative_soln*/,
    const real /*current_time*/,
    const dealii::types::global_dof_index /*cell_index*/) const
{
    // nothing to add here
    std::array<real,nstate> source_term;
    source_term.fill(0.0);
    return source_term;
}

// TO DO: Provide required definition for this
// template <int dim, int nstate, typename real>
// template<typename real2>
// bool InviscidRealGas<dim,nstate,real>::check_positive_quantity(real2 &qty, const std::string qty_name) const {
//     bool qty_is_positive;
//     if (qty < 0.0) {
//         // Refer to base class for non-physical results handling
//         qty = this->template handle_non_physical_result<real2>(qty_name + " is negative.");
//         qty_is_positive = false;
//     } else {
//         qty_is_positive = true;
//     }

//     return qty_is_positive;
// }


template <int dim, int nstate, typename real>
void InviscidRealGas<dim,nstate,real>
::boundary_face_values (
   const int /*boundary_type*/,
   const dealii::Point<dim, real> &/*pos*/,
   const dealii::Tensor<1,dim,real> &/*normal_int*/,
   const std::array<real,nstate> &/*soln_int*/,
   const std::array<dealii::Tensor<1,dim,real>,nstate> &/*soln_grad_int*/,
   std::array<real,nstate> &/*soln_bc*/,
   std::array<dealii::Tensor<1,dim,real>,nstate> &/*soln_grad_bc*/) const
{
    // TO DO: Update this you are using any kind of BC that is not periodic
}

template <int dim, int nstate, typename real>
inline real InviscidRealGas<dim,nstate,real>
:: compute_density ( const std::array<real,nstate> &conservative_soln ) const
{
    const real density = conservative_soln[0];
    return density;
}

template <int dim, int nstate, typename real>
template<typename real2>
inline dealii::Tensor<1,dim,real2> InviscidRealGas<dim,nstate,real>
::compute_velocities ( const std::array<real2,nstate> &conservative_soln ) const
{
    const real2 density = compute_density(conservative_soln);
    dealii::Tensor<1,dim,real2> vel;
    for (int d=0; d<dim; ++d) { vel[d] = conservative_soln[1+d]/density; }
    return vel;
}

template <int dim, int nstate, typename real>
template <typename real2>
inline real2 InviscidRealGas<dim,nstate,real>
::compute_velocity_squared ( const dealii::Tensor<1,dim,real2> &velocities ) const
{
    real2 vel2 = 0.0;
    for (int d=0; d<dim; d++) { 
        vel2 = vel2 + velocities[d]*velocities[d]; 
    }    
    
    return vel2;
}

// template <int dim, int nstate, typename real>
// inline std::array<real,nstate> InviscidRealGas<dim,nstate,real>
// :: get_NASA_coeff ( const real temperature ) const
// {
//     /// delete this
//     temperature = temperature;
//     ///
//     /// IT is for N2, T range: 200[K] - 1000[K]
//     real a1 = 2.210371497e+04;
//     real a2 = -3.818461820e+02;
//     real a3 = 6.082738360e+00;
//     real a4 = -8.530914410e-03;
//     real a5 = 1.384646189e-05;
//     real a6 = -9.625793620e-09;
//     real a7= 2.519705809e-12;
//     real b1 = 7.108460860e+02;
//     /// array
//     real coeff[0] = a1;
//     real coeff[1] = a2;
//     real coeff[2] = a3;
//     real coeff[3] = a4;
//     real coeff[4] = a5;
//     real coeff[5] = a6;
//     real coeff[6] = a7;
//     real coeff[7] = b1;
//     return coeff;
// }

/// It IS FOR Cp computation
template <int dim, int nstate, typename real>
inline real InviscidRealGas<dim,nstate,real>
:: compute_Cp ( const real temperature ) const
{
    /// This should be made as a function ...
    /// It is for N2, T range: 200[K] - 1000[K]
    real a1 = 2.210371497e+04;
    real a2 = -3.818461820e+02;
    real a3 = 6.082738360e+00;
    real a4 = -8.530914410e-03;
    real a5 = 1.384646189e-05;
    real a6 = -9.625793620e-09;
    real a7= 2.519705809e-12;
    // real b1 = 7.108460860e+02;
    /// 
    /// gas constant_air
    real N_air = 28.96470 * 10e-4; // [kg/mol]
    real Ru = 8.314;               // [J/mol]
    real R_air = Ru/N_air;              // [J/kg]
    real R_ref = R_air; // [J/kg]
    /// gas constant_N2
    real N_N2 = 28.01340 * 10e-4;  // [kg/mol]
    real R_N2 = Ru/N_N2;           // [J/kg]
    R_N2 = R_N2/R_ref;         // [...]
    /// This should be madde as a function...

    /// temperature
    real temperature_ref = 273.15; // [K]
    /// dimensinalize... T
    real T = temperature*temperature_ref; // [K]

    /// polynomial
    real Cp = a1/pow(T,2.0) + a2/T + a3 + a4*T + a5*pow(T,2.0) + a6*pow(T,3.0) + a7*pow(T,4.0);
    Cp = Cp*R_N2;
    return Cp;
}

/// It is for h computation
template <int dim, int nstate, typename real>
inline real InviscidRealGas<dim,nstate,real>
:: compute_enthalpy ( const real temperature  ) const
{
    /// This should be made as a function ...
    /// It is for N2, T range: 200[K] - 1000[K]
    real a1 = 2.210371497e+04;
    real a2 = -3.818461820e+02;
    real a3 = 6.082738360e+00;
    real a4 = -8.530914410e-03;
    real a5 = 1.384646189e-05;
    real a6 = -9.625793620e-09;
    real a7= 2.519705809e-12;
    real b1 = 7.108460860e+02;
    /// 
    /// gas constant_air
    real N_air = 28.96470 * 10e-4; // [kg/mol]
    real Ru = 8.314;               // [J/mol]
    real R_air = Ru/N_air;              // [J/kg]
    real R_ref = R_air; // [J/kg]
    /// gas constant_N2
    real N_N2 = 28.01340 * 10e-4;  // [kg/mol]
    real R_N2 = Ru/N_N2;           // [J/kg]
    R_N2 = R_N2/R_ref;         // [...]
    /// This should be madde as a function...

    /// temperature
    real temperature_ref = 273.15; // [K]
    /// dimensinalize... T
    real T = temperature*temperature_ref; // [K]


    /// polynomial
    real enthalpy = -a1/pow(T,2.0) + a2*(log(T))/T + a3 + a4*T/2 + a5*pow(T,2.0)/3 + a6*pow(T,3.0)/4 + a7*pow(T,4.00)/5 +b1/T;
    return enthalpy;
}

/// IT IS FOR ALGORITHM 3
template <int dim, int nstate, typename real>
inline real InviscidRealGas<dim,nstate,real>
:: compute_temperature ( const std::array<real,nstate> &conservative_soln ) const
{
    const real density = compute_density(conservative_soln);
    const dealii::Tensor<1,dim,real> vel = compute_velocities(conservative_soln);
    const real vel2 = compute_velocity_squared(vel);

    /// initial guess: This must be modified...
    real temperature_old = 1.0; /// [...]
    ///

    /// This must be constant (outside the function)
    /// gas constant_air
    real N_air = 28.96470 * 10e-4; // [kg/mol]
    real Ru = 8.314;               // [J/mol]
    real R_air = Ru/N_air;         // [J/kg]
    real R_ref = R_air;            // [J/kg]
    /// gas constant_N2
    real N_N2 = 28.01340 * 10e-4;  // [kg/mol]
    real R_N2 = Ru/N_N2;           // [J/kg]
    R_N2 = R_N2/R_ref;             // [...]
    /// temperature
    real temperature_ref = 273.15; // [K]
    /// velocity
    real vel_ref = 1.0; /// mach_inf???
    /// This should be madde as a function...

    /// initial guess.... this must be modified
    real temperature = temperature_old;

    /// Newton-Raphson method
    real tol = 1.0;
    do {
        real Cp = compute_Cp(temperature);
        real enthalpy = compute_enthalpy(temperature);
        real f_T  = (enthalpy - (R_ref*temperature_ref/pow(vel_ref,2.0))*R_N2*temperature) - (conservative_soln[3]/density - 0.50*vel2);
        real f_Td = (R_ref*temperature_ref/pow(vel_ref,2.0)) * (Cp - R_N2);
        temperature = temperature_old - f_T/f_Td;
        tol = abs(temperature - temperature_old);
        temperature_old = temperature;
    }
    while (tol > 1.0e-5); // this should be modifieds

    return temperature;
}

/// IT IS FOR ALGORITHM 4
template <int dim, int nstate, typename real>
inline real InviscidRealGas<dim,nstate,real>
:: compute_pressure ( const std::array<real,nstate> &conservative_soln ) const
{
    const real density = compute_density(conservative_soln);

    /// This must be constant (outside the function)
    /// gas constant_air
    real N_air = 28.96470 * 10e-4; // [kg/mol]
    real Ru = 8.314;               // [J/mol]
    real R_air = Ru/N_air;         // [J/kg]
    real R_ref = R_air;            // [J/kg]
    /// gas constant_N2
    real N_N2 = 28.01340 * 10e-4;  // [kg/mol]
    real R_N2 = Ru/N_N2;           // [J/kg]
    R_N2 = R_N2/R_ref;             // [...]
    /// gamma
    real gam_ref = 1.4;
    /// mach_ref
    real mach_ref = 1.0;

    /// This should be madde as a function...

    real temperature = compute_temperature(conservative_soln);
    real pressure = (density*R_N2*temperature) / (gam_ref*pow(mach_ref,2.0));

    return pressure;
}

/// IT IS FOR ALGORITHM 6, IT is only valid for single species. For multi-species, adding algorism 5 and modify largely this.
template <int dim, int nstate, typename real>
inline real InviscidRealGas<dim,nstate,real>
:: compute_total_enthalpy ( const std::array<real,nstate> &conservative_soln ) const
{
    const real density = compute_density(conservative_soln);
    const real pressure = compute_pressure(conservative_soln);
    const real total_energy = conservative_soln[3]/density;
    real total_enthalpy = total_energy + pressure/density;

    return total_enthalpy;
}

/// IT IS FOR ALGORITHM 7
template <int dim, int nstate, typename real>
std::array<dealii::Tensor<1,dim,real>,nstate> InviscidRealGas<dim,nstate,real>
::convective_flux (const std::array<real,nstate> &conservative_soln) const
{
    std::array<dealii::Tensor<1,dim,real>,nstate> conv_flux;
    const real density = compute_density(conservative_soln);
    const real pressure = compute_pressure(conservative_soln);
    const dealii::Tensor<1,dim,real> vel = compute_velocities(conservative_soln);
    const real total_enthalpy = compute_total_enthalpy(conservative_soln);

    for (int flux_dim=0; flux_dim<dim; ++flux_dim) {
        // Density equation
        conv_flux[0][flux_dim] = conservative_soln[1+flux_dim];
        // Momentum equation
        for (int velocity_dim=0; velocity_dim<dim; ++velocity_dim){
            conv_flux[1+velocity_dim][flux_dim] = density*vel[flux_dim]*vel[velocity_dim];
        }
        conv_flux[1+flux_dim][flux_dim] += pressure; // Add diagonal of pressure
        // Energy equation
        conv_flux[nstate-1][flux_dim] = density*vel[flux_dim]*total_enthalpy;
        // TO DO: now loop over nspecies
    }
    return conv_flux;
}



// Instantiate explicitly
template class InviscidRealGas < PHILIP_DIM, PHILIP_DIM+2, double     >;
template class InviscidRealGas < PHILIP_DIM, PHILIP_DIM+2, FadType    >;
template class InviscidRealGas < PHILIP_DIM, PHILIP_DIM+2, RadType    >;
template class InviscidRealGas < PHILIP_DIM, PHILIP_DIM+2, FadFadType >;
template class InviscidRealGas < PHILIP_DIM, PHILIP_DIM+2, RadFadType >;

} // Physics namespace
} // PHiLiP namespace
