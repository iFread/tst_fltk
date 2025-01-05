#include "menu_.h"
#include <FL/Fl.H>

namespace Graph2 {


void menu_:: add( Core::base_* it)
{
 // здесь возможна проверка вертикально/горизонтально
l.push_back(it);
 if(w_<(static_cast<int>(it->name().size())*sym_w))
     w_=(it->name().size()*sym_w+2*mrg)*2;
 h_= l.size()*sym_h +(l.size()+1)*mrg;
 resize(w_,h_);

}


void menu_::draw()
{     // пройти по списку l и отобразить name_ каждого элемента

    fl_rect(loc.x(),loc.y(),w_ ,h_+2*mrg  , Color::black);
  Point nxt={loc.x(),loc.y()};
 auto sl= l.find(select_elem);
    for(auto it=l.begin(),e=l.end();it!=e;++it)
    {

    // fl_draw((*it).name().c_str(),nxt.x(),nxt.y());

      if(*sl &&(*it==*sl))
          draw(nxt, **it,Color::blue );
      else
          draw(nxt,**it,Color::cyan);
        nxt= {nxt.x(),nxt.y()+sym_h+ mrg};

    }
}

void menu_::draw(Point o, Core::base_&b, Color c)
{

     fl_rectf(o.x()+1,o.y()+1+mrg,(w_-2) ,(sym_h-2)+2* mrg ,c.as_int());

// fl_rectf(o.x(),o.y()+mrg,w_+2*mrg ,sym_h);
 //fl_color(Color(Color::black).as_int());
 //fl_draw(b.name().c_str(),o.x()+mrg,o.y()+sym_h+ mrg);
 draw_text(Point(o.x()+mrg,o.y()+ mrg),b.name().c_str(),f_,cl);
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
     до текущего курсора, если разница больше sym_h/2+ mrg,
      выполнять новый поиск элемента

    */
    switch (ev)
    {
    case FL_MOVE:
 {
     int cnt=Fl::event_y();

     if(_cnt_pos_<0||std::abs(_cnt_pos_-cnt)>(sym_h/2+mrg))
       { _cnt_pos_=find_item(cnt);
 // проверка на sub_menu,
         // и вызов callback если истина

     pw->redraw();
    } }  break;



     case FL_PUSH:

      switch (Fl::event_button())
      {
       case FL_LEFT_MOUSE:

         if(select_elem)
             select_elem->callback();
          break;
        case FL_RIGHT_MOUSE:
          break;

      }

        break;
    case FL_LEAVE:

     _cnt_pos_=-1;
     select_elem=nullptr;
 pw->redraw();
       break;
    }




    return ev;
}


int menu_::find_item(int pos)
{

  int nxt_h=loc.y() ;

   for(auto bg=l.cbegin(),end=l.cend() ;bg!=end;++bg)
   {
    if(pos>nxt_h && pos<nxt_h+sym_h+2*mrg)
       {

        std::cout<<"name : "<<(*bg)->name()<<"\n";
       select_elem=*bg;
        return nxt_h+mrg+sym_h/2 ; // середина элемента
    }
        // на каждой итерации прибавляем размеры элемента+отступ
       nxt_h=nxt_h+sym_h+2*mrg;

   }
   return -1;

}
void menu_::clear()
{  for(auto e=l.begin();e!=l.end();)
    {
    Core::base_* del= *e;
    e=l.remove(e);
    delete del;
 }
    select_elem=nullptr;
    l.clear();
}

}
