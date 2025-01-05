#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include "window.h"
#include "menu_.h"
#include "item_menu.h"
#include "modal_window.h"

#include <iostream>

namespace Graph {


class main_window:public window
{
    Graph2::menu_ *m_{nullptr};


public:
main_window(Point o,int w,int h,const std::string& s=""):window(o,w,h,s.c_str())

{
 //attach(m_);
 std::cout<<"create main_window \n";
}

main_window(const main_window&)=delete;
main_window(main_window&&)=delete;


void open(){
    std::cout<<"open file... \n";
    Graph2::base_modal* w=new Graph2::base_modal(Point (x()+100,y()+100),500,400,"test_modal");
//   w->set_label("some text in label\nor quastion for user");

     w->set_callback(new Core::item_cb<void(Graph2::base_modal::*)()>(*w,&Graph2::base_modal::set_path),"Hello World");

    while(w->shown())
    {
      Fl::wait();
    }
    w->hide();
    std::cout<<"get path = "<<w->get_path()<<"\n";
   delete w;

}

int handle(int e);


// как вариант
    // void create_menu(Point o,Widget&w) // или унаследованный от Widget класс, с виртуальной функцией\
virtual Graph2::menu_* create_menu(Point); //
// таким образом виджет меню , будет формироваться нужным классом, и должен отображаться поверх остальных \
виджетов, в этом случае события должны быть перехвачены классом menu_
Graph2::menu_* create_menu(Point o);



void create()
{
  std::cout<<"create new file...\n";
}


~main_window(){
  if(m_)  m_->clear();
     detach(*m_);
             }
};
}


#endif // MAIN_WINDOW_H
