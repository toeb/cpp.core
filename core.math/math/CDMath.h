/*
* IBDS - Impulse-Based Dynamic Simulation Library
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
#include <math/core.h>
#include <math/MathDefs.h>
namespace nspace
{
  // 	/** CDMath enthält einige wichtige mathematischen Funktionen,
  // 	  * die bei der Kollisionserkennung benötigt werden.
  // 	  \author Jan Bender
  // 	  */
  // 	class CDMath
  // 	{
  // 	public:
  // 		static bool sameSide (const Vector3D &p1, const Vector3D &p2, const Vector3D &a, const Vector3D &b);
  // 		static bool pointInTriangle(const Vector3D &p, const Vector3D &a, const Vector3D &b, const Vector3D &c);
  // 		static Real intersectionEdgeTriangle (const Vector3D &e1, const Vector3D &e2, const Vector3D &a, const Vector3D &b, const Vector3D &c, HesseNormalForm *hnf, Vector3D &iPoint);
  // 		static bool distancePointEdge (const Vector3D &p, const Vector3D &e1, const Vector3D &e2, Real & dist, Vector3D &l);
  // 		static bool distancePointEdge2 (const Vector3D &p, const Vector3D &e1, const Vector3D &e2, Real & dist, Vector3D &l);
  // 		static Real distanceEdgeEdge (Vector3D *a1, Vector3D *b1, Vector3D *a2, Vector3D *b2, Vector3D &np1, Vector3D &np2, bool &vv);
  // 		static int lineSegmentIntersection2D (Vector2D *a, Vector2D *b, Vector2D *c, Vector2D *d, Vector2D &intersection);
  // 	};
}
