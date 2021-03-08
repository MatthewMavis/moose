//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "gmshTest.h"
#include "CastUniquePointer.h"
#include "RestartableDataIO.h"

#include "libmesh/replicated_mesh.h"
#include "libmesh/face_quad4.h"
#include "libmesh/exodusII_io.h"
#include "libmesh/mesh_communication.h"

#include <set>
#include <gmsh.h>
#include <iostream>

#define _USE_MATH_DEFINES
 
#include <cmath>

registerMooseObject("MooseApp", gmshTest);

defineLegacyParams(gmshTest);

InputParameters
gmshTest::validParams()
{
  InputParameters params = MeshGenerator::validParams();

  params.addRequiredParam<MeshFileName>("file", "The filename to read.");
  params.addParam<std::vector<std::string>>(
      "exodus_extra_element_integers",
      "The variable names in the mesh file for loading extra element integers");
  params.addParam<bool>("use_for_exodus_restart",
                        false,
                        "True to indicate that the mesh file this generator is reading can be used "
                        "for restarting variables");
  params.addRequiredParam<Real>("Hole_radius",
                                       "Hole radius");

  params.addRequiredParam<Real>("Cooling_Tube_Thickness",
                                       "Cooling_Tube_Thickness");

  params.addRequiredParam<Real>("Intermediate_Thickness",
                                       "Intermediate_Thickness");

  params.addRequiredParam<Real>("Small_Hole_Radius",
                                       "Small_Hole_Radius");

  params.addRequiredParam<Real>("Angle_Between_Holes",
                                       "Angle_Between_Holes");

  params.addRequiredParam<int>("HoleAmount",
                                       "HoleAmount");

  params.addClassDescription("Read a mesh from a file.");
  return params;
}

gmshTest::gmshTest(const InputParameters & parameters)
  : MeshGenerator(parameters), _file_name(getParam<MeshFileName>("file")),
  _hole_radius(parameters.get<Real>("Hole_radius")),
  _Cooling_Tube_Thickness(parameters.get<Real>("Cooling_Tube_Thickness")),
  _Intermediate_Thickness(parameters.get<Real>("Intermediate_Thickness")),
  _Small_Hole_Radius(parameters.get<Real>("Small_Hole_Radius")),
  _Angle_Between_Holes(parameters.get<Real>("Angle_Between_Holes")),
  _HoleAmount(parameters.get<int>("HoleAmount"))
  
{
  Real holeSize = _hole_radius;
  Real Cooling_Tube_Thickness = _Cooling_Tube_Thickness;
  Real Intermediate_Thickness = _Intermediate_Thickness;
  Real Small_Hole_Radius = _Small_Hole_Radius;
  Real Angle_Between_Holes = _Angle_Between_Holes;
  int HoleAmount = _HoleAmount;
  
  gmsh::initialize();
  gmsh::model::add("DivertorSimple");

  gmsh::model::occ::addPoint(-0.014, -0.014, 0, 1.0, 1);
  gmsh::model::occ::addPoint(-0.014, 0.014, 0, 1.0, 2);

  gmsh::model::occ::addPoint(-0.0001, 0.014, 0, 1.0, 3);
  gmsh::model::occ::addPoint(-0.0001, 0.008, 0, 1.0, 4);
  gmsh::model::occ::addPoint(0.0001, 0.008, 0, 1.0, 5);
  gmsh::model::occ::addPoint(0.0001, 0.014, 0, 1.0, 6);

  gmsh::model::occ::addPoint(0.014, 0.014, 0, 1.0, 7);
  gmsh::model::occ::addPoint(0.014, -0.014, 0, 1.0, 8);

  gmsh::model::occ::addLine(1, 2, 1);
  gmsh::model::occ::addLine(2, 3, 2);
  gmsh::model::occ::addLine(3, 4, 3);
  gmsh::model::occ::addLine(4, 5, 4);
  gmsh::model::occ::addLine(5, 6, 5);
  gmsh::model::occ::addLine(6, 7, 6);
  gmsh::model::occ::addLine(7, 8, 7);
  gmsh::model::occ::addLine(8, 1, 8);
  
  gmsh::model::occ::addCircle(0 , 0, 0, holeSize + Cooling_Tube_Thickness + Intermediate_Thickness, 9);
  gmsh::model::occ::addCircle(0 , 0, 0, holeSize + Cooling_Tube_Thickness, 10);
  gmsh::model::occ::addCircle(0 , 0, 0, holeSize, 11);


  gmsh::model::occ::addCurveLoop({1,2,3,4,5,6,7,8},1);
  gmsh::model::occ::addCurveLoop({9},2);
  gmsh::model::occ::addCurveLoop({10},3);
  gmsh::model::occ::addCurveLoop({11},4);

  gmsh::model::occ::addPlaneSurface({1,2},1);
  gmsh::model::occ::addPlaneSurface({2,3},2);
  gmsh::model::occ::addPlaneSurface({3,4},3);
  gmsh::model::occ::addPlaneSurface({4},4);


  float angle = 0.0;
  int circleID = 12;
  int LoopID = 5;
  int Small_Hole_Loop_Ids[HoleAmount];
  HoleAmount = (HoleAmount-1)/2;
  for (int i=0; i<=HoleAmount; i++){
      if (i==0){
          angle = 0.0;
          float x = (holeSize+Cooling_Tube_Thickness+(Intermediate_Thickness/2))*(sin(angle));
          float y = (holeSize+Cooling_Tube_Thickness+(Intermediate_Thickness/2))*(cos(angle));
          gmsh::model::occ::addCircle( x, y, 0, Small_Hole_Radius, circleID);
          gmsh::model::occ::addCurveLoop({circleID},LoopID);
          gmsh::model::occ::addPlaneSurface({2,3,LoopID},LoopID);
          circleID++;
          LoopID++;
      }
      else{
          angle = i*(Angle_Between_Holes*(M_PI/180));
          float x = (holeSize+Cooling_Tube_Thickness+(Intermediate_Thickness/2))*(sin(angle));
          float y = (holeSize+Cooling_Tube_Thickness+(Intermediate_Thickness/2))*(cos(angle));
          gmsh::model::occ::addCircle( x, y, 0, Small_Hole_Radius, circleID);
          gmsh::model::occ::addCurveLoop({circleID},LoopID);
          gmsh::model::occ::addPlaneSurface({2,3,LoopID},LoopID);
          circleID++;
          LoopID++;

          x = (holeSize+Cooling_Tube_Thickness+(Intermediate_Thickness/2))*(sin(-angle));
          y = (holeSize+Cooling_Tube_Thickness+(Intermediate_Thickness/2))*(cos(-angle));
          gmsh::model::occ::addCircle( x, y, 0, Small_Hole_Radius, circleID);
          gmsh::model::occ::addCurveLoop({circleID},LoopID);
          gmsh::model::occ::addPlaneSurface({2,3,LoopID},LoopID);
          circleID++;
          LoopID++;

      }
  }
  


  gmsh::model::occ::synchronize();

  int top = gmsh::model::addPhysicalGroup(1, {2,6}, 1);
  int left = gmsh::model::addPhysicalGroup(1, {1}, 2);
  int right = gmsh::model::addPhysicalGroup(1, {7}, 3);
  int bottom = gmsh::model::addPhysicalGroup(1, {8}, 4);

  int Tung_Int_boundary = gmsh::model::addPhysicalGroup(1, {9}, 5);
  int Int_Tube_boundary = gmsh::model::addPhysicalGroup(1, {10}, 6);
  int Tube_Hole_boundary = gmsh::model::addPhysicalGroup(1, {11}, 7);

  int ps101 = gmsh::model::addPhysicalGroup(2, {1}, 8);
  int ps102 = gmsh::model::addPhysicalGroup(2, {2}, 9);
  int ps103 = gmsh::model::addPhysicalGroup(2, {3}, 10);
  int ps104 = gmsh::model::addPhysicalGroup(2, {4}, 11);

  gmsh::model::setPhysicalName(2, ps101, "Tungsten");
  gmsh::model::setPhysicalName(2, ps102, "Intermediate");
  gmsh::model::setPhysicalName(2, ps103, "Cooling_Tube");
  gmsh::model::setPhysicalName(2, ps104, "Hole");
  
  gmsh::model::setPhysicalName(1, top, "Top");
  gmsh::model::setPhysicalName(1, left, "Left");
  gmsh::model::setPhysicalName(1, right, "Right");
  gmsh::model::setPhysicalName(1, bottom, "Bottom");

  gmsh::model::setPhysicalName(1, Tung_Int_boundary, "Tung_Int_boundary");
  gmsh::model::setPhysicalName(1, Int_Tube_boundary, "Int_Tube_boundary");
  gmsh::model::setPhysicalName(1, Tube_Hole_boundary, "Tube_Hole_boundary");


  gmsh::option::setNumber("Mesh.MeshSizeMin", 0.00001);
  gmsh::option::setNumber("Mesh.MeshSizeMax", 0.0003);
  gmsh::option::setNumber("Mesh.Algorithm", 6);
  gmsh::model::mesh::setOrder(2);
  gmsh::model::mesh::generate(2);
  gmsh::model::mesh::refine();

  gmsh::write("DivertorSimple.msh");
  
  gmsh::finalize();

}

std::unique_ptr<MeshBase>
gmshTest::generate()
{
  auto mesh = buildMeshBaseObject();

  bool exodus =
      _file_name.rfind(".exd") < _file_name.size() || _file_name.rfind(".e") < _file_name.size();
  bool has_exodus_integers = isParamValid("exodus_extra_element_integers");
  bool restart_exodus = (getParam<bool>("use_for_exodus_restart") && _app.getExodusFileRestart());
  if (exodus)
  {
    auto exreader = std::make_shared<ExodusII_IO>(*mesh);

    if (has_exodus_integers)
      exreader->set_extra_integer_vars(
          getParam<std::vector<std::string>>("exodus_extra_element_integers"));

    if (restart_exodus)
    {
      _app.setExReaderForRestart(std::move(exreader));
      exreader->read(_file_name);
      mesh->allow_renumbering(false);
    }
    else
    {
      if (mesh->processor_id() == 0)
        exreader->read(_file_name);
      MeshCommunication().broadcast(*mesh);
    }

    mesh->prepare_for_use();
  }
  else
  {
    if (_pars.isParamSetByUser("exodus_extra_element_integers"))
      mooseError("\"exodus_extra_element_integers\" should be given only for Exodus mesh files");
    if (_pars.isParamSetByUser("use_for_exodus_restart"))
      mooseError("\"use_for_exodus_restart\" should be given only for Exodus mesh files");

    // to support LATEST word for loading checkpoint files
    std::string file_name = MooseUtils::convertLatestCheckpoint(_file_name, false);

    mesh->read(file_name);

    // we also read declared mesh meta data here if there is meta data file
    RestartableDataIO restartable(_app);
    std::string fname = file_name + "/meta_data_mesh" + restartable.getRestartableDataExt();
    if (MooseUtils::pathExists(fname))
    {
      restartable.setErrorOnLoadWithDifferentNumberOfProcessors(false);
      // get reference to mesh meta data (created by MooseApp)
      auto & meta_data = _app.getRestartableDataMap(MooseApp::MESH_META_DATA);
      if (restartable.readRestartableDataHeaderFromFile(fname, false))
        restartable.readRestartableData(meta_data, DataNames());
    }
  }

  return dynamic_pointer_cast<MeshBase>(mesh);
}
