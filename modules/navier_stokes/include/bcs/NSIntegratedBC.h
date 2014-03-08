<<<<<<< HEAD
//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once
=======
#ifndef NSINTEGRATEDBC_H
#define NSINTEGRATEDBC_H
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)

#include "IntegratedBC.h"

// Forward Declarations
<<<<<<< HEAD
class IdealGasFluidProperties;
=======
class NSIntegratedBC;

template<>
InputParameters validParams<NSIntegratedBC>();
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)

/**
 * This class couples together all the variables
 * for the compressible Navier-Stokes equations to
 * allow them to be used in derived IntegratedBC
 * classes.  This prevents duplication of lines
 * of code between e.g. the momentum and energy
 * equations, since they have a lot in common.
 */
class NSIntegratedBC : public IntegratedBC
{
public:
<<<<<<< HEAD
  static InputParameters validParams();

  NSIntegratedBC(const InputParameters & parameters);

protected:
  const VariableValue & _u_vel;
  const VariableValue & _v_vel;
  const VariableValue & _w_vel;

  const VariableValue & _rho;
  const VariableValue & _rho_u;
  const VariableValue & _rho_v;
  const VariableValue & _rho_w;
  const VariableValue & _rho_E;

  const VariableGradient & _grad_rho;
  const VariableGradient & _grad_rho_u;
  const VariableGradient & _grad_rho_v;
  const VariableGradient & _grad_rho_w;
  const VariableGradient & _grad_rho_E;

=======
  NSIntegratedBC(const std::string & name, InputParameters parameters);

  virtual ~NSIntegratedBC(){}

protected:
  /**
   * Not defined here, need to be defined in derived classes.
   */
  // virtual Real computeQpResidual();
  // virtual Real computeQpJacobian();
  // virtual Real computeQpOffDiagJacobian(unsigned jvar);

  // Coupled variables
  VariableValue& _u_vel;
  VariableValue& _v_vel;
  VariableValue& _w_vel;

  VariableValue& _rho;
  VariableValue& _rho_u;
  VariableValue& _rho_v;
  VariableValue& _rho_w;
  VariableValue& _rho_e;

  // Gradients
  VariableGradient& _grad_rho;
  VariableGradient& _grad_rho_u;
  VariableGradient& _grad_rho_v;
  VariableGradient& _grad_rho_w;
  VariableGradient& _grad_rho_e;

  // Variable numberings
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)
  unsigned _rho_var_number;
  unsigned _rhou_var_number;
  unsigned _rhov_var_number;
  unsigned _rhow_var_number;
<<<<<<< HEAD
  unsigned _rhoE_var_number;

  // Integrated BC can use Mat. properties...
  const MaterialProperty<Real> & _dynamic_viscosity;
  const MaterialProperty<RealTensorValue> & _viscous_stress_tensor; // Includes _dynamic_viscosity

  // Fluid properties
  const IdealGasFluidProperties & _fp;

  // Helper functions for mapping Moose variable numberings into
  // the "canonical" numbering for the compressible NS equations.
  bool isNSVariable(unsigned var);
  unsigned mapVarNumber(unsigned var);
};
=======
  unsigned _rhoe_var_number;

  // Integrated BC can use Mat. properties...
  MaterialProperty<Real> & _dynamic_viscosity;
  MaterialProperty<RealTensorValue> & _viscous_stress_tensor; // Includes _dynamic_viscosity

  // Required parameters
  Real _gamma;
  Real _R;

  // Helper function for mapping Moose variable numberings into
  // the "canonical" numbering for the compressible NS equations.
  unsigned map_var_number(unsigned var);
};


#endif // NSINTEGRATEDBC_H
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)
