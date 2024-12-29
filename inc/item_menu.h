#ifndef ITEM_MENU_H
#define ITEM_MENU_H
#include <iostream>
#include "m_tuple.h"
#include "cb_item.h"

#include <utility>


namespace  Core
{
using namespace Containers;
// callback -part
// часть хранящая callback
// предполагаем, что callback не возвращает ничего в вызывающую функцию

// item  - содержит cb и другие данные




struct base_
{
    std::string name_;

     base_(const std::string& n):name_(n){}

     std::string name(){return name_;}
    virtual void callback()=0;
     virtual ~base_(){}
};
// общий элемент


// *********************
// элемент меню, требующий строку в заголовке
template <typename T>
struct item:public base_
{


 base_cb* cb_{nullptr};   // хранит callback элемента


public:
 item():base_("noname_"),cb_(nullptr){}
 template<typename ...Arg>
item(const std::string &s,T &t,void(T::*f)(Arg...),Arg...a):base_(s),cb_(make_cb(t,f,a...))
{}

~item(){delete cb_;}

 template<typename ...Arg>
 void set_callback(T& t, void(T::*f)(Arg...),Arg...a)
 {
   if(cb_)
       delete  cb_;
   cb_=make_cb(t,f,a...);
 }

    void callback(){
        if(cb_)
             cb_->callback();
    }

    template<typename ...Arg>
    void callback(Arg...a)
    {
      if(cb_)
           cb_->callback<T,Arg...>(a...);
    }


};

}

#endif // ITEM_MENU_H
