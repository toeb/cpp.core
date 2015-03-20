#include <core.shim.h>
#include <core/utility/StringTools.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iterator>
#include <cstring>
using namespace std;
NS_USE(CORE_NAMESPACE)::stringtools;


    std::string NS(CORE_NAMESPACE)::stringtools::wstringToString(const wstring & lstring){
      std::stringstream stream;
      for(size_t i=0; i < lstring.size();i++){
        stream<< (char)lstring.at(i);
      }
      return stream.str();
    }
    std::wstring NS(CORE_NAMESPACE)::stringtools::stringToWstring(const string & str){
      std::wstringstream stream;
      for(size_t i=0; i < str.size(); i++){
        stream << (wchar_t)str.at(i);
      }
      return stream.str();
    }

char * NS(CORE_NAMESPACE)::stringtools::c_str(const std::string  & original){
  char *cDocString = new char[original.size()+1]; // +1 to account for \0 byte

  std::strncpy(cDocString, original.c_str(), original.size());
  cDocString[original.size()]=0;// ensure it is null terminated ( if it is not already)
  return cDocString;
}

StringToken::StringToken(std::istream & stream):stream(stream){}
bool StringToken::next(){
  word=stringtools::nextToken(stream);      
  if(word=="")return false;
  return true;
}
StringToken:: operator bool(){
  return stream.good();
}

string NS(CORE_NAMESPACE)::stringtools::nextToken(std::istream & stream){
  static string newline="\n";
  static string empty="";
  bool stop=false;
  while(!stop){
    char c = stream.peek();
    switch(c){        
    case '\n':      
    case '\r':
      stream.ignore();
      return newline;
    case '\t':  
    case ' ':        
      stream.ignore();
      if(!stream)return empty;
      break;
    default:
      stop = true;
      break;
    };
  }
  string tok;
  stream >> tok;
  return tok;

}

std::vector<std::string> NS(CORE_NAMESPACE)::stringtools::split(const std::string & str, const char separator){  
  std::vector<std::string> result;
  std::stringstream stream(str);
  std::string item;
  while(getline(stream,item,separator)){
    result.push_back(item);
  }
  return result;
}
std::vector<std::string> NS(CORE_NAMESPACE)::stringtools::split(istringstream & stream){  
  vector<string> tokens;
  copy(istream_iterator<string>(stream),
    istream_iterator<string>(),
    back_inserter<vector<string> >(tokens));
  return tokens;
}

std::vector<std::string> NS(CORE_NAMESPACE)::stringtools::split(const std::string & str, const std::string & separator){
  std::vector<std::string> parts;
  size_t start = 0, end =0;
  while((end=str.find(separator,start))!= str.npos){
    parts.push_back(str.substr(start,end-start));
    start = end+separator.size();
  }
  parts.push_back(str.substr(start));
  return parts;
}


std::vector<std::string> NS(CORE_NAMESPACE)::stringtools::split(const std::string & str){
  istringstream stream(str);
  return split(stream);
}
std::string NS(CORE_NAMESPACE)::stringtools::trim(std::stringstream & stream){      
  return trim(stream.str());

}


std::string NS(CORE_NAMESPACE)::stringtools::trimFront(const std::string & str){
  size_t front = 0;
  bool isWhitespace;  
  bool allWhitespace=true;
  do{
    isWhitespace=false;
    switch(str[front]){
    case ' ':
    case '\t':
    case '\n':
    case '\r':
      isWhitespace=true;

      break;
    default:
      allWhitespace = false;
    } 

    front++;
  }
  while(isWhitespace && front < str.size());
  if(allWhitespace)return "";
  return str.substr(front-1);
}


std::string NS(CORE_NAMESPACE)::stringtools::trimBack(const std::string & str){

  int back=str.size()-1;
  if(back < 0)return "";
  bool isWhitespace; 

  bool allWhitespace=true;
  do{
    isWhitespace=false;
    switch(str[back]){
    case ' ':
    case '\t':
    case '\n':
    case '\r':
      isWhitespace=true;
      break;
    default:
      allWhitespace = false;
    } 

    back--;
  }while(isWhitespace && back >=0); 

  if(allWhitespace)return "";
  return str.substr(0,back+2);
}

std::string NS(CORE_NAMESPACE)::stringtools::trim(const std::string & str){
  return trimFront(trimBack(str));

}
bool NS(CORE_NAMESPACE)::stringtools::startsWith(const std::string & subject,const std::string & what){
  if(subject.size()<what.size())return false; 
  for (size_t i = 0; i < what.size(); i++){
    if(what[i]!=subject[i])return false;
  };
  return true;
}


bool NS(CORE_NAMESPACE)::stringtools::endsWithIgnoreCase(const std::string &subject, const std::string & what){
  return endsWith(toLowerCase(subject),toLowerCase(what));
}
bool NS(CORE_NAMESPACE)::stringtools::endsWith(const std::string & subject, const std::string & what){
  auto str = subject;
  auto obj = what;
  std::reverse(begin(str),end(str));
  std::reverse(begin(obj),end(obj));
  return startsWith(str,obj);
}

bool NS(CORE_NAMESPACE)::stringtools::startWithIgnoreCase(const std::string &subject, const std::string & what){
  auto s =toLowerCase(subject);
  auto w = toLowerCase(what);
  return startsWith(s,w);
}


std::string NS(CORE_NAMESPACE)::stringtools::toLowerCase(const std::string & original){
  std::string data = original;
  std::transform(data.begin(), data.end(), data.begin(), ::tolower);
  return data;
}
std::string NS(CORE_NAMESPACE)::stringtools::toUpperCase(const std::string & original){
  std::string data = original;
  std::transform(data.begin(), data.end(), data.begin(), ::toupper);
  return data;
}

bool NS(CORE_NAMESPACE)::stringtools::contains(const std::string & original, const std::string & search){
  if( original.find(search) > original.size())return false;
  return true;
}
bool NS(CORE_NAMESPACE)::stringtools:: containsIgnoreCase(const std::string & original, const std::string & search){
  string ori = toLowerCase(original);
  string src = toLowerCase(search);
  if( ori.find(src) > ori.size())return false;
  return true;
}

std::string NS(CORE_NAMESPACE)::stringtools:: operator +(const std::string & a, const std::string & b){
  std::string result = "";
  result.append(a);
  result.append(b);
  return result;
}
std::string NS(CORE_NAMESPACE)::stringtools:: operator +(const std::string &a, const char * b){
  return a+std::string(b);
}
std::string NS(CORE_NAMESPACE)::stringtools::operator +(const char * a, const std::string &b){
  return std::string(a)+b;
}

std::string NS(CORE_NAMESPACE)::stringtools::repeat(const std::string &str, unsigned int n){
  std::stringstream ss;
  for(unsigned int i=0; i < n; i++){
    ss << str;
  }
  return ss.str();
}

std::string NS(CORE_NAMESPACE)::stringtools::replace(std::string  original, const std::string & search, const std::string & replacement){
  if( original.find(search) > original.size())return original;
  return  replace(original.replace(original.find(search), search.size(), replacement),search,replacement);
}

std::string NS(CORE_NAMESPACE)::stringtools::spaces(unsigned int n){
  return repeat(" ",n);
}

