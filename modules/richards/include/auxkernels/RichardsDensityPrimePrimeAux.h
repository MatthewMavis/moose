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
/*****************************************/
/* Written by andrew.wilkins@csiro.au    */
/* Please contact me if you make changes */
/*****************************************/

#ifndef RICHARDSDENSITYPRIMEPRIMEAUX_H
#define RICHARDSDENSITYPRIMEPRIMEAUX_H
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)

#include "AuxKernel.h"

#include "RichardsDensity.h"

<<<<<<< HEAD
// Forward Declarations

/**
 * Second derivative of fluid density wrt porepressure
 */
class RichardsDensityPrimePrimeAux : public AuxKernel
{
public:
  static InputParameters validParams();

  RichardsDensityPrimePrimeAux(const InputParameters & parameters);
=======
//Forward Declarations
class RichardsDensityPrimePrimeAux;

template<>
InputParameters validParams<RichardsDensityPrimePrimeAux>();

class RichardsDensityPrimePrimeAux: public AuxKernel
{
public:
  RichardsDensityPrimePrimeAux(const std::string & name, InputParameters parameters);
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)

protected:
  virtual Real computeValue();

<<<<<<< HEAD
  /// porepressure
  const VariableValue & _pressure_var;

  /// userobject that defines density as a fcn of porepressure
  const RichardsDensity & _density_UO;
};
=======
  VariableValue & _pressure_var;
  const RichardsDensity & _density_UO;
};

#endif // RICHARDSDENSITYPRIMEPRIMEAUX_H
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)
