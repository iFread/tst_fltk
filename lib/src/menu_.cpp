#include "menu_.h"
#include <FL/Fl.H>

namespace Graph2 {


void menu_:: add( Core::base_* it)
{
 // здесь возможна проверка вертикально/горизонтально
l.push_back(it);
 if(w_<(it->name().size()*sym_w))
     w_=it->name().size()*sym_w;
 h_= l.size()*sym_h +(l.size()+1)*mrg;
 resize(w_,h_);

}


void menu_::draw()
{     // пройти по списку l и отобразить name_ каждого элемента

    fl_rect(loc.x(),loc.y(),w_+2*mrg,h_+mrg, FL_RED);
  Point nxt={loc.x(),loc.y()};
    for(auto it=l.cbegin(),e=l.cend();it!=e;++it)
    {

    // fl_draw((*it).name().c_str(),nxt.x(),nxt.y());
    draw(nxt, *it );
        nxt= {nxt.x(),nxt.y()+sym_h+mrg};
    }
}

void menu_::draw(Point o,Core::base_&b)
{
 fl_rectf(o.x(),o.y()+mrg,w_+2*mrg ,sym_h  , Color::blue);
 fl_color(Color(Color::black).as_int());
 fl_draw(b.name().c_str(),o.x()+mrg,o.y()+sym_h+mrg);
}

int menu_::handle(int ev)
{
  // при движении мыши определяем область (елемент над которым курсор)
    // при нажатии вызывается callback выбранного элемента

   // Если покидаем меню, (но не переход на submenu) запускается таймер,

// для оптимизации :
    /*
    если сохранять точку (значение по Y) текущего элемента
     и при движении мыши проверять разницу от сохраненной точки
     до текущего курсора, если разница больше sym_h+ mrg,
      выполнять новый поиск элемента

    */
    switch (ev)
    {
    case FL_MOVE:
 {
        int c=find_item();

    }      break;

     case FL_LEAVE:

        break;

    }




    return ev;
}


int menu_::find_item() const
{
   // int x_=Fl::event_x();
    int y_=Fl::event_y();

  int nxt_h=loc.y() ;

   for(auto bg=l.cbegin(),end=l.cend() ;bg!=end;++bg)
   {
    if(y_>nxt_h && y_<nxt_h+sym_h+2*mrg)
       {
        std::cout<<"name : "<<(*bg).name()<<"\n";
        return nxt_h+mrg+sym_h/2 ; // середина элемента
    }
        // на каждой итерации прибавляем размеры элемента+отступ
       nxt_h=nxt_h+sym_h+2*mrg;

   }
   return -1;

}

}
