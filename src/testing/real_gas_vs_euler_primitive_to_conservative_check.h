#ifndef __REAL_GAS_VS_EULER_PRIMITIVE_TO_CONSERVATIVE_CHECK__
#define __REAL_GAS_VS_EULER_PRIMITIVE_TO_CONSERVATIVE_CHECK__

#include "tests.h"

namespace PHiLiP {
namespace Tests {

/// Real Gas Vs Euler Primitive To Conservative Check
template <int dim, int nstate>
class RealGasVsEulerPrimitiveToConservativeCheck: public TestsBase
{
public:
    /// Constructor
    RealGasVsEulerPrimitiveToConservativeCheck(
        const Parameters::AllParameters *const parameters_input,
        const dealii::ParameterHandler &parameter_handler_input);

    /// Parameter handler for storing the .prm file being ran
    const dealii::ParameterHandler &parameter_handler;
    
    // /// Expected kinetic energy at final time
    // const double kinetic_energy_expected;

    // /// Expected theoretical dissipation rate at final time
    // const double theoretical_dissipation_rate_expected;

    /// Run test
    int run_test () const override;
};

} // End of Tests namespace
} // End of PHiLiP namespace

#endif
