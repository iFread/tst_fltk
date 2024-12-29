 #include "base_gui.h"
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Output.H>
#include <Fl/Fl_Input.H>
#include <Fl/Fl_Slider.H>
#include <Fl/Fl_Box.H>
#include "fl_widgets.h"
#include <typeinfo>

#include <iostream>
#include "window.h"


namespace Graph {

Widget::~Widget(){
 //  pw->hide();
//   own->detach(*this);
   // pw->user_data(0);
 if(pw){ delete pw;
 pw=nullptr;}

//own=nullptr;
 }

void Widget::attach(window &w)
{
 own=&w;
  create(loc,w_,h_);

//  /own->resizable(pw);
//own->attach(pw);
}

void Widget::show(){if(pw) pw->show();}
void Widget::hide(){if(pw)
                      pw->hide();}

void Widget::move(int x, int y){
  hide();
  loc=Point(loc.x_+x,loc.y_+y);
  pw->position(loc.x_,loc.y_);
  show();
 }

void Widget::resize(int w,int h)
{

 if( pw)
    pw->resize(loc.x(),loc.y(),w,h);
  w_=w;
  h_=h;
 //  own->redraw();

}

void Widget::callback(Callback cb,Address adr){

  do_it=cb;
 pw->callback(reinterpret_cast<Fl_Callback*>(do_it),adr);

}

void Widget:: create(Point p,int w,int h)
{
    loc=p;w_=w;h_=h;
  //  pw=new Fl_Box(loc.x(),loc.y(),w_,h_);
}
//***********************Label

void Label::create(Point p,int w,int h)
{
    Widget::create(p,w,h);
     pw=new Fl_Box(p.x(),p.y(),w_,h_,label.c_str());//label.c_str();
}


Widget& Label::create()
{
    return *new Label(std::move(*this));
}

// ********************EMPTY

void Empty::create(Point p,int w,int h)
{
loc=p;
w_=w;
h_=h;

 pw=new fl_empty(p,w,h);

 pw->user_data(this);
}

Widget& Empty::create()
{
    return  (*this);
}
// **************************************
// Label2

void Label2::draw()
{
    Font old=Font(fl_font(),fl_size());
   Color cold=fl_color();
 fl_rectf(loc.x(),loc.y(),w(),h(),bg.as_int());
 fl_color(cl.as_int());
 fl_font(f_.as_int(),fl_size());
 fl_draw(pw->label(),loc.x(),loc.y());
fl_color(cold.as_int());
fl_font(old.as_int(),old.fontsize());
}


  // button
//***************************

void Button::create(Point x,int w,int h)
{
    loc=x;
    w_=w;
    h_=h;
   pw= new Fl_Button(x.x_,x.y_,w,h,label.c_str());
}
Widget& Button::create(){

    return *new Button(std::move(*this));
}

Fl_Widget& Button::content(){return reference_to<Fl_Button>(pw);}

//***********************************************
void In_Box::create(Point x,int w,int h) {
 //Fl_Input *p=
    loc=x;
    w_=w;
    h_=h;
    pw= new Fl_Input(x.x(),x.y(),w,h,label.c_str());
//p->box(Fl_Boxtype:: FL_UP_FRAME  );
// p->value("27");
//return p;
}

Widget& In_Box::create(){

    return *this;
}

Fl_Widget &In_Box:: content(){return  reference_to<Fl_Input>(pw);}

int In_Box:: get_int() const{

   const char *s=  reference_to<Fl_Input>(pw).value();
    //return pw->;
  // нужно проверить что строка содержит корректные числа
   // возможно перегрузить для дробных чисел, atof()
  // std::cout<<"in func, value = "<<s<<"\n";
   return  atoi(s);
}
std::string In_Box::get_string() const
{
    return reference_to<Fl_Input>(pw).value();
}

void In_Box::value(const char* s)
{
  reference_to<Fl_Input>(pw).value(s);

}

float In_Box:: get_float()const
{
    const char*s=reference_to<Fl_Input>(pw).value();
    return atof(s);
}

//******************************************************************
void Out_Box::create(Point p, int w, int h)
{
loc=p;
w_=w;
h_=h;
   pw= new Fl_Output(p.x(),p.y(),w,h,label.c_str());
 //op->value("determinant");
  // return op;
}

Fl_Widget& Out_Box::content(){return  reference_to<Fl_Output>(pw);}


Widget& Out_Box::create(){

    return * this;
}

void Out_Box::put(int n)
{
  reference_to<Fl_Output>(pw).value(std::to_string(n).c_str());
}

void Out_Box::put(float f){
  reference_to<Fl_Output>(pw).value(std::to_string(f).c_str());
}

void Out_Box::put(float a,int pr)
{ // найти целую часть и обрезать  до pr+1; для точки
 (a<0)?++pr:0;
    int i_a=a;
    int cnt=0;
    while(i_a)
    {
      i_a/=10;
      cnt++;
    }
   (cnt==0 )?++pr:0;

   std::string s=std::to_string(a+0.005);
  s.erase(cnt+pr+1);
   reference_to<Fl_Output>(pw).value(s.c_str());

}
void Out_Box::put(const std::string &s)
{
  reference_to<Fl_Output>(pw).value(s.c_str());
}

//****************************Slider

Fl_Widget& Slider::content(){return  reference_to<Fl_Slider>(pw);}

void Slider::create(Point p,int w,int h)
{
  loc=p;w_=w;h_=h;
pw=new Fl_Slider(FL_HOR_FILL_SLIDER,p.x_,p.y_,w,h,label.c_str());
//Fl_Slider& r=reference_to<Fl_Slider>(pw);
//

// r.slider_size( 1);

  //r.precision(0);
// r.maximum(100);
// r.minimum(10);
}

double Slider:: value()const{

    double v=reference_to<Fl_Slider>(pw).value() ;
//  reference_to<Fl_Slider>(pw).step(v);
//std::cout<<"value slider = "<<v <<"\n";
 return v;
}
void Slider::value(int v)
{
  reference_to<Fl_Slider>(pw).value(v ) ;
}

 void Slider:: value(double v){reference_to<Fl_Slider>(pw).value(v ) ;}
void Slider:: step(int a)
{
reference_to<Fl_Slider>(pw).step(a);

}
void Slider:: step(double a)
{
reference_to<Fl_Slider>(pw).step(a);

}

double Slider::step() const
 {return  static_cast<Fl_Slider*>(pw)->step();}

void Slider::range(int min, int max)
{
 reference_to<Fl_Slider>(pw).bounds(min,max);
}

// Simple_Choice
void  Simple_Choice::create(Point p,int w,int h){
    Widget::create(p,w,h);

    //pw=new fl_empty(p,w,h);

    pw->user_data(this);
}
//template <typename T>
Widget& Simple_Choice:: create(){return *this;}
//template <typename T>




void Simple_Choice::  draw()
{
 if(fl_visible)
 { // размер листа
   fl_rect(loc.x(),loc.y(),w_,l.size()*h_,FL_GRAY0 );
 int pos=loc.y()+(h_-fl_height()/2);

 if(curent)
       fl_draw(curent->c_str(),loc.x()+2,pos);
int m_x=Fl::event_x();
int m_y=Fl::event_y();
std::cout<<"coord : "<<m_x<<", "<<m_y<<"\n";
std::cout<<"param :"<<loc.x()<<" to "<<loc.x()+w_<<", "<<pos<<" to "<<pos+h_<<"\n";
  fl_color(FL_BLACK);
for(size_t i=0;i<l.size();++i)
   {
  // if(l[i].value())
if(&l[i].value() ==curent) continue;

if((m_x>=loc.x()&&m_x<loc.x()+w_)&&(m_y>=pos&& m_x<pos+h_)) {
    fl_rect(loc.x(),pos-h_,w_,h_,FL_GREEN);

}
pos+=h_;
fl_draw((l[i].value()).c_str(),loc.x()+2,pos);

}
 } else {
    fl_rect(loc.x(),loc.y(),w_,h_,FL_GRAY0);
if(curent) {

   int h=fl_height();
   h=(h_- h/2);
    fl_draw(curent->c_str(),loc.x()+5,loc.y_+h);
   }
 }
}

int  Simple_Choice:: handle(int e)
{
    switch (e) {

    case FL_PUSH:
        // при нажатии кнопки ,если fl_visible - делаем выбор
        switch (Fl::event_button()) {
        case FL_LEFT_MOUSE:
            if(fl_visible){
             std::cout<<"new enter\n";//
            fl_visible=false;
             }
            else
            {
                fl_visible=true;

            }
            break;


        }
    break;

    case FL_LEAVE:
//fl_visible=false;
//pw->redraw();
        break;

    }

    return e;
}

void Simple_Choice:: create_menu(Point p,sim_list<std::string> &l){


}
}



