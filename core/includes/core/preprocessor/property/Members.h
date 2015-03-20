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

/**
 * \file  src\core\Members.h
 *
 * \brief Declares Macros for defining standard Members.
 */
#pragma once
#include <core/core.h>


#include <memory>
#include <core/patterns/StaticInitializer.h>
// helper macros needed for MODIFIER(x)
#define _MODIFIER_public public:
#define _MODIFIER_private private:
#define _MODIFIER_protected protected:
#define _MODIFIER_

/**
 * \brief returns the modifier specfied by x and appending a :
 *        if x is not empty MODIFIER(public) -->
 *        public: MODIFIER(private) --> private:
 *        MODIFIER() -->
 *
 * \param x The void to process.
 */
#define MODIFIER(x) _MODIFIER_ ## x

/**
 * \brief macro for defining the name of a field (member variable) (SomeName --> _SomeName)
 *
 * \param NAME  The name.
 */
#define FIELDNAME(NAME) _ ## NAME


/**
 * \brief macro for get method (SomeName --> getSomeName)
 *
 * \param NAME  The name.
 */
#define GETMETHOD(NAME) get ## NAME

/**
 * \brief macro for set method (SomeName --> setSomeName)
 *
 * \param NAME  The name.
 */
#define SETMETHOD(NAME) set ## NAME

/**
 * \brief  defines a field named <NAME> of type <TYPE> in a class/struct which is private by
 *         default FIELD(int, number) --> private: int number;
 *        remark:  actually the expansion will result in: private: public: int number;
 *
 * \param TYPE      The type.
 * \param NAME      The name.
 * \param _MODIFIER The modifier.
 */
#define FIELD(TYPE,NAME,_MODIFIER) \
private: \
  MODIFIER(_MODIFIER) TYPE NAME;

/**
 * \brief defines a getter method for a property name <NAME> of type <TYPE> which is public by
 *        default GET(int, Number) --> public: inline int getNumber()const GET(int, Number,
 *        protected) --> protected: inline int getNumber()const.
 *
 * \param TYPE      The type.
 * \param NAME      The name.
 * \param _MODIFIER The modifier.
 */
#define GET(TYPE,NAME,_MODIFIER) public:  MODIFIER(_MODIFIER) inline TYPE GETMETHOD(NAME) () const

/**
 * \brief defines a setter method for a property name <NAME> of type <TYPE> which is public by
 *        default SET(int, Number) --> public: inline void setNumber(int value)
 *        SET(int, Number, protected) --> protected: inline void setNumber(int value)
 *
 * \param TYPE      The type.
 * \param NAME      The name.
 * \param _MODIFIER The modifier.
 */
#define SET(TYPE,NAME,_MODIFIER) public: MODIFIER(_MODIFIER) inline void SETMETHOD(NAME) (TYPE value)

//#define FIELD(MODIFIER, TYPE,NAME) MODIFIER: TYPE FIELDNAME(NAME);

/**
 * \brief declares the default setter method (default: public) allows insertion of code before the
 *        fields value is returned.
 *
 * \param TYPE      The type.
 * \param NAME      The name.
 * \param _MODIFIER The modifier.
 * \param BEFOREGET The beforeget.
 */
#define GETTER(TYPE,NAME,_MODIFIER,BEFOREGET) GET(TYPE,NAME,_MODIFIER){BEFOREGET; return FIELDNAME(NAME); }

/**
 * \brief declares the default getter method allows insertion of code before and after th value of
 *        the field is set.
 *
 * \param TYPE      The type.
 * \param NAME      The name.
 * \param _MODIFIER The modifier.
 * \param BEFORESET The beforeset.
 * \param AFTERSET  The afterset.
 */
#define SETTER(TYPE,NAME,_MODIFIER,BEFORESET,AFTERSET) SET(TYPE,NAME,_MODIFIER){BEFORESET; FIELDNAME(NAME) = value; AFTERSET; }

/**
 * \brief BASIC_PROPERTY - defines a property which consists of a private field named _<NAME> and a
 *        getter and setter method which are public by default it is also possible to inject code
 *        in get method as well as before and after the private field was changed
 *        BASIC_PROPERTY(std::string, LastName) -->  private: std::string _LastName;
 *                                         public: inline std::string getLastName()const{ return
 *                                         _LastName; }
 *                                         public: inline void setLastName(std::string value){
 *                                         _LastName=value; }
 *
 *        BASIC_PROPERTY(int, Num,protected,
 *        std::cout<<"getting Num"<<std::endl, std::cout << "setting Num" << std::endl, std::cout << "Num was set to " << value << std::endl) -->
 *                   private: int _Num;
 *                   public: inline int getNum()const{
 *                     std::cout << "getting Num" << std::endl;
 *                     return _Num;
 *                   }
 *                   public: inline void setNum(int value){
 *                     std::cout << "setting Num" << std::endl;
 *                     _Num = value;
 *                     std::cout << "Num was set to " << value << std::endl;
 *                   }
 *        which can then be called given: _Num =0;
 *        object.setNum(3);
 *        object.getNum();
 *        --> output   setting Num
 *                     Num was set to 3 getting Num.
 *
 * \param TYPE      The type of the property.
 * \param NAME      The name of the property.
 * \param _MODIFIER The modifier of the accessor methods.
 * \param BEFOREGET The code executed before get.
 * \param BEFORESET The code executed before set.
 * \param AFTERSET  The code executed after set.
 */
#define BASIC_PROPERTY(TYPE,NAME,_MODIFIER, BEFOREGET, BEFORESET, AFTERSET) \
  FIELD(TYPE,FIELDNAME(NAME),private) \
  GETTER(TYPE,NAME,_MODIFIER,BEFOREGET) \
  SETTER(TYPE,NAME,_MODIFIER,BEFORESET,AFTERSET)

/**
 * \brief defines a reference accessor of type <TYPE> & which is non const and public by default
 *        REF(std::string, FirstName) --> public: inline std::string  & FirstName()
 *        REF(std::string, FirstName, const, protected) --> protected: inline const std::string &
 *        FirstName()const.
 *
 * \param TYPE      The type.
 * \param NAME      The name.
 * \param CONST     The constant.
 * \param _MODIFIER The modifier.
 */
#define REF(TYPE,NAME,CONST,_MODIFIER) public: MODIFIER(_MODIFIER) inline CONST TYPE & NAME() CONST

/**
 * \brief A macro that defines readonly reference.
 *
 * \param MODIFIER  The modifier.
 * \param TYPE      The type.
 * \param NAME      The name.
 */
#define READONLY_REFERENCE(MODIFIER, TYPE,NAME) MODIFIER : inline const TYPE &NAME() const {return FIELDNAME(NAME); }

/**
 * \brief A macro that defines a reference.
 *
 * \param MODIFIER  The modifier.
 * \param TYPE      The type.
 * \param NAME      The name.
 */
#define REFERENCE(MODIFIER,TYPE,NAME) MODIFIER : inline TYPE &NAME(){return FIELDNAME(NAME); }

/**
 * \brief A macro that defines the modifiable and readonly references.
 *
 * \param MODIFIER  The modifier.
 * \param TYPE      The type.
 * \param NAME      The name.
 */
#define REFERENCES(MODIFIER,TYPE,NAME) REFERENCE(MODIFIER, TYPE,NAME); READONLY_REFERENCE(MODIFIER,TYPE,NAME);

/**
 * \brief A macro that defines field reference.
 *
 * \param MODIFIER  The modifier.
 * \param TYPE      The type.
 * \param NAME      The name.
 */
#define FIELD_REFERENCE(MODIFIER,TYPE,NAME) FIELD(TYPE,FIELDNAME(NAME),private) REFERENCES(MODIFIER,TYPE,NAME);

/**
 * \brief A macro that defines public field reference.
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 */
#define PUBLIC_FIELD_REFERENCE(TYPE,NAME) FIELD_REFERENCE(public,TYPE,NAME)

/**
 * \brief A macro that defines readonly simple property.
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 */
#define READONLY_SIMPLE_PROPERTY(TYPE,NAME) \
  FIELD(TYPE,FIELDNAME(NAME),private); \
  GETTER(TYPE,NAME,public,);

/**
 * \brief A macro that defines readonly property.
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 */
#define READONLY_PROPERTY(TYPE,NAME) \
  READONLY_REFERENCE(public,TYPE,NAME) \
  READONLY_SIMPLE_PROPERTY(TYPE,NAME)

/**
 * \brief A macro that defines itemaddmethodname.
 *
 * \param NAME  The name.
 */
#define ITEMADDMETHODNAME(NAME) onItemAddedTo ## NAME

/**
 * \brief A macro that defines itemremovemethodname.
 *
 * \param NAME  The name.
 */
#define ITEMREMOVEMETHODNAME(NAME) onItemRemovedFrom ## NAME

/**
 * \brief A macro that defines item added.
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 */
#define itemAdded(TYPE,NAME) ITEMADDMETHODNAME(NAME) (TYPE  item)

/**
 * \brief A macro that defines item removed.
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 */
#define itemRemoved(TYPE,NAME) ITEMREMOVEMETHODNAME(NAME) (TYPE  item)

/**
 * \brief creates a set of type TYPE in the current class allows public reference acces to the
 *        field. adds an observer to the set which causses the code blocks in ONADD and ONREMOVE to
 *        be called whenever an element is added or removed
 *        e.g.
 *         class TestClass{
 *           PROPERTYSET(int,Numbers,{cout
 *           << item << " added"<<endl;}, {cout << item << " removed" <<endl;});
 *         };
 *        int main(){
 *         TestClass c;
 *         c.Numbers().add(2);
 *         c.Numbers().add(3);
 *         c.Numbers().add(2);
 *         c.Numbers().remove(3);
 *         c.Numbers().remove(3);
 *         c.Numbers().remove(2);
 *        }
 *        this code would result in following output 2 added 3 added 3 removed 2 removed.
 *
 * \param TYPE      The type.
 * \param NAME      The name.
 * \param ONADD     The onadd.
 * \param ONREMOVE  The onremove.
 */
#define PROPERTYSET(TYPE,NAME, ONADD, ONREMOVE) \
  FIELD(NS(CORE_NAMESPACE)::Set<TYPE >,FIELDNAME(NAME),private); \
private: \
  std::unique_ptr<NS(CORE_NAMESPACE)::ObservableCollection<TYPE >::Observer> _ ## NAME ## Observer; \
  void init ## NAME ## Observer(){ \
    if(!_ ## NAME ## Observer.get()) { \
      _ ## NAME ## Observer.reset(new NS(CORE_NAMESPACE)::ObservableCollection<TYPE >::DelegateObserver( \
                                    [this](NS(CORE_NAMESPACE)::ObservableCollection<TYPE > * sender, TYPE object){ ITEMADDMETHODNAME(NAME) (object); }, \
                                    [this](NS(CORE_NAMESPACE)::ObservableCollection<TYPE > * sender, TYPE object){ ITEMREMOVEMETHODNAME(NAME) (object); } \
                                    )); \
      FIELDNAME(NAME).addObserver(_ ## NAME ## Observer.get()); \
    } \
  } \
  void itemAdded(TYPE,NAME) ONADD; \
  void itemRemoved(TYPE,NAME) ONREMOVE; \
public: \
  const NS(CORE_NAMESPACE)::Set<TYPE > & NAME() const { return FIELDNAME(NAME); } \
  NS(CORE_NAMESPACE)::Set<TYPE > & NAME(){init ## NAME ## Observer(); return FIELDNAME(NAME); } \
private:

/**
 * \brief A macro that defines initializername.
 *
 * \param NAME  The name.
 */
#define INITIALIZERNAME(NAME) __ ## NAME ## Initializer

/**
 * \brief A macro that defines initializerclassname.
 *
 * \param NAME  The name.
 */
#define INITIALIZERCLASSNAME(NAME) __ ## NAME ## Initializer ## Class

/**
 * \brief use inside a class definition.  INITIALIZATIONCODE will be executed every time an object
 *        the class is instanciated.
 *
 * \param NAME                The name.
 * \param INITIALIZATIONCODE  The initializationcode.
 */
#define INITIALIZER(NAME,INITIALIZATIONCODE) \
private: \
  class INITIALIZERCLASSNAME(NAME){ \
public: \
    INITIALIZERCLASSNAME(NAME) (){INITIALIZATIONCODE} \
  }; \
  INITIALIZERCLASSNAME(NAME) INITIALIZERNAME(NAME);

/**
 * \brief use inside a class definition INITIALIZATIONCODE will be executed for this type.  It will
 *        be called when the first object of that type is constructed.
 *
 * \param NAME                The name.
 * \param INITIALIZATIONCODE  The initializationcode.
 */
#define STATIC_INITIALIZER(NAME,INITIALIZATIONCODE) DS_EXECUTE_ONCE(NAME){INITIALIZATIONCODE;}


/**
 * \brief A macro that defines on property changing method name.
 *
 * \param NAME  The name.
 */
#define ON_PROPERTY_CHANGING_METHOD_NAME(NAME)on ## NAME ## Changing

/**
 * \brief the signature of the on changing method (w/o returntype, which is void)
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 */
#define ON_PROPERTY_CHANGING(TYPE,NAME) ON_PROPERTY_CHANGING_METHOD_NAME(NAME) (TYPE oldvalue, TYPE & newvalue, bool & cancel)

/**
 * \brief a nicer to read alias of ON_PROPERTY_CHANGING.
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 */
#define propertyChanging(TYPE,NAME) ON_PROPERTY_CHANGING(TYPE,NAME)

/**
 * \brief A macro that defines extended property.
 *
 * \param TYPE      The type.
 * \param NAME      The name.
 * \param _MODIFIER The modifier.
 * \param BEFOREGET The beforeget.
 * \param BEFORESET The beforeset.
 * \param AFTERSET  The afterset.
 */
#define EXTENDED_PROPERTY(TYPE, NAME,_MODIFIER,BEFOREGET,BEFORESET, AFTERSET) \
  BASIC_PROPERTY(TYPE,NAME,_MODIFIER,BEFOREGET, \
                 BEFORESET; \
                 bool cancel=false; \
                 if(FIELDNAME(NAME)==value) return; \
                 this->ON_PROPERTY_CHANGING_METHOD_NAME(NAME) (FIELDNAME(NAME),value,cancel); \
                 if(cancel) return; \
                 , AFTERSET); \
private: \
  void ON_PROPERTY_CHANGING(TYPE,NAME)

#define EXTENDED_REFERENCE_PROPERTY(MODIFIER,TYPE, NAME) \
MODIFIER: \
  const TYPE &NAME() const {return FIELDNAME(NAME); } \
  TYPE & NAME(){return FIELDNAME(NAME); } \
private:

/**
 * \brief A macro that defines reference property.
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 */
#define REFERENCE_PROPERTY(TYPE, NAME) EXTENDED_REFERENCE_PROPERTY(public,TYPE, NAME)

/**
 * \brief Defines a Simple property
 *
 *        This macro defines a Property in a class generating getter and setter methods as well as
 *        a field of the specified TYPE called _<Name> .  It also checks the value for equality
 *        before changing it (if the oldvalue and new value are equal the set method just returns)
 *        The last statement generated is a method called on<NAME>Changing(<TYPE> oldvalue,<TYPE>
 *        newvalue, bool & cancel)
 *        which the client needs to implement (minimally by adding empty braces)
 *        IMPORTANT :  you can initialize the fields normally in the constructor by writing
 *        :_<Name>(...)
 *         Example 1: PROPERTY(int, NumberOfOrders){}  will create:
 *         - a private int field called _NumberOfOrders
 *         - the getter and setter method int getNumberOfOrders()const, void setNumberOfOrders(int
 *         value)
 *         - the onNumberOfOrdersChanging(...) method
 *         Example 2: PROPERTY(int, NumberOfOrders){
 *           if(newvalue < 3){
 *             cancel = true;
 *             return;
 *           }
 *           std::cout
 *           << "Number of Orders changed from " << oldvalue << " to " << newvalue <<std::endl;
 *         }
 *         this will create the same field and methods as example 1 however it will cancel the
 *         change if the new value is smaller than 3.  if the value is higher than three a string
 *         will be printed e.g: setNumberOfOrders(4) --> "Number of Orders changed from 0 to 4".
 *
 * \param TYPE  The type.
 * \param NAME  The name.
 */
#define SIMPLE_PROPERTY(TYPE, NAME) EXTENDED_PROPERTY(TYPE,NAME,public,,,)
