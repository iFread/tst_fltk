#ifndef TST_ITEM_H
#define TST_ITEM_H
#include "m_tuple.h"
#include <utility>
#include <string>
#include <iostream>
namespace Containers
{


template <typename T>
struct item_2;

struct base_item
{
 // возможно интерфейс
  //  virtual void callback()=0;

   virtual void callback()=0;

       template<typename T,typename ...Arg>
    void callback(Arg...a)
      {
//       // вызвать callback производного класса
           static_cast<item_2<T>*>(this)->callback(a...);
    }
//       //


    virtual ~base_item(){}
};

template <typename Derived>
struct  base_item_tmp:public Derived
{

    template<typename ...Arg>
    void callback(Arg...a)
    {
        static_cast<Derived>(*this)->callback(a...);
    } // для вызова с аргументами

    virtual void callback()
    {
        static_cast<Derived*>(this)->callback();
    } // для  вызова без аргументов

    ~base_item_tmp(){}
};

template <typename Base,typename Derived,typename ...Arg>
void callback(Base* b,Arg...a)
{
    static_cast<Derived*>(b)->callback(a...);
}






template <typename T,typename Ret ,typename ...Arg>
struct item_2<Ret(T::*)(Arg...)>:public base_item
{
 using  foo =Ret(T::*)(Arg...) ;

template<typename U>
using decay_t=typename std::decay<U>::type;


using tuple_type=Containers::Tuple<decay_t<Arg>...>;

std::string name_;
T* obj_;
foo f_;
tuple_type tp;


item_2(const std::string & n,T& obj,foo f,Arg...a):name_(n),obj_(&obj),f_(f),tp(make_tuple(a...))
{}
// item_2(T*o,foo f):obj_(o),f_(f),tp(){}
// создаем
template<typename T1,typename Fx,typename ...Args>
item_2(const std::string &n,T1* t,Fx f):name_(n),obj_(t),f_(f)
{

}

item_2(const item_2& it):name_(it.name_),obj_(it.obj_),f_(it.f_),tp(it.tp)
{

}

//

//template<typename ...Args>

template<typename Tuple,size_t ...Ins>
void _callback(const Tuple &t,index_sequance<size_t,Ins...>)
{
(*obj_.*f_)((get<Ins>(t))...);
}

void callback()
{
    std::cout<<"name : "<<name_<<":";
   constexpr auto ss= tuple_size<tuple_type>::value;
    _callback(tp,make_index_sequance<ss>{});
}
template<typename... Args>
void callback(Args...a)
{  constexpr auto ss= tuple_size<tuple_type>::value;
   _callback(make_tuple<Args...>(a...),make_index_sequance<ss>{});
}

    };


template <typename Obj,typename Ret,typename ...Arg>
item_2<Ret(Obj::*)(Arg...)>* make_item2(const std::string &n,Obj&o,Ret(Obj::*f)(Arg...))
{
     return new item_2<Ret(Obj::*)(Arg...)>(n,o,f);
}
template <typename Obj,typename Ret=void,typename ...Arg>
item_2<Ret(Obj::*)(Arg...)>* make_item2(const std::string& n,Obj&o,Ret(Obj::*foo)(Arg...),Arg...a)
{
    return new item_2<Ret(Obj::*)(Arg...)>(n,o,foo,a...);
}
template <typename T,typename Ret,typename ...Arg>
item_2<Ret(T::*)(Arg...)>* make_item2(const item_2<Ret(T::*)(Arg...)>& it)
{
    return new item_2<Ret(T::*)(Arg...)>(it);
}

//list<base_item_tmp<item_2>*> l;





template <typename T>
struct item_3:base_item
{
   base_item* it;
    template<typename ...Arg>
    item_3(const std::string &s,T&t,void(T::*f)(Arg...),Arg...a):it(new item_2<void(T::*)(Arg...)>(s,t,f,a...))
    {}

    void callback()
    {
      it->callback();
    }
};
}



#endif // TST_ITEM_H
