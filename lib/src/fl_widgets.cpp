#include "fl_widgets.h"
#include "base_gui.h"

namespace Graph
{

fl_empty::fl_empty(Point p,int w,int h):Fl_Widget(p.x(),p.y(),w,h){user_data(nullptr);}

void fl_empty::draw()
{

  if(user_data())
    reinterpret_cast<Graph::Empty*>(user_data())->draw();   // к чему cast
}

int fl_empty::handle(int ev)
{
  if(user_data())
 {     return static_cast<Graph::Empty*>(user_data())->handle(ev);   // к чему cast

  }
      return ev;
}


}
