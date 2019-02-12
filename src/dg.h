#ifndef __DISCONTINUOUSGALERKIN_H__
#define __DISCONTINUOUSGALERKIN_H__

#include <deal.II/base/parameter_handler.h>

#include <deal.II/grid/tria.h>

#include <deal.II/fe/fe_dgq.h>
#include <deal.II/fe/fe_dgp.h>
#include <deal.II/fe/mapping_q1.h> // Might need mapping_q
#include <deal.II/fe/mapping_q.h> // Might need mapping_q

#include <deal.II/dofs/dof_handler.h>

#include <deal.II/lac/vector.h>

#include "parameters.h"


namespace PHiLiP
{
    using namespace dealii;

    template <int dim, typename real>
    class DiscontinuousGalerkin
    {
    public:
        //DiscontinuousGalerkin(Parameters::AllParameters *parameters_input);
        DiscontinuousGalerkin(Parameters::AllParameters *parameters_input, const unsigned int degree);
        int run();

    private:
        void compute_inv_mass_matrix();
        void compute_stiffness_matrix();

        void setup_system ();

        void compute_time_step();

        void assemble_system (
            FEValues<dim,dim> &fe_values,
            FEFaceValues<dim,dim> &fe_values_face,
            FEFaceValues<dim,dim> &fe_values_face_neighbor,
            FESubfaceValues<dim,dim> &fe_values_subface);
        void assemble_cell_terms_explicit(
            const FEValues<dim,dim> &fe_values,
            const std::vector<types::global_dof_index> &current_dofs_indices,
            Vector<real> &current_cell_rhs);
        void assemble_boundary_term_explicit(
            const FEFaceValues<dim,dim> &fe_values_face,
            const std::vector<types::global_dof_index> &current_dofs_indices,
            Vector<real> &current_cell_rhs);
        void assemble_face_term_explicit(
            const FEValuesBase<dim,dim> &fe_values_face_current,
            const FEFaceValues<dim,dim>     &fe_values_face_neighbor,
            const std::vector<types::global_dof_index> &current_dofs_indices,
            const std::vector<types::global_dof_index> &neighbor_dofs_indices,
            Vector<real>          &current_cell_rhs,
            Vector<real>          &neighbor_cell_rhs);

        void solve(Vector<real> &solution);
        void output_results(const unsigned int cycle) const;

        // Mesh
        Triangulation<dim>   triangulation;

        // For now, use linear mapping of domain boundaries
        // May need to use MappingQ or MappingQGeneric to represent curved 
        // boundaries iso/superparametrically
        const MappingQ<dim,dim> mapping;

        // Lagrange polynomial basis
        //FE_DGQ<dim> finite_element;
        // Legendre polynomial basis
        FE_DGP<dim> fe;

        // Degrees of freedom handler allows us to iterate over the finite
        // elements' degrees of freedom on the given triangulation
        DoFHandler<dim> dof_handler;

        const QGauss<dim>   quadrature;
        const QGauss<dim-1> face_quadrature;


        //// Sparse matrix needed to hold the system
        //SparsityPattern      sparsity_pattern;
        //SparseMatrix<double> system_matrix;
        //FullMatrix<real> cell_mass_matrix;
        //FullMatrix<real> cell_stiffness_matrix;
        //FullMatrix<real> cell_lifting_matrix;
        //FullMatrix<real> inverse_mass_matrix;
        //FullMatrix<real> phys_to_ref_matrix;

        Vector<real> solution;
        Vector<real> right_hand_side;
        Vector<real> source_term;

        Vector<real> cell_rhs;

        std::vector< FullMatrix<real> > inv_mass_matrix;

        Parameters::AllParameters *parameters;


    }; // end of DiscontinuousGalerkin class
    //template class DiscontinuousGalerkin<1, double>;
    //template class DiscontinuousGalerkin<2, double>;
    //template class DiscontinuousGalerkin<3, double>;


    // Returns a pointer to a DiscontinuousGalerkin object with correct template arguments
    //DiscontinuousGalerkin* create_discontinuous_galerkin (
    //    const unsigned int dimension,
    //    Parameters::AllParameters *parameters_input,
    //    const unsigned int degree,
    //    const unsigned int double_type = 0);
} // end of PHiLiP namespace

#endif
