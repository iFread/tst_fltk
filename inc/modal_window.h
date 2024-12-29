#ifndef MODAL_WINDOW_H
#define MODAL_WINDOW_H

#include "item_menu.h"
#include "window.h"
#include "base_gui.h"

using namespace Graph;
namespace Graph2
{
// базовое окно: одна кнопка и какая-то информация
 class base_modal:public window
 {
   Button  bn_ok;
   Button bn_cncl;
   Label2 lb_;
  Core::base_cb * cb_;

 public:
     // размер кнопок 70x30, расположены снизу окна, на 10 px от края окна

   base_modal(Point o,int w,int h,const std::string& s="text"):window(o,w,h,s.c_str()),
       bn_ok(Button(Point(10,h-40),70,30,"Ok")),
       bn_cncl(Button(Point(w-80,h-40),70,30,"Cancel")),
       lb_(Point(w/2,h/2),w/2,h/2),cb_(nullptr)
         {
       init();
       }

// callback - должен быть собственный метод окна,
   // иначе нет смысла,
   // каждое окно имеет set/get методы с нужными параметрами,
   // при выборе устанавливаем параметры, после закрытия окна - передаем в вызывающее окно
   // полученный параметр
void set_callback(Core::base_cb* b,const std::string& s="");



void init();

void set_label(const std::string &s) {lb_.set_label(s);}
// пример callback :
 // окно открытия : получаем path - к файлу,
 // после нажатия ok - передаем сформированный path - вызывающему.

std::string get_path(){return path_;}
void set_path(){//path_=p;
    // path_=lb_.
    hide();
 }

~base_modal(){if(cb_) delete cb_;}
 private:
std::string path_{};

 };


}



#endif // MODAL_WINDOW_H
