#include <iostream>
#include "window.h"
#include "item_.h"
#include "tst_item.h"
#include "menu_.h"
#include "item_menu.h"
#include "main_window.h"

using namespace std;

void tst_graph();

 struct A
 {
     int a_,b_;

   A(int a,int b):a_(a),b_(b){}

    void print(int a,int b,int c )
     {
       std::cout<<a<<"..."<<b<<"..."<<c<<"\n";
     }
     void print()
     {
       std::cout<<"method has not any parametr\n";
     }

     void print(double d)
     {
         std::cout<<d<<"zdets\n";
     }

 };
 struct B
 {
     void printf() {std::cout<<"printf in B\n";}
 };
void tst_item();

int main()
{
 //tst_item();
  tst_graph();
    return 0;
}


void tst_item()
{
    using namespace Graph2;
    A a(10,12);
  B b;
 item_3<A> it("Hello",a,&A::print);
 it.callback();

Core::item_cb<void(A::*)(double) > its(a,&A::print,3.13 );
Core::base_cb* iit=   Core::make_cb(a,&A::print,3.16);
its.callback();
 iit->callback< A,double>(4.56);

 Core::item<A> u;
 u.set_callback<double>(a,&A::print,3.77);
 u.callback();
 u.callback<double>(3.111);

}


void tst_graph()
{
    using  namespace Graph ;
    main_window w(Point(100,100),800,600,"test");


    gui_run();


}

