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

#include "NodalBC.h"

// Forward Declarations

// Specialization required of all user-level Moose objects
=======
#ifndef NSIMPOSEDVELOCITYDIRECTIONBC_H
#define NSIMPOSEDVELOCITYDIRECTIONBC_H

#include "NodalBC.h"

//Forward Declarations
class NSImposedVelocityDirectionBC;


// Specialization required of all user-level Moose objects
template<>
InputParameters validParams<NSImposedVelocityDirectionBC>();


>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)

/**
 * This class imposes a velocity direction component as a
 * Dirichlet condition on the appropriate momentum equation.
 * For example, in the x-direction, the residual equation becomes:
 *
 * u1/|u| - u1_hat_desired = 0
 *
 * or
 *
 * u1 - u1_hat_desired*|u| = 0
 *
 * or
 *
 * rho*u1 - rho*u1_hat_desired*|u| = 0
 *
 * where:
 * u1  = the x-momentum component
 * |u| = velocity magnitude
<<<<<<< HEAD
 * u1_hat_desired = The desired velocity direction, \f$ \in (0,1) \f$
=======
 * u1_hat_desired = The desired velocity direction, \in (0,1)
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)
 */
class NSImposedVelocityDirectionBC : public NodalBC
{
public:
<<<<<<< HEAD
  static InputParameters validParams();

  NSImposedVelocityDirectionBC(const InputParameters & parameters);

protected:
=======
  // Constructor
  NSImposedVelocityDirectionBC(const std::string & name, InputParameters parameters);

  // Destructor, better be virtual
  virtual ~NSImposedVelocityDirectionBC(){}

protected:

>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)
  // NodalBC's can (currently) only specialize the computeQpResidual function,
  // the computeQpJacobian() function automatically assembles a "1" onto the main
  // diagonal for this DoF.
  virtual Real computeQpResidual();

  // Coupled variables
<<<<<<< HEAD
  const VariableValue & _rho;
  const VariableValue & _u_vel;
  const VariableValue & _v_vel;
  const VariableValue & _w_vel;
=======
  VariableValue& _rho;
  VariableValue& _u_vel;
  VariableValue& _v_vel;
  VariableValue& _w_vel;
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)

  // The desired value for the unit velocity component
  Real _desired_unit_velocity_component;
};
<<<<<<< HEAD
=======


#endif // NSIMPOSEDVELOCITYDIRECTIONBC_H
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)
