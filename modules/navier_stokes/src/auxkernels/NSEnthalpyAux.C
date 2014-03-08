<<<<<<< HEAD
//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

// Navier-Stokes includes
#include "NSEnthalpyAux.h"
#include "NS.h"

registerMooseObject("NavierStokesApp", NSEnthalpyAux);

InputParameters
NSEnthalpyAux::validParams()
{
  InputParameters params = AuxKernel::validParams();

  params.addClassDescription("Nodal auxiliary variable, for computing enthalpy at the nodes.");
  // Mark variables as required
  params.addRequiredCoupledVar(NS::density, "density");
  params.addRequiredCoupledVar(NS::total_energy, "total energy");
  params.addRequiredCoupledVar(NS::pressure, "pressure");
=======
#include "NSEnthalpyAux.h"

template<>
InputParameters validParams<NSEnthalpyAux>()
{
  InputParameters params = validParams<AuxKernel>();

  // Mark variables as required
  params.addRequiredCoupledVar("rho", "");
  params.addRequiredCoupledVar("rhoe", "");
  params.addRequiredCoupledVar("pressure", "");

  // Parameters with default values
  params.addRequiredParam<Real>("gamma", "Ratio of specific heats");
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)

  return params;
}

<<<<<<< HEAD
NSEnthalpyAux::NSEnthalpyAux(const InputParameters & parameters)
  : AuxKernel(parameters),
    _rho(coupledValue(NS::density)),
    _rhoE(coupledValue(NS::total_energy)),
    _pressure(coupledValue(NS::pressure))
{
  mooseDeprecated("The NSEnthalpyAux auxiliary kernel has been replaced by the EnthalpyAux "
                  "auxiliary kernel");
}
=======
NSEnthalpyAux::NSEnthalpyAux(const std::string & name, InputParameters parameters)
  :AuxKernel(name, parameters),
   _rho(coupledValue("rho")),
   _rhoe(coupledValue("rhoe")),
   _pressure(coupledValue("pressure")),
   _gamma(getParam<Real>("gamma"))
{}
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)

Real
NSEnthalpyAux::computeValue()
{
  // H = (rho*E + P) / rho
<<<<<<< HEAD
  return (_rhoE[_qp] + _pressure[_qp]) / _rho[_qp];
=======
  return (_rhoe[_qp] + _pressure[_qp]) / _rho[_qp];
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)
}
