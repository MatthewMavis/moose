#include "gmsh_testApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
gmsh_testApp::validParams()
{
  InputParameters params = MooseApp::validParams();

  // Do not use legacy DirichletBC, that is, set DirichletBC default for preset = true
  params.set<bool>("use_legacy_dirichlet_bc") = false;

  return params;
}

gmsh_testApp::gmsh_testApp(InputParameters parameters) : MooseApp(parameters)
{
  gmsh_testApp::registerAll(_factory, _action_factory, _syntax);
}

gmsh_testApp::~gmsh_testApp() {}

void
gmsh_testApp::registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ModulesApp::registerAll(f, af, s);
  Registry::registerObjectsTo(f, {"gmsh_testApp"});
  Registry::registerActionsTo(af, {"gmsh_testApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
gmsh_testApp::registerApps()
{
  registerApp(gmsh_testApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
gmsh_testApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  gmsh_testApp::registerAll(f, af, s);
}
extern "C" void
gmsh_testApp__registerApps()
{
  gmsh_testApp::registerApps();
}
