set(FLUX_SOURCE
    viscous_numerical_flux.cpp
    convective_numerical_flux.cpp
    numerical_flux_factory.cpp)

set(POSSIBLE_N_SPECIES "1;11")

foreach(nspecies ${POSSIBLE_N_SPECIES})
foreach(dim RANGE 1 3)
    # Output library
    if(${nspecies} EQUAL "1")
        string(CONCAT NumericalFluxLib NumericalFlux_${dim}D)
    else()
        string(CONCAT NumericalFluxLib NumericalFlux_${dim}D_${nspecies}-SPECIES)
    endif()
    add_library(${NumericalFluxLib} STATIC ${FLUX_SOURCE})
    # Replace occurences of PHILIP_DIM with 1, 2, or 3 in the code
    target_compile_definitions(${NumericalFluxLib} PRIVATE PHILIP_DIM=${dim})
    target_compile_definitions(${NumericalFluxLib} PRIVATE N_SPECIES=${nspecies})

    # Library dependency
    if(${nspecies} EQUAL "1")
        string(CONCAT PhysicsLib Physics_${dim}D)
    else()
        string(CONCAT PhysicsLib Physics_${dim}D_${nspecies}-SPECIES)
    endif()
    target_link_libraries(${NumericalFluxLib} ${PhysicsLib})
    # Setup target with deal.II
    if(NOT DOC_ONLY)
        DEAL_II_SETUP_TARGET(${NumericalFluxLib})
    endif()

    unset(NumericalFluxLib)
    unset(PhysicsLib)
endforeach()
endforeach()
