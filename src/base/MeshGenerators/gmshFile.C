//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "gmshFile.h"
#include "CastUniquePointer.h"
#include "RestartableDataIO.h"

#include "libmesh/replicated_mesh.h"
#include "libmesh/face_quad4.h"
#include "libmesh/exodusII_io.h"
#include "libmesh/mesh_communication.h"

#include <set>
#include <gmsh.h>
#include <iostream>
#include <vector>
#include <iterator>

#define _USE_MATH_DEFINES
 
#include <cmath>

registerMooseObject("MooseApp", gmshFile);

defineLegacyParams(gmshFile);

InputParameters
gmshFile::validParams()
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
  params.addRequiredParam<MeshFileName>("geofile", "The gmsh .geo file to read.");
  params.addRequiredParam<int>("dim", "Dimensions of the mesh");
  params.addParam<std::vector<std::string>>(
    "param_names","The names of the variable parameters to change");
  params.addParam<std::vector<Real>>(
    "param_values","The values of the variable parameters to change");

  params.addClassDescription("Read a mesh from a file.");
  return params;
}

gmshFile::gmshFile(const InputParameters & parameters)
  : MeshGenerator(parameters), _file_name(getParam<MeshFileName>("file")),
  _geo_file_name(getParam<MeshFileName>("geofile")),
  _dim(getParam<int>("dim")),
  _param_names(getParam<std::vector<std::string>>("param_names")),
  _param_values(getParam<std::vector<Real>>("param_values"))
  
{
  gmsh::initialize();

  //Grab the names and values that need to be changed based on the user input.
  //These values are entered into onelab::setNumber which adds a json database entry
  //for them. This is then merged into the real .geo file in memory. (The .geo is not physically changed).
  int param_amount = _param_names.size();
  for (int i=0; i< param_amount; i++){
    std::cout << "Changing "<< _param_names[i] << " to " << _param_values[i] << std::endl;
    gmsh::onelab::setNumber(_param_names[i], {_param_values[i]});
  }

  gmsh::merge(_geo_file_name);

  //gmsh::open(_geo_file_name);

  gmsh::model::mesh::generate(_dim);

  gmsh::write(_file_name);

  gmsh::finalize();

}

std::unique_ptr<MeshBase>
gmshFile::generate()
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
