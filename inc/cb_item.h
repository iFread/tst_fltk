#ifndef CB_ITEM_H
#define CB_ITEM_H

#include <m_tuple.h>
#include <iostream>



namespace Core {

using namespace Containers;

template <typename T>
struct item_cb;  // объявление


struct base_cb // ABT
{



// вызов будет выглядеть как ptr->callback<void(A::*)(double)>(double d);

    template<typename T,typename ...Arg>
    void callback(Arg...a)
    {
       item_cb<void(T::*)(Arg...)>* ddptr= dynamic_cast<item_cb<void(T::*)(Arg...)>*>(this);
       // вызов = ptr->callback<A,double>(double)
     //  item_clb<T>* dptr_= dynamic_cast<item_clb<T>*>(this);
       if(ddptr)
           ddptr->template callback<Arg...>(a...);
       else  // хотелось бы ошибки компиляции
           std::cerr<<"wrong type\n";
    }

   virtual void callback()=0;// для вызова без аргумента (99% случаев)


   virtual ~base_cb(){}
};


template <typename T,typename ...Arg>
struct item_cb<void(T::*)(Arg...)>:public base_cb {



using func_ = void(T::*)(Arg...) ;
using type = item_cb<void(T::*)(Arg...)> ;
template<typename U>
using decay_t = typename std::decay<U>::type;

using tuple_type= Containers::Tuple<decay_t<Arg>...>;
//using make_tuple = Containers::make_tuple;
  // храним сам объект, метод, и тапл аргументов
T* obj_;
func_ f_;
tuple_type tp_;

public:
 item_cb(T& t,func_ fx,Arg...a): obj_(&t),f_(fx),tp_(make_tuple(a...))
 {}



 void callback()
{
    constexpr size_t ss=tuple_size<tuple_type>::value;
    _callback(tp_,make_index_sequance<ss>{});

}

 template<typename ...Args>
 void callback(Args...a)
 {
     constexpr size_t ss= tuple_size<tuple_type>::value;
     tuple_type ttp=make_tuple<Args...>(a...);
     _callback(ttp,make_index_sequance<ss>{});

 }

 protected:
 template<size_t...Ins>
 void _callback(const tuple_type&  tp,index_sequance<size_t,Ins...>)
 {
 (*obj_.*f_)((get<Ins>(tp))...);
 }

}  ;


template <typename T,typename ...Arg>
item_cb<void(T::*)(Arg...)>* make_cb(T& t,void(T::*f)(Arg...),Arg...a)
{
    return new item_cb<void(T::*)(Arg...)>(t,f,a...);
}

//template <typename T >
//struct item_cb<T>
//{

//};

}
#endif // CB_ITEM_H
