
#pragma once
#include <core/core.h>
#include <memory>

NS_BEGIN(CORE_NAMESPACE)
  template<typename Class>
  struct make{
    //construction methods for up to 9 arguments
    //constructor methods for 0 arguments 

    static inline Class * raw(){
      return new Class();
    }

    static inline std::shared_ptr<Class> shared(){
      return std::make_shared<Class>();
    }

    static inline void placement(void * address){
      new (address) Class();
    }

    static inline std::unique_ptr<Class> unique(){
      return std::unique_ptr<Class>( new Class());
    }

    static inline Class * raw_0(){
      return new Class();
    }

    static inline std::shared_ptr<Class> shared_0(){
      return std::make_shared<Class>();
    }

    static inline void placement_0(void * address){
      new (address) Class();
    }

    static inline std::unique_ptr<Class> unique_0(){
      return std::unique_ptr<Class>( new Class());
    }
    //constructor methods for 1 arguments 
    template<typename T0>
    static inline Class * raw(T0 && a0){
      return new Class(a0);
    }
    template<typename T0>
    static inline std::shared_ptr<Class> shared(T0 && a0){
      return std::make_shared<Class>(a0);
    }
    template<typename T0>
    static inline void placement(void * address, T0 && a0){
      new (address) Class(a0);
    }
    template<typename T0>
    static inline std::unique_ptr<Class> unique(T0 && a0){
      return std::unique_ptr<Class>( new Class(a0));
    }
    template<typename T0>
    static inline Class * raw_1(T0 && a0){
      return new Class(a0);
    }
    template<typename T0>
    static inline std::shared_ptr<Class> shared_1(T0 && a0){
      return std::make_shared<Class>(a0);
    }
    template<typename T0>
    static inline void placement_1(void * address, T0 && a0){
      new (address) Class(a0);
    }
    template<typename T0>
    static inline std::unique_ptr<Class> unique_1(T0 && a0){
      return std::unique_ptr<Class>( new Class(a0));
    }
    //constructor methods for 2 arguments 
    template<typename T0, typename T1>
    static inline Class * raw(T0 && a0, T1 && a1){
      return new Class(a0, a1);
    }
    template<typename T0, typename T1>
    static inline std::shared_ptr<Class> shared(T0 && a0, T1 && a1){
      return std::make_shared<Class>(a0, a1);
    }
    template<typename T0, typename T1>
    static inline void placement(void * address, T0 && a0, T1 && a1){
      new (address) Class(a0, a1);
    }
    template<typename T0, typename T1>
    static inline std::unique_ptr<Class> unique(T0 && a0, T1 && a1){
      return std::unique_ptr<Class>( new Class(a0, a1));
    }
    template<typename T0, typename T1>
    static inline Class * raw_2(T0 && a0, T1 && a1){
      return new Class(a0, a1);
    }
    template<typename T0, typename T1>
    static inline std::shared_ptr<Class> shared_2(T0 && a0, T1 && a1){
      return std::make_shared<Class>(a0, a1);
    }
    template<typename T0, typename T1>
    static inline void placement_2(void * address, T0 && a0, T1 && a1){
      new (address) Class(a0, a1);
    }
    template<typename T0, typename T1>
    static inline std::unique_ptr<Class> unique_2(T0 && a0, T1 && a1){
      return std::unique_ptr<Class>( new Class(a0, a1));
    }
    //constructor methods for 3 arguments 
    template<typename T0, typename T1, typename T2>
    static inline Class * raw(T0 && a0, T1 && a1, T2 && a2){
      return new Class(a0, a1, a2);
    }
    template<typename T0, typename T1, typename T2>
    static inline std::shared_ptr<Class> shared(T0 && a0, T1 && a1, T2 && a2){
      return std::make_shared<Class>(a0, a1, a2);
    }
    template<typename T0, typename T1, typename T2>
    static inline void placement(void * address, T0 && a0, T1 && a1, T2 && a2){
      new (address) Class(a0, a1, a2);
    }
    template<typename T0, typename T1, typename T2>
    static inline std::unique_ptr<Class> unique(T0 && a0, T1 && a1, T2 && a2){
      return std::unique_ptr<Class>( new Class(a0, a1, a2));
    }
    template<typename T0, typename T1, typename T2>
    static inline Class * raw_3(T0 && a0, T1 && a1, T2 && a2){
      return new Class(a0, a1, a2);
    }
    template<typename T0, typename T1, typename T2>
    static inline std::shared_ptr<Class> shared_3(T0 && a0, T1 && a1, T2 && a2){
      return std::make_shared<Class>(a0, a1, a2);
    }
    template<typename T0, typename T1, typename T2>
    static inline void placement_3(void * address, T0 && a0, T1 && a1, T2 && a2){
      new (address) Class(a0, a1, a2);
    }
    template<typename T0, typename T1, typename T2>
    static inline std::unique_ptr<Class> unique_3(T0 && a0, T1 && a1, T2 && a2){
      return std::unique_ptr<Class>( new Class(a0, a1, a2));
    }
    //constructor methods for 4 arguments 
    template<typename T0, typename T1, typename T2, typename T3>
    static inline Class * raw(T0 && a0, T1 && a1, T2 && a2, T3 && a3){
      return new Class(a0, a1, a2, a3);
    }
    template<typename T0, typename T1, typename T2, typename T3>
    static inline std::shared_ptr<Class> shared(T0 && a0, T1 && a1, T2 && a2, T3 && a3){
      return std::make_shared<Class>(a0, a1, a2, a3);
    }
    template<typename T0, typename T1, typename T2, typename T3>
    static inline void placement(void * address, T0 && a0, T1 && a1, T2 && a2, T3 && a3){
      new (address) Class(a0, a1, a2, a3);
    }
    template<typename T0, typename T1, typename T2, typename T3>
    static inline std::unique_ptr<Class> unique(T0 && a0, T1 && a1, T2 && a2, T3 && a3){
      return std::unique_ptr<Class>( new Class(a0, a1, a2, a3));
    }
    template<typename T0, typename T1, typename T2, typename T3>
    static inline Class * raw_4(T0 && a0, T1 && a1, T2 && a2, T3 && a3){
      return new Class(a0, a1, a2, a3);
    }
    template<typename T0, typename T1, typename T2, typename T3>
    static inline std::shared_ptr<Class> shared_4(T0 && a0, T1 && a1, T2 && a2, T3 && a3){
      return std::make_shared<Class>(a0, a1, a2, a3);
    }
    template<typename T0, typename T1, typename T2, typename T3>
    static inline void placement_4(void * address, T0 && a0, T1 && a1, T2 && a2, T3 && a3){
      new (address) Class(a0, a1, a2, a3);
    }
    template<typename T0, typename T1, typename T2, typename T3>
    static inline std::unique_ptr<Class> unique_4(T0 && a0, T1 && a1, T2 && a2, T3 && a3){
      return std::unique_ptr<Class>( new Class(a0, a1, a2, a3));
    }
    //constructor methods for 5 arguments 
    template<typename T0, typename T1, typename T2, typename T3, typename T4>
    static inline Class * raw(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4){
      return new Class(a0, a1, a2, a3, a4);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4>
    static inline std::shared_ptr<Class> shared(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4){
      return std::make_shared<Class>(a0, a1, a2, a3, a4);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4>
    static inline void placement(void * address, T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4){
      new (address) Class(a0, a1, a2, a3, a4);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4>
    static inline std::unique_ptr<Class> unique(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4){
      return std::unique_ptr<Class>( new Class(a0, a1, a2, a3, a4));
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4>
    static inline Class * raw_5(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4){
      return new Class(a0, a1, a2, a3, a4);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4>
    static inline std::shared_ptr<Class> shared_5(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4){
      return std::make_shared<Class>(a0, a1, a2, a3, a4);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4>
    static inline void placement_5(void * address, T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4){
      new (address) Class(a0, a1, a2, a3, a4);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4>
    static inline std::unique_ptr<Class> unique_5(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4){
      return std::unique_ptr<Class>( new Class(a0, a1, a2, a3, a4));
    }
    //constructor methods for 6 arguments 
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    static inline Class * raw(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5){
      return new Class(a0, a1, a2, a3, a4, a5);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    static inline std::shared_ptr<Class> shared(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5){
      return std::make_shared<Class>(a0, a1, a2, a3, a4, a5);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    static inline void placement(void * address, T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5){
      new (address) Class(a0, a1, a2, a3, a4, a5);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    static inline std::unique_ptr<Class> unique(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5){
      return std::unique_ptr<Class>( new Class(a0, a1, a2, a3, a4, a5));
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    static inline Class * raw_6(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5){
      return new Class(a0, a1, a2, a3, a4, a5);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    static inline std::shared_ptr<Class> shared_6(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5){
      return std::make_shared<Class>(a0, a1, a2, a3, a4, a5);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    static inline void placement_6(void * address, T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5){
      new (address) Class(a0, a1, a2, a3, a4, a5);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    static inline std::unique_ptr<Class> unique_6(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5){
      return std::unique_ptr<Class>( new Class(a0, a1, a2, a3, a4, a5));
    }
    //constructor methods for 7 arguments 
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    static inline Class * raw(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6){
      return new Class(a0, a1, a2, a3, a4, a5, a6);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    static inline std::shared_ptr<Class> shared(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6){
      return std::make_shared<Class>(a0, a1, a2, a3, a4, a5, a6);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    static inline void placement(void * address, T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6){
      new (address) Class(a0, a1, a2, a3, a4, a5, a6);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    static inline std::unique_ptr<Class> unique(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6){
      return std::unique_ptr<Class>( new Class(a0, a1, a2, a3, a4, a5, a6));
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    static inline Class * raw_7(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6){
      return new Class(a0, a1, a2, a3, a4, a5, a6);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    static inline std::shared_ptr<Class> shared_7(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6){
      return std::make_shared<Class>(a0, a1, a2, a3, a4, a5, a6);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    static inline void placement_7(void * address, T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6){
      new (address) Class(a0, a1, a2, a3, a4, a5, a6);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    static inline std::unique_ptr<Class> unique_7(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6){
      return std::unique_ptr<Class>( new Class(a0, a1, a2, a3, a4, a5, a6));
    }
    //constructor methods for 8 arguments 
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    static inline Class * raw(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6, T7 && a7){
      return new Class(a0, a1, a2, a3, a4, a5, a6, a7);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    static inline std::shared_ptr<Class> shared(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6, T7 && a7){
      return std::make_shared<Class>(a0, a1, a2, a3, a4, a5, a6, a7);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    static inline void placement(void * address, T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6, T7 && a7){
      new (address) Class(a0, a1, a2, a3, a4, a5, a6, a7);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    static inline std::unique_ptr<Class> unique(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6, T7 && a7){
      return std::unique_ptr<Class>( new Class(a0, a1, a2, a3, a4, a5, a6, a7));
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    static inline Class * raw_8(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6, T7 && a7){
      return new Class(a0, a1, a2, a3, a4, a5, a6, a7);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    static inline std::shared_ptr<Class> shared_8(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6, T7 && a7){
      return std::make_shared<Class>(a0, a1, a2, a3, a4, a5, a6, a7);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    static inline void placement_8(void * address, T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6, T7 && a7){
      new (address) Class(a0, a1, a2, a3, a4, a5, a6, a7);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    static inline std::unique_ptr<Class> unique_8(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6, T7 && a7){
      return std::unique_ptr<Class>( new Class(a0, a1, a2, a3, a4, a5, a6, a7));
    }
    //constructor methods for 9 arguments 
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    static inline Class * raw(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6, T7 && a7, T8 && a8){
      return new Class(a0, a1, a2, a3, a4, a5, a6, a7, a8);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    static inline std::shared_ptr<Class> shared(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6, T7 && a7, T8 && a8){
      return std::make_shared<Class>(a0, a1, a2, a3, a4, a5, a6, a7, a8);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    static inline void placement(void * address, T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6, T7 && a7, T8 && a8){
      new (address) Class(a0, a1, a2, a3, a4, a5, a6, a7, a8);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    static inline std::unique_ptr<Class> unique(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6, T7 && a7, T8 && a8){
      return std::unique_ptr<Class>( new Class(a0, a1, a2, a3, a4, a5, a6, a7, a8));
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    static inline Class * raw_9(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6, T7 && a7, T8 && a8){
      return new Class(a0, a1, a2, a3, a4, a5, a6, a7, a8);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    static inline std::shared_ptr<Class> shared_9(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6, T7 && a7, T8 && a8){
      return std::make_shared<Class>(a0, a1, a2, a3, a4, a5, a6, a7, a8);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    static inline void placement_9(void * address, T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6, T7 && a7, T8 && a8){
      new (address) Class(a0, a1, a2, a3, a4, a5, a6, a7, a8);
    }
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    static inline std::unique_ptr<Class> unique_9(T0 && a0, T1 && a1, T2 && a2, T3 && a3, T4 && a4, T5 && a5, T6 && a6, T7 && a7, T8 && a8){
      return std::unique_ptr<Class>( new Class(a0, a1, a2, a3, a4, a5, a6, a7, a8));
    }
  };
NS_END(CORE_NAMESPACE)
