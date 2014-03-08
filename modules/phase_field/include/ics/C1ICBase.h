<<<<<<< HEAD
//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

// Portions of this code Copyright 2007-2009 Roy Stogner
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
//"Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
=======
#ifndef C1ICBASE_H
#define C1ICBASE_H

//Portions of this code Copyright 2007-2009 Roy Stogner
//
//Permission is hereby granted, free of charge, to any person obtaining
//a copy of this software and associated documentation files (the
//"Software"), to deal in the Software without restriction, including
//without limitation the rights to use, copy, modify, merge, publish,
//distribute, sublicense, and/or sell copies of the Software, and to
//permit persons to whom the Software is furnished to do so, subject to
//the following conditions:
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
//CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
//TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)

#include "Kernel.h"
#include "InitialCondition.h"

// System includes
#include <string>

<<<<<<< HEAD
=======
// Forward Declarations
<<<<<<< HEAD
=======
class C1ICBase;

template<>
InputParameters validParams<C1ICBase>();
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)

>>>>>>> 1519a1c8f7 (Merging Modules into MOOSE #2460)
/**
 * C1ICBase is used by the CrossIC.
 */
class C1ICBase : public InitialCondition
{
public:
<<<<<<< HEAD
  static InputParameters validParams();

  C1ICBase(const InputParameters & parameters);
=======

  /**
   * Constructor
   *
   * @param name The name given to the initial condition in the input file.
   * @param parameters The parameters object holding data for the class to use.
   * @param var_name The variable this InitialCondtion is supposed to provide values for.
   */
  C1ICBase(const std::string & name,
           InputParameters parameters);
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)

protected:
  Real _average;
  Real _amplitude;
  Real _length;
  Real _width;
  Real _buffer;
  Real _interface;

  Number interfaceValue(Real r);
  Number interfaceDerivative(Real r);
};
<<<<<<< HEAD
=======

#endif //C1ICBASE_H
>>>>>>> d297f50cb1 (Merging Modules into MOOSE #2460)
