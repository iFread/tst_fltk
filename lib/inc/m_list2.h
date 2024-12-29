#ifndef MY_LIST_2_H
#define MY_LIST_2_H
#include <iostream>
#include<type_traits>
#include <iterator>
#include <initializer_list>
template<typename T>
class  list2 {
template <typename D>
struct Node
{
  
Node(D d):data_(d),nxt_(nullptr),prv_(nullptr){}    

 D*data() {return  &data_;}
~Node(){}

 
 void add(Node *n)
{
     if(!n) return;
  n->nxt_=nxt_;// 
    nxt_=n;
if(n->nxt_) // если была последующая Node
    n->nxt_->prv_=n;
 n->prv_=this;
     
}
 //D& operator*(){return data_;}
  D data_;// для копии 
 Node* nxt_;
 Node* prv_;
 
};


   // специализация для указателей
// не освобождаем память
template<typename Tp>
struct Node<Tp*>
{
Node(Tp* t):tp_(t),nxt_(nullptr),prv_ (nullptr){}
  Tp*   data(){return   tp_;} 
 ~Node(){}    
    
 void add(Node *n)
{
 if(!n) return;
  n->nxt_=nxt_;// 
    nxt_=n;
if(n->nxt_) // если была последующая Node
    n->nxt_->prv_=n;
 n->prv_=this;
    
}   

//Tp* operator*(){return tp_;}


 bool operator==(const Node<Tp*> other){

     return tp_==other.tp_;
 }
 
  Tp* tp_;
  Node* nxt_;
  Node*prv_;
  

};
template<typename Iter> // для <int*> Iter = int*
class Iterator: public std::iterator<std::bidirectional_iterator_tag
                                        ,Iter >
{

friend list2;
public: 
 using value_type = typename std::remove_pointer<Iter>::type; 
 using pointer=value_type*;
 using reference=value_type&;
 
 typedef std::bidirectional_iterator_tag iterator_category;

Iterator(Node<Iter>* it):it_(it){}
  //template<typename It>
  //Iterator(Node<It*>* n):it_{}
 Iterator   operator++(){//if(!it_)    return Iterator(nullptr);
   if(it_)
     it_=it_->nxt_;
   return *this;
                      }
  Iterator   operator--(){ //if(!it_) return Iterator(nullptr);
 if(it_)
      it_=it_->prv_;
   return *this;
  }
  
  // поэтому возвращаемый здесь тип int*&
value_type& operator*() {return          *(it_->data())  ;}   
value_type operator*() const {return *(it_->data());}
 
 bool operator!=(const Iterator& it) const 
 {
   return  !(it.it_==it_);
} 

bool operator==(const Iterator &it) const {return it.it_==it_;}
operator bool() {return it_;}
private:
void _insert(Node<Iter> *n)
{
 it_->add(n);   
}
bool _remove()
{
  if(!it_) return false;
  
  // если есть предыдущий 
  // то 1 -его nxt_ = к it_->nxt_; И it_->nxt_->prv_=it_->prv_;  
  Node<Iter>* dl_=it_;
    it_=it_->nxt_;
  
  if(dl_->prv_)   
   dl_->prv_->nxt_= it_;   //dl_->nxt_;

  if(it_)
      it_->prv_=dl_->prv_;
  
    
 delete dl_; 
  return true;
}
private:
    Node<Iter>* it_; 
};

// ***********************************
// специализация для указателя
template<typename Iter>
class Iterator<Iter*>: public std::iterator <std::bidirectional_iterator_tag
        ,Iter >
{
public:
    using value_type=Iter*;
    using difference_type= ptrdiff_t;
    using pointer_t=Iter**;
    using reference =T*&;

   typedef std::bidirectional_iterator_tag iterator_category;


private:
    Node<Iter*> *it_; // it_ --здесь указаьель
public:

    Iterator(Node<value_type>* f):it_(f){}


    Iterator operator++()
    {
        if(it_)
            it_=it_->nxt_;
         return *this;//Iterator(it_++);
    }

    Iterator operator--()
    {if(it_)
         it_=it_->prv_;
        return *this;

    }
    value_type operator*()
    {
        if(it_)
           return it_->data();
        return  nullptr;
    }

    bool operator!=(const Iterator& it) const
    {
      return  !(it.it_==it_); //
   }

    bool operator==(const Iterator& it) const
    {
        return it_==it.it_;
    }
    bool _remove()
    {
      if(!it_) return false;

      // если есть предыдущий
      // то 1 -его nxt_ = к it_->nxt_; И it_->nxt_->prv_=it_->prv_;
      Node<Iter*>* dl_=it_;
        it_=it_->nxt_;

      if(dl_->prv_)
       dl_->prv_->nxt_= it_;   //dl_->nxt_;

      if(it_)
          it_->prv_=dl_->prv_;


     delete dl_;
      return true;
    }

};


public:

list2():first_(nullptr),last_(nullptr){}
 explicit list2(const std::initializer_list<T> &l):first_(nullptr),last_(nullptr)
{
//  std::cout<<"initializer_list \n";
  for(auto el =l.begin(),en=l.end();el!=en;++el)
    push_back(*el);
}

  list2(const list2 &l):first_(nullptr),last_(nullptr)
{
//  for(auto cp=l.cbegin();cp!=cend();++cp)
//      push_back(*cp); 
  Node<T>*n =l.first_;
while(n)
{
 push_back(*n->data()); 
 n=n->nxt_;  
} 
  
}
list2& operator=(const list2 &l)
{
 if(this==&l) return *this; 
 clear();
Node<T>* n=l.first_;
while(n)
{
  push_back(*n->data());
  n=n->nxt_;
}
return *this;
  
    
}


  list2(list2&&l) noexcept: first_(nullptr),last_(nullptr)
{
  
  first_=l.first_;
  last_=l.last_;
     l.first_=l.last_=nullptr;
  
  
}
list2& operator=(list2&& l) noexcept
{
   if(this==&l) return *this;
  first_=l.first_;
  last_=l.last_;
  l.first_=l.last_=nullptr;
   return *this;
  
}
void push_back(const T& t)
{
   if(!first_)
   {
    first_=new Node<T>(t);   
    last_=first_;
   } else 
   {
    Node<T>* tmp=new Node<T>(t);
    last_->add(tmp);
    last_=last_->nxt_;
}
   sz_++;
}

void push_front(const T& t)
{
 if(!first_)
      push_back(t);
   else 
    {
      Node<T>* tmp=new Node<T>(t);
     tmp->nxt_=first_->nxt_;
      tmp->add(first_);
     first_=tmp;
  sz_++;
 }
    
}
void insert( Iterator<T> it,const T& t)
{
     it._insert(new Node<T>(t));
     sz_++;
}

Iterator <T> find(const T& t)
{
    Node<T> *tmp=first_;
   while(tmp && (tmp->data()!= t))
{
  tmp=tmp->nxt_;     
}  return Iterator<T>(tmp);
}


Iterator<T*> find(const T* t)
{
  Node<T*>* tmp=first_;
    while(tmp &&(tmp->data()!=t))
        tmp=tmp->nxt_;
    return Iterator<T*>(tmp);
}
// возвращает iterator на следующую Node
Iterator<T> remove(Iterator<T> it)
{
  if(it==begin()) 
   {
   first_=first_->nxt_;  
  } 
    if(it._remove())
        sz_--;

    return it;
}




Iterator<T> begin(){return Iterator<T>(first_);}
Iterator<T> end() {return Iterator<T>(nullptr);}
  Iterator<T> cbegin()const  {return Iterator<T>(first_);}
 Iterator<T> cend()const {return Iterator<T>(nullptr);}
bool empty() const { return !first_;}

void clear() 
{
 auto el=begin(); 
 while(el!=end())
   el=remove(el);
}
size_t size() const {
   // std::cout<<"list size = "<<sz_<<"\n";
    return sz_;}


~list2(){clear();}

private:
Node<T>* first_;
Node<T>* last_;
size_t sz_{0};
};


#endif
