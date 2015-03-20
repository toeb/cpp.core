#pragma once
#include <core/core.h>

#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
NS_BEGIN(CORE_NAMESPACE)
  namespace stringtools{
    //concatenates to strings
    std::string operator +(const std::string & a, const std::string & b);
    // concatenates a string and a const char *
    std::string operator +(const std::string & a, const char * b);
    // concatenatesa a string and a const char*
    std::string operator +(const char * a, const std::string & b);
    // concatenates  astring and any type of reference using the << operator
    template<typename T> std::string operator +(const std::string & a, const T & t);
    // concatenates  astring and any type of reference using the << operator
    template<typename T> std::string operator +( const T & t,const std::string & a);
    bool contains(const std::string & original, const std::string & search);
    bool containsIgnoreCase(const std::string & original, const std::string & search);
    std::string toLowerCase(const std::string & original);
    std::string toUpperCase(const std::string & original);
    // replaces the search string in original with replacement string
    std::string replace(std::string original, const std::string & search, const std::string & replacement);
    // generates whitespaces
    std::string spaces(unsigned int n);
    // repeats str n times
    std::string repeat(const std::string & str, unsigned int n );
    // trims the stream and retruns the string
    std::string trim(std::stringstream & stream);
    std::string trim(const std::string & str);
    std::string trimFront(const std::string & str);
    std::string trimBack(const std::string & str);
    bool startsWith(const std::string & subject,const std::string & what);
    bool endsWith(const std::string & subject, const std::string & what);
    bool startWithIgnoreCase(const std::string &subject, const std::string & what);
    bool endsWithIgnoreCase(const std::string &subject, const std::string & what);
    std::vector<std::string> split(const std::string & str, const std::string & separator);
    std::vector<std::string> split(const std::string & str, const char separator);
    std::vector<std::string> split(const std::string & str);
    std::vector<std::string> split(std::istringstream & stream);
    //returns the next token in stream - this may be a word (delimited by whitespace) or a newline.  if an empty string "" is returned the stream is empty
    std::string nextToken(std::istream & stream);
    
    std::string wstringToString(const std::wstring & lstring);
    std::wstring stringToWstring(const std::string & string);

    // creates a null terminated copy of the original string on heap
    char * c_str(const std::string  & original);
    


   


    // struct for tokenizing a stream (  while(token.next()){do eomething}
    struct StringToken{
      StringToken(std::istream & stream);
      std::istream & stream;
      std::string word;
      bool next();
      operator bool();   
    };

  }//stringtools

  
    //specialize using macro or: template<> double Parse<double>::operation(const std::string  &word){}
    //
    template<typename T>
    struct Parse{
      static inline bool operation(T & value, const std::string & word){
        std::istringstream stream(word);
        stream>>value;
        return true;
      }
    };
    /**
    * \brief A macro that helps to specialize Parse.
    *
    * \param TYPE  The type.
    */
#define SPECIALIZE_PARSE(TYPE) template<> bool Parse<TYPE>::operation(TYPE & value, const std::string  &word)
     /**
     * \brief Parses a T from the string and stores it in value. 
     *
     * \tparam  typename T  Type of   t.
     * \param [out]  value The value.
     * \param word            The word.
     *
     * \return  true if it succeeds, false if it fails.
     */
    template<typename T> inline bool parse(T & value, const std::string & word){      
      return Parse<T>::operation(value,word);
    }
    
    /**
     * \brief Parses the given word.  
     *
     * \tparam  typename T  Type of the typename t.
     * \param word  The word.
     *
     * \return  the parse Type.
     */
    template<typename T> inline T parse(const std::string & word){
      T result;
      parse(result,word);
      return result;
    };

    /**
     * \brief reads a word from the stream an tries to parse it.
     *
     * \tparam  typename T  Type of value.
     * \param [out]  value   The value.
     * \param [in]  stream  The stream.
     *
     * \return  true if it succeeds, false if it fails.
     */
    template<typename T> inline bool parseNext(T& value, std::istream & stream){      
      std::string word;
      stream >> word;
      return parse<T>(value,word);      
    }


    template<typename T> inline T parseNext( std::istream & stream){
      T result;
      parseNext(result,stream);
      return result;
    }

    //todo what happens when parse error?

    template<>
    struct Parse<double>{
      static inline bool operation(double & value, const std::string & word){        
        value = std::strtod(word.c_str(),0);
        return true;
      }
    };

    template<>
    struct Parse<unsigned long>{
      static inline bool operation(unsigned long & value, const std::string & word){        
        value = std::strtoul(word.c_str(),0,10);
        return true;
      }
    };
    
    template<>
    struct Parse<long>{
      static inline bool operation(long & value, const std::string & word){        
        value = std::strtol(word.c_str(),0,10);
        return true;
      }
    };

    
    template<>
    struct Parse<int>{
      static inline bool operation( int & value, const std::string & word){     
#pragma warning(suppress:4244)
      value= parse<long>(word);
        return true;
      }
    };


    
    template<>
    struct Parse<short>{
      static inline bool operation( short & value, const std::string & word){     
#pragma warning(suppress:4244)
      value= parse<long>(word);
        return true;
      }
    };


    
    
    template<>
    struct Parse<char>{
      static inline bool operation( char & value, const std::string & word){     
#pragma warning(suppress:4244)
      value= parse<long>(word);
        return true;
      }
    };


    template<>
    struct Parse<unsigned int>{
      static inline bool operation( unsigned int & value, const std::string & word){     
#pragma warning(suppress:4244)
      value= parse<unsigned long>(word);
        return true;
      }
    };
    
    
    template<>
    struct Parse<unsigned short>{
      static inline bool operation( unsigned short & value, const std::string & word){     
#pragma warning(suppress:4244)
      value= parse<unsigned long>(word);
        return true;
      }
    };

    
    template<>
    struct Parse<unsigned char>{
      static inline bool operation( unsigned char & value, const std::string & word){    
#pragma warning(suppress:4244) 
      value= parse<unsigned long>(word);
        return true;
      }
    };

    
    
    template<>
    struct Parse<float>{
      static inline bool operation( float & value, const std::string & word){     
#pragma warning(suppress:4244)
      value= parse<double>(word);
        return true;
      }
    };






NS_END(CORE_NAMESPACE)


//implementation

template<typename T> std::string NS(CORE_NAMESPACE)::stringtools::operator +(const std::string & a, const T & t){
  std::stringstream s;
  s<<a<<t;
  return s.str();
}

template<typename T> std::string NS(CORE_NAMESPACE)::stringtools::operator +( const T & t,const std::string & a){
  return a+t;
}
