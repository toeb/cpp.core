#pragma once
#include <core/core.h>

NS_BEGIN(CORE_NAMESPACE)
  //this file contains static functions for discriminating signatures of overloaded functions with up to + 9 arguments
  // discriminators for 0 arguments
  template<typename Class, typename ReturnType>
  inline auto const_signature(ReturnType(Class::*signature_ptr)()const)->ReturnType(Class::*)()const{
    return signature_ptr;
  }

  template<typename Class, typename ReturnType>
  inline auto signature(ReturnType(Class::*signature_ptr)())->ReturnType(Class::*)(){
    return signature_ptr;
  }

  template<typename ReturnType>
  inline auto static_signature(ReturnType(*signature_ptr)())->ReturnType(*)(){
    return signature_ptr;
  }

  // discriminators for 1 arguments
  template<typename T0, typename Class, typename ReturnType>
  inline auto const_signature(ReturnType(Class::*signature_ptr)(T0)const)->ReturnType(Class::*)(T0)const{
    return signature_ptr;
  }

  template<typename T0, typename Class, typename ReturnType>
  inline auto signature(ReturnType(Class::*signature_ptr)(T0))->ReturnType(Class::*)(T0){
    return signature_ptr;
  }

  template<typename T0, typename ReturnType>
  inline auto static_signature(ReturnType(*signature_ptr)(T0))->ReturnType(*)(T0){
    return signature_ptr;
  }

  // discriminators for 2 arguments
  template<typename T0, typename T1, typename Class, typename ReturnType>
  inline auto const_signature(ReturnType(Class::*signature_ptr)(T0, T1)const)->ReturnType(Class::*)(T0, T1)const{
    return signature_ptr;
  }

  template<typename T0, typename T1, typename Class, typename ReturnType>
  inline auto signature(ReturnType(Class::*signature_ptr)(T0, T1))->ReturnType(Class::*)(T0, T1){
    return signature_ptr;
  }

  template<typename T0, typename T1, typename ReturnType>
  inline auto static_signature(ReturnType(*signature_ptr)(T0, T1))->ReturnType(*)(T0, T1){
    return signature_ptr;
  }

  // discriminators for 3 arguments
  template<typename T0, typename T1, typename T2, typename Class, typename ReturnType>
  inline auto const_signature(ReturnType(Class::*signature_ptr)(T0, T1, T2)const)->ReturnType(Class::*)(T0, T1, T2)const{
    return signature_ptr;
  }

  template<typename T0, typename T1, typename T2, typename Class, typename ReturnType>
  inline auto signature(ReturnType(Class::*signature_ptr)(T0, T1, T2))->ReturnType(Class::*)(T0, T1, T2){
    return signature_ptr;
  }

  template<typename T0, typename T1, typename T2, typename ReturnType>
  inline auto static_signature(ReturnType(*signature_ptr)(T0, T1, T2))->ReturnType(*)(T0, T1, T2){
    return signature_ptr;
  }

  // discriminators for 4 arguments
  template<typename T0, typename T1, typename T2, typename T3, typename Class, typename ReturnType>
  inline auto const_signature(ReturnType(Class::*signature_ptr)(T0, T1, T2, T3)const)->ReturnType(Class::*)(T0, T1, T2, T3)const{
    return signature_ptr;
  }

  template<typename T0, typename T1, typename T2, typename T3, typename Class, typename ReturnType>
  inline auto signature(ReturnType(Class::*signature_ptr)(T0, T1, T2, T3))->ReturnType(Class::*)(T0, T1, T2, T3){
    return signature_ptr;
  }

  template<typename T0, typename T1, typename T2, typename T3, typename ReturnType>
  inline auto static_signature(ReturnType(*signature_ptr)(T0, T1, T2, T3))->ReturnType(*)(T0, T1, T2, T3){
    return signature_ptr;
  }

  // discriminators for 5 arguments
  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename Class, typename ReturnType>
  inline auto const_signature(ReturnType(Class::*signature_ptr)(T0, T1, T2, T3, T4)const)->ReturnType(Class::*)(T0, T1, T2, T3, T4)const{
    return signature_ptr;
  }

  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename Class, typename ReturnType>
  inline auto signature(ReturnType(Class::*signature_ptr)(T0, T1, T2, T3, T4))->ReturnType(Class::*)(T0, T1, T2, T3, T4){
    return signature_ptr;
  }

  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename ReturnType>
  inline auto static_signature(ReturnType(*signature_ptr)(T0, T1, T2, T3, T4))->ReturnType(*)(T0, T1, T2, T3, T4){
    return signature_ptr;
  }

  // discriminators for 6 arguments
  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename Class, typename ReturnType>
  inline auto const_signature(ReturnType(Class::*signature_ptr)(T0, T1, T2, T3, T4, T5)const)->ReturnType(Class::*)(T0, T1, T2, T3, T4, T5)const{
    return signature_ptr;
  }

  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename Class, typename ReturnType>
  inline auto signature(ReturnType(Class::*signature_ptr)(T0, T1, T2, T3, T4, T5))->ReturnType(Class::*)(T0, T1, T2, T3, T4, T5){
    return signature_ptr;
  }

  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename ReturnType>
  inline auto static_signature(ReturnType(*signature_ptr)(T0, T1, T2, T3, T4, T5))->ReturnType(*)(T0, T1, T2, T3, T4, T5){
    return signature_ptr;
  }

  // discriminators for 7 arguments
  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename Class, typename ReturnType>
  inline auto const_signature(ReturnType(Class::*signature_ptr)(T0, T1, T2, T3, T4, T5, T6)const)->ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6)const{
    return signature_ptr;
  }

  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename Class, typename ReturnType>
  inline auto signature(ReturnType(Class::*signature_ptr)(T0, T1, T2, T3, T4, T5, T6))->ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6){
    return signature_ptr;
  }

  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename ReturnType>
  inline auto static_signature(ReturnType(*signature_ptr)(T0, T1, T2, T3, T4, T5, T6))->ReturnType(*)(T0, T1, T2, T3, T4, T5, T6){
    return signature_ptr;
  }

  // discriminators for 8 arguments
  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename Class, typename ReturnType>
  inline auto const_signature(ReturnType(Class::*signature_ptr)(T0, T1, T2, T3, T4, T5, T6, T7)const)->ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7)const{
    return signature_ptr;
  }

  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename Class, typename ReturnType>
  inline auto signature(ReturnType(Class::*signature_ptr)(T0, T1, T2, T3, T4, T5, T6, T7))->ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7){
    return signature_ptr;
  }

  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename ReturnType>
  inline auto static_signature(ReturnType(*signature_ptr)(T0, T1, T2, T3, T4, T5, T6, T7))->ReturnType(*)(T0, T1, T2, T3, T4, T5, T6, T7){
    return signature_ptr;
  }

  // discriminators for 9 arguments
  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename Class, typename ReturnType>
  inline auto const_signature(ReturnType(Class::*signature_ptr)(T0, T1, T2, T3, T4, T5, T6, T7, T8)const)->ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7, T8)const{
    return signature_ptr;
  }

  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename Class, typename ReturnType>
  inline auto signature(ReturnType(Class::*signature_ptr)(T0, T1, T2, T3, T4, T5, T6, T7, T8))->ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7, T8){
    return signature_ptr;
  }

  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename ReturnType>
  inline auto static_signature(ReturnType(*signature_ptr)(T0, T1, T2, T3, T4, T5, T6, T7, T8))->ReturnType(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8){
    return signature_ptr;
  }

NS_END(CORE_NAMESPACE)
