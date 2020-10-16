//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "MeshModifier.h"

class ElementBlockIDChangerBase;

template <>
InputParameters validParams<ElementBlockIDChangerBase>();

/**
 * This class deletes elements from the mesh data structure
 * after it has been generated or read but before any FEM
 * data structures are initialized. Users are free to implement
 * their own derived classes by providing an implementation
 * for "shouldDelete".
 */
class ElementBlockIDChangerBase : public MeshModifier
{ 
public:
  ElementBlockIDChangerBase(const InputParameters & parameters);

protected:
  virtual void modify() override;

  /**
   * Method that returns a Boolean indicating whether an
   * element should be removed from the mesh.
   */
  virtual bool shouldChange(const Elem * elem) = 0;

};

