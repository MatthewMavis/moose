//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ElementBlockIDChangerGeneratorBase.h"
#include "libmesh/remote_elem.h"

#include "MooseMeshUtils.h"
#include "CastUniquePointer.h"

InputParameters
validParams<ElementBlockIDChangerGeneratorBase>()
{
  InputParameters params = MeshGenerator::validParams();
  params.addRequiredParam<MeshGeneratorName>("input", "The mesh we want to modify");
  return params;
}

ElementBlockIDChangerGeneratorBase::ElementBlockIDChangerGeneratorBase(const InputParameters & parameters)
  : MeshGenerator(parameters),
  _input(getMesh("input"))
{
}

std::unique_ptr<MeshBase>
ElementBlockIDChangerGeneratorBase::generate()
{
  std::unique_ptr<MeshBase> mesh = std::move(_input);

  // First let's figure out which elements need to be changed
  for (auto & elem : mesh->element_ptr_range())
  {
    if (shouldChange(elem)){
      SubdomainID block_id = static_cast<SubdomainID>(99);
      elem->subdomain_id() = block_id;
      std::cout << elem->subdomain_id() << std::endl;
    }
  }

  return dynamic_pointer_cast<MeshBase>(mesh);
}
