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
#include <core/Object.h>
#include <map>


NS_BEGIN(CORE_NAMESPACE)
class Type;
template<typename T> const Type *  type_of();
  /**
   * \brief Multiton. a class which manages unique instances for objects.  works with the type system.
   */
  template<typename SuperClass=Object>
  class Multiton {
public:
    typedef SuperClass * ObjectInstance;
    typedef const Type * ObjectType;

private:
    std::map<ObjectType, ObjectInstance> registeredObjects;
public:

    ~Multiton(){
    /*  for(auto i : registeredObjects) {
        delete i.second;
      };*/
      for(auto it = registeredObjects.begin(); it!=registeredObjects.end();it++){
        delete (*it).second;
      }
      registeredObjects.clear();
    }

    ObjectInstance request(ObjectType type){
      auto it = registeredObjects.find(type);
      if(it==registeredObjects.end()) return 0;
      return it->second;
    }
    template<typename T> T* request(){
      return dynamic_cast<T*>(request(NS(CORE_NAMESPACE)::type_of<T>()));
    }

    bool registerType(ObjectInstance object){
      if(request(object->getType())) return false;
      registeredObjects[object->getType()]=object;
      onObjectRegistered(object);
      return true;
    }

    template<typename T>
    bool registerType(std::function<T*()>  constructor){
      if(request<T>()) return false;
      return registerType(constructor());
    }

    template<typename T>
    bool registerType(){
      return registerType<T>([] (){return new T(); });
    }

    template<typename T>
    T* require(std::function<T*()> constructor){
      auto result = request<T>();
      if(!result) {
        registerType(constructor);
        result =request<T>();
      }
      return dynamic_cast<T*>(result);
    };

    template<typename T>
    T * require(){
      return require<T>([] (){return new T(); });
    }

protected:
    virtual void onObjectRegistered(ObjectInstance instance){}

  };
NS_END(CORE_NAMESPACE)
