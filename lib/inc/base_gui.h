 #ifndef BASE_GUI_H_
 #define BASE_GUI_H_

#include <Fl/Fl_Widget.H>
#include "point.h"
#include <string>
#include <vector>
#include "simple_item.h"
 //#include "window.h"
namespace Graph {

using Address= void*;
using  Callback=void(*)(Address,Address);

template <typename T>
T& reference_to(Address ptr){return  *static_cast<T*>(ptr);}




//template <typename T> T& content(Address adr){ return *reinterpret_cast<T*>(adr);}
//template <typename T> T& content2(Widget *adr){ return *reinterpret_cast<T*>(adr);}



 class window;
class Widget {

public:
// Widget(Fl_Widget* p=nullptr):pw(p){}
    Widget(Point p, int ww, int hh,const std::string &s="", Callback cb=nullptr ):
        own(nullptr),pw(nullptr),loc(p),w_(ww),h_(hh),label(s),do_it(cb){}

    // копирование виджетов недоступно
  Widget(const Widget &w) =delete;
  Widget& operator=(const Widget& w)=delete;
 // нужно перемещение ресурса ( Fl_Widget* pw)

Widget(Widget&& w):own(w.own),pw(w.pw),loc(w.loc),w_(w.w_),h_(w.h_),label(w.label) ,do_it(nullptr){
w.pw=nullptr;
w.own=nullptr;
}
  virtual ~Widget();

protected:
 window *own;  // Fl_Widget ???
 Fl_Widget *pw;
 Point loc;
 int w_,h_;
 std::string label;
 Callback do_it;

 // методы работы с виджетами
public:
  void attach(window &w);

  void hide();
  void show();
  void move(int x,int y);
  void set_label(const std::string &s){label=s;if(pw)pw->label(label.c_str());}
  int w() const {return w_;}
  int h() const {return h_;}
  virtual void resize(int w,int h);
  Point position() const {return loc;}
 void set_position(Point x){loc=x;if(pw)pw->position(loc.x(),loc.y());}
  void callback(Callback,Address);

  // virtual int handle(int e) {return pw->handle(e);}

   virtual void create(Point p,int w,int h)=0;
  virtual Widget& create()=0;

  //  template<typename T>
   Fl_Widget& content() {return *pw;} //{return *reinterpret_cast<T&>(pw);}


  // template< class T>
   Fl_Widget& operator->(){return *pw;}
};

// this class on creating set Fl_Widget::user_data  how Widget*
class Label:public Widget
{
public:
    Label(Point p,int w,int h,const std::string &s=""):Widget(p,w,h,s){}
protected:
    void create(Point p,int w,int h);
    Widget& create();
private:
    void callback(Callback ,Address ){}
};
class Empty:public Widget
{


public:
    Empty(Point p,int w,int h,const std::string& s=""):Widget(p,w,h,s){}
    Empty(Empty&& e):Widget(std::move(e)){}
    virtual void draw() =0;
    virtual int handle(int e)=0;
   virtual ~Empty(){ /*if(pw)pw->user_data(0);*/}
     void resize(int x,int y) {
            // pw->resize(loc.x(),loc.y(),w,h);
           //w()=w;
           //h_=h;
         Widget::resize(x,y);
                              }

protected:
    void create(Point p,int w,int h);
    Widget& create();

};



class Button:public Widget{
public:
    Button(Point x, int w,int h,const std::string &s="",Callback cb=nullptr):Widget(x,w,h,s,cb){}

   Fl_Widget& content();
protected:
   void create(Point p,int w,int h);
  virtual Widget& create();
};



class In_Box:public Widget{

public:

    enum Align{left,right,center};
    In_Box(Point p,int w,int h, const std::string & s=""):Widget(p,w,h,s){}
    In_Box(In_Box&& bx):Widget(std::move(bx)){}
    Fl_Widget& content();

~In_Box(){}
    int get_int() const;
  float get_float()const;
     std::string get_string() const;
     void value(const char* s);
     void value(const std::string &s){value(s.c_str());}
     void value(int x){value(std::to_string(x).c_str());}
     void value(float x,int prec=2){
         std::string s=std::to_string(x);
       int dif_pos=s.find('.'); // позиция точки

       s=s.substr(0,dif_pos+1+prec);
         value( s.c_str());}//std::to_string(x).c_str());}

     //   void drawtext(Align a=Align::left);//   |    txt| - |txt....| - |   txt   |
protected:
  void create(Point p,int w,int h);
 virtual Widget& create();
};

class Out_Box:public Widget {
 public:
    Out_Box(Point p,int w,int h,const std::string &s=""):Widget(p,w,h,s){}
    Out_Box(Out_Box&&bx):Widget(std::move(bx)){}
   void create(Point p,int w,int h);
   virtual Widget& create();
   Fl_Widget& content();
       void put(int);
       void put(float);
  void put(float,int pr);
       void put(const std::string&s);
       ~Out_Box(){}
};

class Slider:public Widget{

    double value_{0.0};
public:
    Slider(Point p,int w,int h,const std::string &s=""):Widget(p,w,h,s){}
     Slider(Slider&& sl):Widget(std::move(sl)){}
    Fl_Widget& content();
    double value( ) const;
    void value(int v);
    void value(double v);//{reference_to<Fl_Slider>(pw).value(v ) ;}
    void step(int a);//{ue_+i;}
     void step(double a);
     double step()const;
     void range(int min,int max); // step==((max-min)/100)
    // установить минимум, максимум
      // значение шага
    ~Slider(){}
     void resize(int x,int y){Widget::resize(x,y);}
     void create(Point p,int w,int h);
protected:

virtual Widget& create(){return *new Slider(std::move(*this));}
};




//template <typename T>
class Simple_Choice:public Empty {

 sim_list<std::string> l;
 std::string *curent{nullptr};
 bool fl_visible{false};// флаг отображения
 Widget* menu_{nullptr};

public:
Simple_Choice(Point p,int w,int h):Empty(p,w,h){};
void add(std::string s){l.add(s);
                        curent=   &*( l[0])  ;
                       }

 void create(Point p,int w,int h);//{Widget::create(p,w,h);}
 Widget & create();

 int handle(int e);
 void draw();

 void  create_menu(Point p,sim_list<std::string> &l);
 // callbacck для меню, скрывающий меню


//void add(T t){l.add(t);}


//template <typename T>




};

}



#endif
