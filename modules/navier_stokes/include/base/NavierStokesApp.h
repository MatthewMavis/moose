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

class NavierStokesApp : public MooseApp
{
public:
  static InputParameters validParams();

  NavierStokesApp(InputParameters parameters);
  virtual ~NavierStokesApp();

  static void registerApps();
  static void registerAll(Factory & f, ActionFactory & af, Syntax & s);
  static void registerObjects(Factory & factory);
  static void registerObjectDepends(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
  static void registerExecFlags(Factory & factory);
  static void associateSyntaxDepends(Syntax & syntax, ActionFactory & action_factory);

  bool errorOnJacobianNonzeroReallocation() const override final { return true; }
};
=======
#ifndef NAVIER_STOKESAPP_H
#define NAVIER_STOKESAPP_H

#include "MooseApp.h"

class NavierStokesApp;

template<>
InputParameters validParams<NavierStokesApp>();

class NavierStokesApp : public MooseApp
{
public:
  NavierStokesApp(const std::string & name, InputParameters parameters);
  virtual ~NavierStokesApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* NAVIER_STOKESAPP_H */
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)
