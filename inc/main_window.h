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
Graph2::menu_ m_;


public:
main_window(Point o,int w,int h,const std::string& s=""):window(o,w,h,s.c_str()),
    m_(Point(20,20),{new Core::item<main_window>("new file",*this,&main_window::create),
                     new Core::item<main_window>("open",*this,&main_window::open),
                    new Core::item<window>("quit",*this,&window::hide)})
{
 attach(m_);
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

void create()
{
  std::cout<<"create new file...\n";
}


~main_window(){
    m_.clear();
     detach(m_);
             }
};
}


#endif // MAIN_WINDOW_H
