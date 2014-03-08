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
#ifndef NSSUPGMASS_H
#define NSSUPGMASS_H
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)

#include "NSSUPGBase.h"

// Forward Declarations
<<<<<<< HEAD
=======
class NSSUPGMass;

template<>
InputParameters validParams<NSSUPGMass>();
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)

/**
 * Compute residual and Jacobian terms form the SUPG
 * terms in the mass equation.
 */
class NSSUPGMass : public NSSUPGBase
{
public:
<<<<<<< HEAD
  static InputParameters validParams();

  NSSUPGMass(const InputParameters & parameters);
=======
  NSSUPGMass(const std::string & name, InputParameters parameters);
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:
  // Single function for computing on and off-diagonal Jacobian
  // entries in a single function.  The input index is in Moose
  // variable numbering.
<<<<<<< HEAD
  Real computeJacobianHelper(unsigned var);
};
=======
  Real compute_jacobian(unsigned var);
};

#endif // NSSUPGMASS_H
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)
