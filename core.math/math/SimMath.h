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

namespace nspace
{
  //	typedef Vector3D (*rungeKuttaFct)(const Real x, const Vector3D &y, void *obj);

  // 	/** Klasse für Mathematik-Hilfsfunktionen, die für
  // 	  * die Simulation benötigt werden.
  // 	  */
  // 	class SimMath
  // 	{
  // 	public:
  // 		/** Epsilon wird für Tests auf 0 verwendet */
  // 		static Real eps;
  // 		/** Epsilon im Quadrat */
  // 		static Real eps2;
  // 		/** Cash-Karp-Parameter für Embedded Runge-Kutta */
  // 		static Real	a2, a3, a4, a5, a6,
  // 				b21, b31, b32, b41, b42, b43, b51, b52, b53, b54, b61, b62, b63, b64, b65,
  // 				c1, c3, c4, c6, dc1, dc3, dc4, dc5, dc6;
  // /*
  // 		static Vector3D lotpunkt(const Vector3D &p, const Vector3D &v, const Vector3D &s);
  // 		static Matrix3x3 rotationsmatrix (const Vector3D &a, const Real phi);
  // 		static Matrix3x3 orthonormalize (const Matrix3x3 &M);
  // 		static Vector3D computeBoxIntertiaTensor (const Real m, const Real x, const Real y, const Real z);
  // 		static Vector3D computeSphereIntertiaTensor (const Real m, const Real r);
  // 		static int n_over_k (const int n, const int k);
  // 		static Vector3D *localCoordinates (Matrix3x3 *rotationMatrix, Vector3D *centerOfMass, Vector3D *point);
  // 		static Matrix3x3 crossProductMatrix (const Vector3D &r);
  //     static inline void crossProductMatrix(const Vector3D & r, Matrix3x3 & r_star){
  //
  //       r_star(0,0)=0; r_star(0,1)=-r(2); r_star(0,2)=r(1);
  //       r_star(1,0)=r(2); r_star(1,1)=0; r_star(1,2)=-r(0);
  //       r_star(2,0)=-r(1); r_star(2,1)=r(0); r_star(2,2)= 0;
  //     }
  // 		static Vector3D getEulerAngles (const Matrix3x3 & m);
  // 		static Vector3D rungeKutta (rungeKuttaFct f, const Real h, const Real xn, const Vector3D &yn, void *obj, bool &result);
  // 		static Vector3D rungeKutta (rungeKuttaFct f, const Real h, const Vector3D &yn, void *obj, bool &result);
  // 		static Vector3D embeddedRungeKutta (rungeKuttaFct f, const Real h, const Real xn, const Vector3D &yn, Real &error, void *obj, bool &result);
  // 		static Vector3D embeddedRungeKutta (rungeKuttaFct f, const Real h, const Vector3D &yn, Real &error, void *obj, bool &result);
  // 		static Real computeVolume(const Vector3D &a, const Vector3D &b, const Vector3D &c, const Vector3D &d);
  // 		static Real computeVolumeOriented(const Vector3D &a, const Vector3D &b, const Vector3D &c, const Vector3D &d);*/
  // 	};
}
