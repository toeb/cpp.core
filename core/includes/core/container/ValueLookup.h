#pragma once
#include <core/core.h>
#include <core/container/Set.h>

NS_BEGIN(CORE_NAMESPACE)
  // struct which combines a void pointer and a name
  struct Entry{
    void * value;
    std::string name;
    Entry():value(0),name(""){}
  };

  //a value lookup which has easy to use methods for getting and setting / iterating the values.
  class ValueLookup{
  private:
    Set<Entry*> _entries;
  public:
    // returns the immutable set of entries
    const Set<Entry*> & entries()const;
    template<typename T> T operator()(const std::string & valuename);
    //returns true if a value with the name exists  also result will be assigned the value
    template<typename T> bool get(T & result, const std::string & valuename);
    // returns the named value . if value does not exist the default (T()) is returned (thus T needs to have a default constructor)
    template<typename T> T get(const std::string & value);
    // returns the pointer to the value named valuename
    template<typename T> T * getPointer(const std::string & valuename);
    // sets the value named "valuename" to the value value.  (hihi... value)
    template<typename T> void set(const std::string & valuename,T value);
    // returns true if value named "valuename" exists (but is not necessarily set) (see hasValue)
    bool has(const std::string & valuename)const;
    // returns true if value named "valuename" exists and has a value
    bool hasValue(const std::string & valuename)const;
  private:
    // returns the entry by name or null
    Entry * entry(const std::string & name);
    // readonly access to entry by name
    const Entry * entry(const std::string & name)const;
    // returns entry by name. creating it if it does not exist already
    Entry * require(const std::string & name);
  };

  //Implementation of templated functions

  template<typename T>
  T ValueLookup::operator()(const std::string & parametername){
    return this->get<T>(parametername);
  }

  //returns true if parameter hasValue
  template<typename T>
  bool ValueLookup::get(T & result, const std::string & parametername){
    if(!hasValue(parametername))return false;
    result = get<T>(parametername);
    return true;
  }

  template<typename T>
  T ValueLookup::get(const std::string & parametername){
    T* result = getPointer<T>(parametername);
    //return default value
    if(!result)return T();
    return *result;
  }
  template<typename T>
  T * ValueLookup::getPointer(const std::string & parametername){
    if(!hasValue(parametername))return 0;
    Entry * currentEntry = entry(parametername);
    T*result=0;
    result = static_cast<T*>(currentEntry->value);
    return result;
  }

  template<typename T>
  void ValueLookup::set(const std::string & parametername,T value){
    Entry * entry = _entries.first([parametername](Entry* entry){return entry->name == parametername;});
    if(!entry){
      entry = new Entry;
      entry->name = parametername;
      _entries.add(entry);
    }
    if(!entry->value)entry->value = new T();
    *static_cast<T*>(entry->value) = value;
  }
NS_END(CORE_NAMESPACE)

