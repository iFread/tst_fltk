#ifndef ITEM__H
#define ITEM__H

#include <string>
#include "cb_item.h"
namespace Core {


struct Base_Item
{
  std::string name_;
  std::string name() const {return name_;}
   virtual ~Base_Item()=0  ;


          Base_Item(const std::string &s ):name_(s){}

};


// ELEMENT
template <typename T>
struct iitem:public Base_Item
{

  base_cb* cb_;
public:

  iitem():Base_Item("noname"),cb_(nullptr){}

  template<typename Fx, typename ...Arg>
  iitem(const std::string& s ) {}

};


}



#endif // ITEM__H
