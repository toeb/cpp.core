#pragma once
#include <core/dynamic/dynamic.h>
#include <map>
#include <core/dynamic/DynamicObjectImplemenationBase.h>
NS_BEGIN(CORE_DYNAMIC_NAMESPACE)


class DynamicObjectExpandoImplementation : public DynamicObjectImplementationBase, public std::enable_shared_from_this < DynamicObjectExpandoImplementation > {
  typedef std::map<member_name_type, DynamicObject> member_map_type;

public:
  virtual bool tryGetMemberList(member_list & lst)const override{
    for (auto member : _members){
      lst.push_back(member.first);
    }
    return true;
  };


  // faster insertion from
  //http://stackoverflow.com/questions/97050/stdmap-insert-or-stdmap-find
  virtual bool tryMemberGet(const get_member_context & context, result_type & result)override {
    
    member_map_type::iterator lb = _members.lower_bound(context.name);

    if (lb != _members.end() && !(_members.key_comp()(context.name, lb->first)))
    {
      // key already exists
      // update lb->second if you care to
    }
    else
    {
      // the key does not exist in the map
      // add it to the map
      lb = _members.insert(lb, member_map_type::value_type(context.name, DynamicObject()));    // Use lb as a hint to insert,
      // so it can avoid another lookup
    }
    result.assign(lb->second);


    /* //old implementation of insertion
    if (_members.find(context.name) == std::end(_members)){
      // _members.emplace(std::pair<member_name_type, result_type>(context.name, DynamicObject()));
      _members.insert(std::make_pair(context.name, DynamicObject()));

      //_members[context.name] = DynamicObject();

    }
    result.assign(_members[context.name]);*/
    return true;
  }
  virtual bool tryMemberSet(const set_member_context & context, DynamicObject  value)override {
    _members.insert(std::make_pair(context.name, value));
  //  _members[context.name] = value;
    return true;
  }

  virtual bool tryInvoke(const invoke_context & context, result_type & result, const argument_list_type && arguments) {
    return false;
  }

  //  private:
  member_map_type _members;
};
NS_END(CORE_DYNAMIC_NAMESPACE)

