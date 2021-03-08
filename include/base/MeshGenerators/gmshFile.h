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

  const Real _hole_radius;

  const Real _Cooling_Tube_Thickness;
  
  const Real _Intermediate_Thickness;

  const Real _Small_Hole_Radius;

  const Real _Angle_Between_Holes;
  
  const int _HoleAmount;

  const Real _Thermal_Slit_Width;
  
};
