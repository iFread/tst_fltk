#ifndef MENU__H
#define MENU__H
#include "m_list2.h"
#include <string>
#include <tuple>
#include "m_tuple.h"
// класс вертикального меню,
// базовый элемент("имя", "callback")
// наследник1 : "имя", свойства для выбора, объект с которым связан элемент
// наследник2:  содержит вертикальное меню( callback= при наведении мыши, раскрыть меню)
//              при покидании раскрытого меню- скрыть
//          (здесь возможно симтема обработки событий)
//


// отображение рекурсивно:
     //
   //

// класс горизонтального меню
//  каждый элемент содержит вертикальное меню

 // 1. формирование calback
  // item_->callback(); ==>
  // item->callback(Arg... a) ==>
using namespace Containers;

namespace Graph2 {

// template <size_t N=0>
// using make_sq=   typename  make_is_impl<index_sequance<size_t,0 >,0 >::type  ;



//template <typename Tv,typename Fmx,typename Tuple,size_t ...Ins>
//void _callback(Tv &obj,Fmx fx,const Tuple &t,std::integer_sequence<size_t,Ins...>)
//{
//   // using  FI=func_info<Fmx> ;
//    //using Arg_t =typename FI::stack_arg;
//   // using  Arg_tp =std::tuple<std::decay_t<Args>...>;
//  //  Arg_tp tp=std::make_tuple(a...);

//(obj.*fx)((std::get<Ins>(t))...);
//}


//template <typename  Tv,typename  Fmx,typename  Tuple,size_t ss=tuple_size<Tuple>::value>
//void _callback(Tv &obj,Fmx fx,const Tuple& tp)
//{

//    using tuple_type =decltype (tp) ;

// //  constexpr  static size_t ss=  tuple_size<Tuple>::value;
//    _callback(obj,fx,tp, make_sq<ss>{});
//}
//template <typename  Tv,typename  Fmx,typename  Tuple,size_t ss=tuple_size<Tuple>::value>
//void _callback(Tv &obj,Fmx fx,  Tuple&  tp)
//{

//    using tuple_type =decltype (tp) ;

// //  constexpr  static size_t ss=  tuple_size<Tuple>::value;
//    _callback(obj,fx,tp,make_sq<ss>{});
//}


template <typename Tv,typename Fmx,typename Tuple,size_t ...Ins>
  void _callback(Tv &obj,Fmx fx, Tuple && t,index_sequance<size_t,Ins...>)
{

 // ((get<Ins>(t)),...);
  (obj.*fx)((get<Ins>(t)) ...);
}

template <typename Tv,typename Fmx,typename Tuple,size_t ...Ins>
  void _callback(Tv &obj,Fmx fx, const Tuple &t,index_sequance<size_t,Ins...>)
{

(obj.*fx)((get<Ins>(t))...);
}


  template <typename  Tv, typename Fx, typename Tuple>
  void _callback(Tv & obj, Fx f, const Tuple &t)
  {

      constexpr auto ss= tuple_size<Tuple>::value;
      _callback(obj,f,t,make_index_sequance<ss>{});
  }

template <typename ...Ins>
void print_elem(Ins...i)
{
    std::cout<<"\n";
}



template <typename T,typename...Arg>
void print_elem( const T& t, Arg...val)
{
    std::cout<<t;
 if(sizeof...(val)!=0)
     std::cout<<", ";
    print_elem(val... );

}






template <typename Tuple,size_t... Ins>
 void print_param(const Tuple& t, index_sequance<size_t,Ins...>)
{

      print_elem((get<Ins>(t))...); //Element<idx,Tuple>::Type_t.value
}




 template <class T,class Fmx,class ...Arg>
struct item_  // базовый элемент меню
{
   std::string name_;
T* obj;
Fmx fx;
template<typename U>
using decay_t=typename std::decay<U>::type;

using new_stack =std::tuple<decay_t<Arg>...> ;
using new_stack2=Containers::Tuple<decay_t<Arg>...>;

//new_stack args;
new_stack2 args;

//using
constexpr  static size_t _ssize =tuple_size<new_stack2>::value;


item_(const std::string&s,T&t,Fmx f,Arg...a):name_(s),obj(&t),fx(f),args(make_tuple(a...))
{

}
template<typename ...Args>
item_(const std::string& n,T&t,Fmx f):name_(n),obj(&t),fx(f){}



item_(const item_&)=delete;
item_& operator=(const item_&)=delete;

 item_(item_&& it){ this->obj = it.obj;name_="move obj\n";}

void callback()
{
   //  (obj->*fx)(std::get<0>(args),std::get<1>(args));

 //    _callback(*obj,fx,args);
 //   _callback(*obj,fx,args,  make_seq<_ssize>{});//index_sequance<_ssize>{});//std::make_integer_sequence<size_t,_ssize>{});//std::make_integer_sequence<size_t,_ssize>{});
 std::cout<<name_<<"\n";
    _callback(*obj,fx,args);
   //  _callback(*obj,fx,args,  make_sq<_ssize>{});
    //   print_param(args, make_seq<_ssize>{});//(args);
}


template<typename ...Args>
void callback(Args...a)
{
   std::cout<<name_<<"\n";
  // (obj)?
    _callback(*obj,fx,make_tuple<Args...>(a...));//:_callback(fx,make_tuple<Args...>(a)...);
//    _callback(*obj,fx,make_tuple<Args...>(a...),make_seq<_ssize>{});

//    _callback(*obj,fx,make_tuple<Args...>(a...), make_index_sequance<_ssize>{} );

  // print_param(make_tuple<Args...>(a...),make_seq<_ssize>{});
}

};

template <class Cl,class R,typename ...Arg>
auto select_f(Cl&cl,R(Cl::*func)(Arg...),Arg...a) ->decltype (func)
{
    return func;
}

template <class cl,class Fx,typename ...Arg>
constexpr item_<cl,Fx,Arg...> make_item_(cl &obj,Fx x, Arg...a)
{
   // using Fi =func_info<Fx>;
   // using foo=Fx;
    return  item_<cl,decltype(x),Arg...>(obj,x,a...) ;
}

template <typename Cl,typename Ret=void,typename... Arg>
 item_<Cl,Ret(Cl::*)(Arg...),Arg...> make_item(Cl& cl,Ret(Cl::*func)(Arg...),Arg...a) //->decltype (make_item_(cl,func,a...))
{

     return  item_<Cl,Ret(Cl::*)(Arg...),Arg...>("args ",cl,func,a...) ;
   // return make_item_<Cl,func,Arg...>(cl,func,a...);//(cl,select_f(cl,f_,a...),a...);
}

 template<typename U>
 using decay_t=typename std::decay<U>::type;


 template <typename Cl,typename Ret=void,typename... Arg>
  item_<Cl,Ret(Cl::*)(Arg...),Arg...> make_item(Cl& cl,Ret(Cl::*func)(Arg...)) //->decltype (make_item_(cl,func,a...))
 {
 //  using foo= Ret(Cl::*)(Arg...);
 //    foo f_=&func;
      return item_<Cl,Ret(Cl::*)(Arg...),Arg...>("one_arg",cl,func );
    // return make_item_<Cl,func,Arg...>(cl,func,a...);//(cl,select_f(cl,f_,a...),a...);
 }

  template <class Derived>
  class Base:public Derived
  {

  };

  struct ittem: item_<int,void(*)(int,double),int,double>
  {

  };

template <typename Cl,typename Ret=void,typename ...Arg>
 void foo(Cl& c, Ret(Cl::*f)(Arg...),Arg...a)
{  //using ret=decltype ((c.*f)(a...));
  return (c.*f)(a...);
}

}


#endif // MENU__H
