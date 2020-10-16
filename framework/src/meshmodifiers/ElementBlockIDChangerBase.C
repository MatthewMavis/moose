//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ElementBlockIDChangerBase.h"
#include "MooseMesh.h"

#include "libmesh/remote_elem.h"

template <>
InputParameters
validParams<ElementBlockIDChangerBase>()
{
  InputParameters params = validParams<MeshModifier>();
  return params;
}

ElementBlockIDChangerBase::ElementBlockIDChangerBase(const InputParameters & parameters)
  : MeshModifier(parameters)
{
}

void
ElementBlockIDChangerBase::modify()
{
  libmesh_assert(this->comm().verify(this->name()));

  // Check that we have access to the mesh
  if (!_mesh_ptr)
    mooseError("_mesh_ptr must be initialized before calling ElementBlockIDChangerBase::modify()");

  MeshBase & mesh = _mesh_ptr->getMesh();

  // First let's figure out which elements need to be deleted
  for (auto & elem : mesh.element_ptr_range())
  {
    if (shouldChange(elem)){
      SubdomainID block_id = static_cast<SubdomainID>(99);
      elem->subdomain_id() = block_id;
      std::cout << elem->subdomain_id() << std::endl;
    }
  }
}