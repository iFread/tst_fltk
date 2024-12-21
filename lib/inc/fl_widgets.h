#ifndef FL_WIDGETS_H
#define FL_WIDGETS_H
#include <FL/Fl_Widget.H>

class Point;
namespace Graph {




class fl_empty:public Fl_Widget
{

public:
 fl_empty(Point p,int w,int h);
 ~fl_empty(){

 }
//void resize(int w,int h);
void draw() override;
int handle(int ev) override;
};

}
#endif // FL_WIDGETS_H
