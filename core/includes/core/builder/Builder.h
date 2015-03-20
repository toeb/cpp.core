#pragma once
#include <core/core.h>

#include <core/template/not_void.h>

NS_BEGIN(CORE_NAMESPACE)
  /*
    Using Builders. Builders allow for a fluent way to build Tree structures with 
    Context Sensitivety

    You can define builders a type hierarchy and for associations

    Use the BUILDER and CHILD_BUILDER macros
  */

// default parent type is void
#define BUILDER(TYPE,PARENT)\
  template<typename TDerived, typename TParentBuilder>\
  struct Builder<TYPE,TDerived, TParentBuilder> : public Builder<PARENT,TDerived, TParentBuilder>


#define CHILD_BUILDER(NAME)\
  typedef_template_as DS_CONCAT(NAME,Type);\
  template<typename... TArgs>\
  Builder< typename DS_CONCAT(NAME,Type), typename DS_CONCAT(NAME,Type), builder_type> NAME (TArgs... args){\
    auto b =  child_builder< typename DS_CONCAT(NAME, Type)>(*this, args...); \
    b._callback = [=](std::shared_ptr<DS_CONCAT(NAME,Type)> value){this->NAME##Complete(value);};\
    return b;\
  }\
  void NAME##Complete(std::shared_ptr< typename DS_CONCAT(NAME, Type)> value)



struct DefaultBuilder{
  typedef DefaultBuilder builder_type;
};
  // unspecialized Builder class
  template<typename TCurrent, typename TDerived = TCurrent, typename TParentBuilder = void>
  struct Builder:public DefaultBuilder{

  public:
      typedef Builder<TDerived,TDerived,TParentBuilder> builder_type;
  };



  template<typename TDerived, typename TParentBuilder>
  struct Builder < void, TDerived, TParentBuilder > :public DefaultBuilder{
public:
    typedef TDerived element_type;

    typedef std::shared_ptr<element_type> element_ptr;
    typedef element_type & element_ref;
    typedef Builder<TDerived, TDerived, TParentBuilder> builder_type;

    //typedef builder_type & builder_ref;
    typedef TParentBuilder parent_builder_type;
    //typedef parent_builder_type & parent_builder_ref;
    typedef std::shared_ptr<parent_builder_type> parent_builder_ptr;

    template<typename = void>
    builder_type builder(){ return *(static_cast<builder_type*>(this)); }

    template<typename... TArgs>
    builder_type operator()(TArgs... args){
      return construct();
    }

    template<typename... TArgs>
    builder_type construct(TArgs && ...  args){
      _element = std::make_shared<TDerived, TArgs...>(args...);
      return builder();
    }

    virtual ~Builder(){  }
    Builder(){  }
  public:

    template<typename T = TParentBuilder>
    typename std::enable_if<!std::is_same<T, void>::value, T>::type
      end(){
      if (_callback) _callback(_element);

      return _parent.value;
    }

    template<typename T = TParentBuilder>
    typename std::enable_if< std::is_same<T, void>::value, element_ptr>::type
      end(){
      return _element;
    }

    void setElement(element_ptr value){
      _element = value;
    }

    element_ref element(){
      if (!_element){
        throw std::exception();//("cannot change element because it was not constructed yet, call builder.construct() first");
      }

      return *_element.get();
    }


    
    element_ptr ptr(){
      return _element;
    }
  public:
    not_void<TParentBuilder> _parent;
    std::function<void(element_ptr)> _callback;
  private:
    element_ptr _element;
  };

  template<typename TChild, typename TParentBuilder, typename... TArgs>
  Builder<TChild, TChild, TParentBuilder> child_builder(TParentBuilder parentBuilder, TArgs... args){
    Builder<TChild, TChild, TParentBuilder> builder;
    builder._parent.value = parentBuilder;
    builder.construct(args...);
    return builder;
  }



  template<typename T, typename... TArgs>
  Builder<T> build_construct(TArgs... args){
    Builder<T, T, void> builder;
    return builder.construct(args...);
  }

  template<typename T>
  Builder<T> build(std::shared_ptr<T> existing){
    Builder<T, T, void> builder;
    builder.setElement(existing);
    return builder;
  }

NS_END(CORE_NAMESPACE)

