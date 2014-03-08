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

#include "MooseApp.h"

class PhaseFieldApp : public MooseApp
{
public:
  static InputParameters validParams();

  PhaseFieldApp(const InputParameters & parameters);
  virtual ~PhaseFieldApp();

  static void registerApps();
  static void registerAll(Factory & f, ActionFactory & af, Syntax & s);
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
  static void registerExecFlags(Factory & factory);
};
=======
#ifndef PHASE_FIELDAPP_H
#define PHASE_FIELDAPP_H

#include "MooseApp.h"

class PhaseFieldApp;

template<>
InputParameters validParams<PhaseFieldApp>();

class PhaseFieldApp : public MooseApp
{
public:
  PhaseFieldApp(const std::string & name, InputParameters parameters);
  virtual ~PhaseFieldApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* PHASE_FIELDAPP_H */
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)
