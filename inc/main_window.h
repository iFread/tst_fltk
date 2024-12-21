#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include "window.h"
#include "menu_.h"
#include "item_menu.h"
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
}


void open(){
    std::cout<<"open file... \n";
}

void create()
{
  std::cout<<"create new file...\n";
}

};
}


#endif // MAIN_WINDOW_H
