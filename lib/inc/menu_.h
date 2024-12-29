#ifndef MENU___H
#define MENU___H
#include <string>
#include <item_.h>
#include "m_list2.h"
#include "tst_item.h"
#include "base_gui.h"
#include "item_menu.h"
#include <initializer_list>
#include "gui_attributes.h"
/*
 1. меню содержит заголовок и массив  item_??? (и наследников item_)
 2. меню - tuple {item, submenu}
menu {  item_=make_item("file",make_item())


};

make_menu = {"name", item1,item2...item N};
        //   add_item() ???

     item_("name",this,callback(),Args...a);
     item_("name",canvs,callback(),Args...a);
   make_item<void(Window::*)(std::string)>("open",this,Window::open )

   1. как сделать динамическое обновление (add_item?)

   2.

*/
using namespace Containers;
using namespace Graph;
namespace Graph2 {




class menu_:public Empty
{
 std::string header_;
 list2<Core::base_*> l;

 // нужны какие то данные:
    //размер шрифта(ширина буквы), высота буквы, размер отступа между элементами,
 // эти данные нужно загружать при создании меню

 int w_=0,h_=0; // определяет размер виджета : ширина опеределяется самым длинным name_,
                // высота определяется (количеством base_+(отступы-1)) * размер шрифта
enum ffont {sym_w=8,sym_h=14,mrg=5}; // пока определим в ручную
 // допустим функция init(), при создании меню устанавливает эти размеры
 // считывая их из файла??
 // файл открывается в главном окне(типа выбирается тема), и далее каждый виджет
  // инициализируется этой темой


// позиция курсора, при движении сравниваем положение курсора c сохраненной позицией
// если разница больше  размера элемента/2 выполняем поиск нового элемента
//  сохраненная позиция  поэтому должна быть серединой элемента
 int _cnt_pos_{0};
  Core::base_* select_elem{nullptr};
// указатель на текущий элемент ???


public:
 menu_(Point o={0,0}):Empty(o,10,10){}

    menu_(Point o,const std::initializer_list<Core::base_*> &ll ):Empty(o,10,10)
    {
      for ( auto* el :ll)
          add(el);
    }

  ~menu_()
    {
      clear();
    //  ~Empty();
    }
void clear();
    // при добавлении элемента изменяем размеры
    void add( Core::base_* it);


//    void show() const
//    {
//      for(auto b=l.cbegin(),e=l.cend();b!=e;++b)
//      {
//          (*b).callback();
//      }
//    }


    int handle(int ev) ;
    void draw();
 int find_item(int pos) ;

protected: // + style
   void draw(Point p, Core::base_& b,Color c=Color::grey);
};

}

#endif // MENU__H
