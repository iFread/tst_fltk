#include "main_window.h"

namespace Graph
{


Graph2::menu_* main_window::create_menu(Point o)
{
       return new Graph2::menu_(o,{new Core::item<main_window>("new file",*this,&main_window::create),
                         new Core::item<main_window>("open",*this,&main_window::open),
                       new Core::item<window>("quit",*this,&window::hide)});
}


int main_window:: handle(int e){

    switch (e)
    {

    case FL_PUSH:
 switch (Fl::event_button()) {
      case FL_RIGHT_MOUSE:
      {
     if(m_){
         delete m_;
 }
          int w=Fl::event_x();
          int h=Fl::event_y();
         // m_->set_position(Point(w,h));
         //m_->show();
        m_=create_menu(Point(w,h));
        attach(*m_);
        m_->show();
          redraw();
 }
     break;
    default:
     if(m_) {
      m_->handle(e);

         m_->hide();
  detach(*m_);
     delete m_;
     m_=nullptr;
     //return res;
     }
     break;
 }// m_.hide();

        break;

    }
   return window::handle(e);
}

}
