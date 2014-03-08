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
#ifndef DESORPTIONTOPORESPACE
#define DESORPTIONTOPORESPACE
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)

#include "Kernel.h"
#include "LangmuirMaterial.h"

// Forward Declarations
<<<<<<< HEAD

/**
 * Mass flow rate of fluid to the porespace from the matrix
 * Add this to the DE for the porepressure variable to get
 * fluid flowing from the matrix to the porespace
 */
class DesorptionToPorespace : public Kernel
{
public:
  static InputParameters validParams();

  DesorptionToPorespace(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

  /// MOOSE internal variable number corresponding to the concentration in the matrix (needed for OffDiagJacobian)
  const unsigned int _conc_var;

  /// mass flow rate from matrix = mass flow rate to porespace
  const MaterialProperty<Real> & _mass_rate_from_matrix;

  /// derivative of mass flow rate from matrix wrt concentration
  const MaterialProperty<Real> & _dmass_rate_from_matrix_dC;

  /// derivative of mass flow rate from matrix wrt pressure
  const MaterialProperty<Real> & _dmass_rate_from_matrix_dp;
};
=======
class DesorptionToPorespace;

template<>
InputParameters validParams<DesorptionToPorespace>();

class DesorptionToPorespace : public Kernel
{
public:

  DesorptionToPorespace(const std::string & name,
                        InputParameters parameters);

protected:
  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  VariableValue * _conc_val;
  unsigned int _conc_var;

  MaterialProperty<Real> &_desorption_time_const;
  MaterialProperty<Real> &_adsorption_time_const;
  MaterialProperty<Real> &_equilib_conc;
  MaterialProperty<Real> &_equilib_conc_prime;

};

#endif //DESORPTIONTOPORESPACE
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)
