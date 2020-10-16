//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "ElementBlockIDChangerBase.h"
#include "MooseEnum.h"

class ElementBlockIDChanger;


template <>
InputParameters validParams<ElementBlockIDChanger>();


class ElementBlockIDChanger : public ElementBlockIDChangerBase
{
public:
	ElementBlockIDChanger(const InputParameters& parameters);

protected:
	virtual bool shouldChange(const Elem * elem) override;

private:
	///Defines the elements to be removed
	const std::vector<std::string> _ids;
};

