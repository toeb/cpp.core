#pragma once

namespace nspace{
  namespace math{
    namespace operation{
      namespace scalar{
        namespace opcodes{
          enum OperationCodes{
            Absolute,
            Addition,
            ArcusCosinus,
            ArcusSinus,
            ArcusTangens,
            ArcusTangens2,
            Cosinus,
            Division,
            Identity,
            Maximum,
            Minimum,
            Multiplication,
            Reciprocal,
            Signum,
            Sinus,
            SquareRoot,
            Subtraction,
            Tangens,
            Zero,
            EulersNumber,
            Pi,
            SquareRootOfTwo
          };
        }
      }
    }
    typedef nspace::math::operation::scalar::opcodes::OperationCodes OperationCode;
  }
}
