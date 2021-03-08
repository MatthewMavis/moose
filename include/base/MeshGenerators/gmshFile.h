//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "MeshGenerator.h"

// Forward declarations
class gmshFile;

template <>
InputParameters validParams<gmshFile>();

/**
 * Generates a mesh by reading it from an file.
 */
class gmshFile : public MeshGenerator
{
public:
  static InputParameters validParams();

  gmshFile(const InputParameters & parameters);

  

  std::unique_ptr<MeshBase> generate() override;

protected:
  const MeshFileName & _file_name;
  
  const MeshFileName & _geo_file_name;

  const int _dim;

  const std::vector<std::string> _param_names;

  const std::vector<Real> _param_values;

  
};
