#pragma once
#include <core/core.h>

#include <core/Object.h>
#include <string>

NS_BEGIN(CORE_NAMESPACE)
  // a base class for objects that need to be named
  class NamedObject  : public virtual Object{
    //reflect_type_declaration(NS(CORE_NAMESPACE)::NamedObject);
  private:
    // the name field
    std::string * _name;
  public:
    // the default name. (if a named object does not have a name set it will be returned)
    static const std::string & DefaultName();
    // constructor accepting a string name
    NamedObject(const std::string & name);
    // default constructor
    NamedObject();
    // default destructor
    virtual ~NamedObject();
    // returns the name of this object
    const std::string & name()const;
    // returns true iff the object has a name
    bool hasName()const;
    // sets the name of this object by reference
    void setName(const std::string & name);
    // sets the name of this object by pointer
    void setName(const std::string * name);
    // equality operator. returns true of this objects name equals the string
    bool operator == (const std::string & str)const;
    // equalitiy operator. returns true if this objects name equals the c string
    bool operator==(const char * str)const;
    // equality operator compares a NamedObject's name to a std::string and returns true iff they are equal
    bool friend operator==(const NamedObject * obj, const std::string & name);
  protected:
    // extension point which is called when the name of this named object changes.  subclasses may override this
    virtual void onNameChanged(const std::string& newName){}
  };

  // method for extracting the name of a named object
  const std::string & name(const Object * object);
  // returns true if the object is a named object and it has a name
  bool hasObjectName(const Object * object);
  // returns truie if object is nameable
  bool isObjectNameable(const Object * object);
  // set the name of the object if it is nameable. returns true if it was successful
  bool setObjectName(Object * object, const std::string &name);
NS_END(CORE_NAMESPACE)

