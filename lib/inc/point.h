#ifndef POINT_H
#define POINT_H
#include <cmath>

const float fl_eps=0.001;
struct Point{

  //int x_,y_;
    float x_,y_,z_;
public:
     Point (float x, float y,float z=0.00):x_(x),y_(y),z_(z){}
 // Point(int x,int y):x_(x),y_(y){}
   Point():x_(NAN),y_(NAN) {}
  bool isValid()const {if(x_!=x_||y_!=y_||z_!=z_) return false; return true;}
  float x() const{return x_;}
   float  y() const{return y_;}
   float & x(){return  x_;}
   float & y(){return  y_;}
   float &z() {return z_;}
float z() const{ return z_;}
   bool operator==(const Point &p) const
  {
      return fabs(x_- p.x_)< fl_eps &&fabs(y_-p.y_) < fl_eps &&fabs(z_-p.z_) < fl_eps;
  }
  bool operator!=(const Point &p) const {return !(*this==p);}
  Point operator+(float i) const {return Point{x_+i,y_+i,z_+i};}
  Point operator-(float i) const {return Point{x_-i,y_-i,z_-i};}
  Point operator*(float i) const {return Point{x_*i,y_*i,z_*i};}
  bool operator<(const Point &p)const {
                                if(*this==p) return false;          //если точки равны то не меньше
                                      if(fabs(x_ -p.x())<fl_eps)    // если равны по x
                                              return y_<p.y_;      // значит не равны по y
                                        return x_<p.x_;
                                       }

  // операторы работы с точкой больше оперируют векторам,
virtual ~Point(){}
};

inline Point operator+(const Point &p1, const Point& p2){

    return Point(p1.x()+p2.x(),p1.y()+p2.y(),p1.z()+p2.z());
}

namespace command {



struct Point
{
int x_,y_,z_;

Point():x_(-1),y_(-1),z_(-1){}
Point(int x,int y,int z=0):x_(x),y_(y),z_(z){}

bool equal(const Point &p)
{
    return x_==p.x_&&y_==p.y_&&z_==p.z_;
}



};
}
// struct vector2d, так же пара чисел, но поведение как у отрезка :
// длина,




#endif // POINT_H
