/**
 * Copyright (C) 2013 Tobias P. Becker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the  rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * More information at: https://dslib.assembla.com/
 *
 */
#pragma once

#include <config.h>
namespace nspace {

  /**
   * \brief Values that represent DimensionTraits.
   *        a dimension can be unknown
   *        fixed in size
   *        dynamic in size
   *        or infinite (ie. functions that are calculate when called)
   */
  enum DimensionTraits {
    ///< An enum constant representing the unknown dimension type
    Unknown,
    ///< An enum constant representing fixed at compile time dimension option
    Fixed,
    ///< An enum constant representing the dynamic dimension option (dimension may vary)
    Dynamic,
    ///< An enum constant representing the infinite dimension option
    Infinite,
    ///< An enum constant representing the fixed at runtime dimension option
    FixedAtRuntime
  };
}