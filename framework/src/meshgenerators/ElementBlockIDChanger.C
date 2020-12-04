//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ElementBlockIDChanger.h"
#include "MooseMesh.h"

#include "libmesh/elem.h"

registerMooseObject("MooseApp", ElementBlockIDChanger);

template <>
InputParameters
validParams<ElementBlockIDChanger>()
{
    InputParameters params = validParams<ElementBlockIDChangerGeneratorBase>();
    params.addClassDescription(
        "Mesh modifier which removes elements with the element ID");
    params.addRequiredParam<std::vector<std::string>>("ids", "The IDs of element to be removed");
    return params;
}

ElementBlockIDChanger::ElementBlockIDChanger(const InputParameters& parameters)
  : ElementBlockIDChangerGeneratorBase(parameters), _ids((getParam<std::vector<std::string>>("ids")))
{
}

bool
ElementBlockIDChanger::shouldChange(const Elem * elem)
{
  for (auto & charID : _ids){
    int delID = std::stoi(charID);
    if (elem->id() == delID){
      std::cout << elem->subdomain_id() << std::endl;
      std::cout << "Element " << elem->id() << " Block ID changed!" << std::endl;
      return true;
    }
  }
  
  return false;
  
}
