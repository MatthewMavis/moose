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

#include "NSKernel.h"

// ForwardDeclarations
=======
#ifndef NSMOMENTUMINVISCIDFLUX_H
#define NSMOMENTUMINVISCIDFLUX_H

#include "NSKernel.h"


// ForwardDeclarations
class NSMomentumInviscidFlux;

template<>
InputParameters validParams<NSMomentumInviscidFlux>();


>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)

/**
 * The inviscid flux (convective + pressure terms) for the
 * momentum conservation equations.
 */
class NSMomentumInviscidFlux : public NSKernel
{
public:
<<<<<<< HEAD
  static InputParameters validParams();

  NSMomentumInviscidFlux(const InputParameters & parameters);
=======

  NSMomentumInviscidFlux(const std::string & name, InputParameters parameters);
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Coupled variables
<<<<<<< HEAD
  const VariableValue & _pressure;

  // Parameters
  const unsigned int _component;
=======
  VariableValue & _pressure;

  // Parameters
  unsigned _component;
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)

private:
  // To be used from both the on and off-diagonal
  // computeQpJacobian functions.  Variable numbering
  // should be in the canonical ordering regardless of
  // Moose's numbering.
<<<<<<< HEAD
  Real computeJacobianHelper(unsigned int m);
};
=======
  Real compute_jacobian(unsigned m);
};

#endif
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)
