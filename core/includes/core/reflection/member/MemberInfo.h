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
#include <core/core.h>
#include <core/reflection/type/TypeInfo.h>
#include <core/reflection/attribute/Attribute.h>

NS_BEGIN(CORE_NAMESPACE)
  enum AccessModifierEnum{
    Unknown,
    Private,
    Protected,
    Public
  };

  /**
  * \brief Information about a member.
  *        @TODO remove attributes like description/displayname etc.
  */
  class MemberInfo : public AttributeTarget {    
    // minimally unique name which identifies the meber
    propdef std::string basic_property(Name);    
    property_reference(Name);

    propdef std::string basic_property(FullName);
    property_reference(FullName);

    propdef AccessModifierEnum basic_property(AccessModifier);
    property_reference(AccessModifier);

    propdef const Type * basic_property(OwningType);
  public:
    static bool initializeType();
  protected:
    /**
    * \brief Default constructor.
    */
    MemberInfo();
    MemberInfo(const std::string & name);
    virtual ~MemberInfo();
  };


NS_END(CORE_NAMESPACE)
