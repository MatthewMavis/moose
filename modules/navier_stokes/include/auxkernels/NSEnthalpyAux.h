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

// MOOSE includes
#include "AuxKernel.h"

// Forward Declarations
=======
#ifndef NSENTHALPYAUX_H
#define NSENTHALPYAUX_H

#include "AuxKernel.h"

//Forward Declarations
class NSEnthalpyAux;

template<>
InputParameters validParams<NSEnthalpyAux>();
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)

/**
 * Nodal auxiliary variable, for computing enthalpy at the nodes.
 * The total enthalpy is given by:
 *
 * H = E + p/rho (primitive variables)
 * H = (U_4 + P(U)) / U_0 (conserved variables)
 *
 * where P(U) = (gamma-1)*(U_4 - (1/2)*(U_1^2 + U_2^2 + U_3^2)/U_0)
 * is the pressure.
 */
class NSEnthalpyAux : public AuxKernel
{
public:
<<<<<<< HEAD
  static InputParameters validParams();

  NSEnthalpyAux(const InputParameters & parameters);
=======

  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  NSEnthalpyAux(const std::string & name, InputParameters parameters);

  virtual ~NSEnthalpyAux() {}
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)

protected:
  virtual Real computeValue();

<<<<<<< HEAD
  const VariableValue & _rho;
  const VariableValue & _rhoE;
  const VariableValue & _pressure;
};
=======
  VariableValue & _rho;
  VariableValue & _rhoe;
  VariableValue & _pressure;

  Real _gamma;
};

#endif // NSENTHALPYAUX_H
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)
