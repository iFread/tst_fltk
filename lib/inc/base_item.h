#ifndef BASE_ITEM_H
#define BASE_ITEM_H
namespace Graph2
{

class base_
{
public:
    virtual ~base_(){}
};

template <typename T>
class item_:public base_
{
public:
    void callback(){ static_cast<T*>(this)->_callback();}
};


}



#endif // BASE_ITEM_H
