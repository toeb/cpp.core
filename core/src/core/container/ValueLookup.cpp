#include <core/container/ValueLookup.h>
#include <string>

NS_USE(CORE_NAMESPACE);
using namespace std;

const Set<Entry*> & ValueLookup::entries()const{
  return _entries;
}

bool ValueLookup::has(const std::string & parametername)const{
  return entry(parametername)!=0;
}
bool ValueLookup::hasValue(const std::string & parametername)const{
  const Entry * currentEntry = entry(parametername);
  if(!currentEntry)return false;
  if(!currentEntry->value)return false;
  return true;
}
Entry * ValueLookup::entry(const std::string & name){
  Entry * entry = _entries.first([name](Entry* entry){return entry->name == name;});
  return entry;
}
const Entry * ValueLookup::entry(const std::string & name)const{
  Entry * entry = _entries.first([name](Entry* entry){return entry->name == name;});
  return entry;
}

Entry * ValueLookup::require(const std::string & name){
  Entry * currentEntry = entry(name);
  if(!currentEntry){
    currentEntry = new Entry;
    currentEntry->name = name;
    _entries.add(currentEntry);
  }
  return currentEntry;
}