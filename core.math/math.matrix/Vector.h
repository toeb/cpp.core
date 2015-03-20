/*
* nspace - Impulse-Based Dynamic Simulation Library
* Copyright (c) 2003-2008 Jan Bender http://www.impulse-based.de
*
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*
* Jan Bender - Jan.Bender@impulse-based.de
*/
#pragma once

#include <config.h>
#include <math.matrix/Matrix.h>

#include <math.matrix/MatrixOperations.h>
namespace nspace
{
  /** Vector ist die Oberklasse aller Vektorklassen
  \author Jan Bender
  */
  template<typename T>
  class Vector : public Matrix<T >
  {
  public:

    virtual T & operator()(int i)=0;
    virtual const T & operator()(int i)const=0;
    virtual int size()const=0;

    virtual T length() const = 0;			    // Länge
    virtual T length2() const = 0;			    // Quadratische Länge
    virtual void normalize() = 0;				// Normierung
  };
}
