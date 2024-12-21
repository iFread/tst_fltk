 
#ifndef M_TUPLE_HH
#define M_TUPLE_HH
#include <stddef.h>

namespace Containers
{

//template <typename >
//struct func_info;
//using namespace Containers;
//template <typename  R, typename Cl,typename ...Arg>
//struct func_info<R(Cl::*)(Arg...)>
//{
//    template< typename ...A>
//   // using  Tuple{} =  Containers::Tuple{} ;
//    using ret=R;
//    using cl=Cl;
//    using args=std::tuple<Arg...>;
//    using args2=Containers::Tuple<Arg...>;
//    using stack_arg=std::tuple<std::remove_pointer<std::remove_reference<Arg>>...>;
//   using stack_arg2=Containers::Tuple<std::remove_pointer<std::remove_reference<Arg>>...>;
//};




template <typename T,T... Ins>
struct index_sequance
{
    using value_type = T;
  using type=index_sequance;
    static constexpr size_t size() noexcept{return  sizeof... (Ins);}

};

template <size_t Cnt,size_t...I>
struct make_impl:public make_impl<Cnt-1,Cnt-1,I...>
{
};

template <size_t ... Int>
struct make_impl<0,Int...>:index_sequance<size_t,Int...> {};

template <size_t N>
using make_seq=typename make_impl<N>::type;



template <typename T,size_t... I>
struct make_is_impl{
  //  using type = typename index_sequance<size_t,I...>::type ;
};




template <size_t Cnt,size_t...Ints>
struct make_is_impl<index_sequance<size_t,  Ints...>, Cnt   >
        :make_is_impl<index_sequance<size_t,Cnt-1  ,Ints...>,Cnt -1   >{
 // using type =  typename index_sequance<size_t,  Ints...>::type  ;

};

//template < >
//struct make_is_impl<index_sequance<size_t,0>,0>
//   //:index_sequance<size_t,Ints...>
//{
//    using type =    index_sequance<size_t>  ;
//};

template <size_t...Ints>
struct make_is_impl<index_sequance<size_t,0, Ints...>,0> :make_is_impl<index_sequance<size_t,Ints...>,0>
   //:index_sequance<size_t,Ints...>
{
    using type =    index_sequance<size_t,0,   Ints...>  ;
};
template <size_t...Ints>
struct make_is_impl<index_sequance<size_t ,Ints...>,0>
{
 using type =    index_sequance<size_t,  Ints...>  ;
};
//template <size_t>
//struct make_index_sequance{};

template <size_t I,size_t...Ins>
 using make_index_sequance  =typename make_is_impl<index_sequance<size_t,(I>0)?I-1:Ins... >, (I>0)?I :0  >::type ;

 //  typename make_is_impl<index_sequance<size_t,I>,I>::type  ;// make_is_impl<index_sequance<size_t, I>,I>::type  ;




using sequance  =     index_sequance<size_t > ;

template <size_t N,size_t ...Ins>
using make_sq=   typename  make_is_impl<index_sequance<size_t,(N>0 )? N-1:Ins...>,(N>0)?N :0>::type  ;



    template<typename ... Types>
   struct   Tuple;
  
  // базовый случай
    template<>
    struct Tuple<> {};
    
    template<typename Tfr, typename ...Types>
    struct Tuple<Tfr, Types...>:public Tuple<Types...>
    {
      Tfr value;  
    };
    
   
    // индексы 
     template<size_t idx, typename ...Ttuple>
     struct Element;
    
    


//    template<size_t idx=1,typename Tfr,typename ...Types>
//    struct Element<idx,Tfr,Types...>:public Element<0,Tuple<Types...>> { };



   template<size_t idx,typename Tfr,typename ...Types>
    struct Element<idx,Tuple<Tfr,Types...>>:public Element<idx-1,Tuple<Types...>> { };
    

    template<typename TFr,typename ...Types>
    struct Element<0,Tuple<TFr,Types...>>
    {
        using Type_t = TFr;
        using CType_t = const Type_t;
        using TupleType_t= Tuple<TFr,Types...>;

     };


    template<size_t idx,typename ...Types>
    typename Element<idx,Tuple<Types...> >::Type_t & get(Tuple<Types...>  &tp)
    {
        using TupleType_t=typename Element<idx,Tuple<Types...>>::TupleType_t;
        return static_cast<TupleType_t &>(tp).value;
    }
    
    template<size_t idx,typename ...Types>
 typename Element<idx,Tuple<Types...> >:: Type_t   get(const Tuple<Types...> &tp)
    {


        using TupleType_t=typename Element<idx,Tuple<Types...>>::TupleType_t;

  //   std::cout<<" idx = "<<idx<<" "<< static_cast< TupleType_t >(tp).value<<"\n";

        return static_cast< TupleType_t  >(tp).value;
    }

   // заполнение tuple
   
   // базовый случай
   template<size_t idx,typename Tuple>
   void FillTuple(Tuple &) {}
   
   // кладем элемент и вызываем рекурсивно для остальных
   template<size_t idx,typename Ttuple, typename Tfrst, typename ...Types>
   void FillTuple(Ttuple &tp,const Tfrst &fr, const Types&...tps)
   {
     get<idx>(tp)=fr;
     FillTuple<idx+1>(tp,tps...);
}



 template<typename ...Types>
 Tuple<Types...> make_tuple(const Types& ...tps)
 {
  Tuple<Types...> res;
  FillTuple<0>(res,tps...);
  return res;
}

 template <typename T>
 struct tuple_size;

 template <typename ...Types>
 struct tuple_size< Tuple<Types...>  >
 {
   static const size_t value = sizeof...(Types);

 };
 template <typename ...Types>
 struct tuple_size<const Tuple<Types...>&  >
 {
   static const size_t value = sizeof...(Types);

 };
    
}




#endif
