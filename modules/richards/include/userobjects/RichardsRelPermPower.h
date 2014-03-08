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

#include "RichardsRelPerm.h"

/**
 * Power form of relative permeability, usually
 * used for water
 */
class RichardsRelPermPower : public RichardsRelPerm
{
public:
  static InputParameters validParams();

  RichardsRelPermPower(const InputParameters & parameters);

  /**
   * relative permeability as a function of effective saturation
   * @param seff effective sasturation
   */
  Real relperm(Real seff) const;

  /**
   * derivative of relative permeability wrt effective saturation
   * @param seff effective sasturation
   */
  Real drelperm(Real seff) const;

  /**
   * second derivative of relative permeability wrt effective saturation
   * @param seff effective sasturation
   */
  Real d2relperm(Real seff) const;

protected:
  /// immobile saturation
  Real _simm;

  /// exponent used in the power relationship
  Real _n;
};
=======
/*****************************************/
/* Written by andrew.wilkins@csiro.au    */
/* Please contact me if you make changes */
/*****************************************/

//  "Power" form of relative permeability
//
#ifndef RICHARDSRELPERMPOWER_H
#define RICHARDSRELPERMPOWER_H

#include "RichardsRelPerm.h"

class RichardsRelPermPower;


template<>
InputParameters validParams<RichardsRelPermPower>();

class RichardsRelPermPower : public RichardsRelPerm
{
 public:
  RichardsRelPermPower(const std::string & name, InputParameters parameters);

  Real relperm(Real seff) const;
  Real drelperm(Real seff) const;
  Real d2relperm(Real seff) const;

 protected:

  Real _simm;
  Real _n;

};

#endif // RICHARDSRELPERMPOWER_H
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)
