#ifndef SIMPLE_ITEM_H
#define SIMPLE_ITEM_H
#include <iostream>
#include <cstring>
namespace Graph {

// связный список элементов,

// дописать возможность передачи компоратора для T

template <typename T>
class sim_list{

    template<typename U>
    struct Node{
     U data_;
     Node* next_;

     Node(U t):data_(t),next_(nullptr){}
   ~Node(){if(next_) delete next_;}
//U* operator->(){return &data_;}
     void add(Node* r)
   {
     if(next_)
          next_->add(r);
     else  next_=r;
    }

    };



    template<typename Iter>
    class Iterator{

        friend class sim_list<T>;
   public:
        typedef Iter iterator_type;
        typedef iterator_type & reference;
        typedef iterator_type* pointer ;
        typedef iterator_type value_type ;

    private:
      iterator_type*   value_; // здесь value - Node<T>
 // Node<Iter> val;          // а нам нужен value это само T
     Iterator(iterator_type * t):value_(t){} // не публичный конструктор
    public:
        //публичные конструкторы копирования и операторы присваивания
   Iterator(const Iterator &it):value_(it.value_){}
   Iterator& operator=(const Iterator& it){
   if(this==&it ) return *this;
     value_=it.value_;
           return *this;
   }
   Iterator(Iterator&& it):value_(std::move(it.value_)){it.value_=nullptr;}
   Iterator  operator=(Iterator&& it)
   {
       return Iterator(std::move(it));
   }
 value_type    operator*()const {return  *value_;}
value_type& operator*(){return *value_;}

 Iterator operator++()
 {
     return Iterator(value_->next);

 }

 operator bool(){return value_;}


 value_type* operator->(){return value_;}

// value_type* operator->(){return    value;}
//const value_type  operator->()const {return  value;}

  value_type& value(){  return   *value_ ;}
    };

    Node<T>* root{nullptr};
    size_t size_{0};
public:
    typedef Iterator<Node<T>> iterator ;
    typedef Iterator <const Node<T>> const_iterator;
    typedef Iterator<T> iter_t ;
    typedef Iterator<const T> const_iter_t ;

    sim_list(){}
    sim_list(const sim_list& l)
    {
        for(size_t i{};i<l.size();++i)
        {
         add(*(l[i]));
        }
    }

  sim_list& operator=(const sim_list& l)
  {
    if(&l==this) return *this;
   clear();  // очистить
   for(size_t i{};i<l.size();++i)
   {
      add(*(l[i]));
   }
   return *this;

  }
    ~sim_list(){delete root;}
void clear(){

   size_t sz=size();
   while (root)
   {
       Node<T> *d=root;
       root=root->next_;
       d->next_=nullptr;
       delete d;


   }
   size_=0;
}

  void add(size_t pos,T t)
  {
     if(pos<0)
          add(t); // при неверном индексе добавить в конец
        pos%=size_;

   Node<T> *p=new Node<T>(t);
  Node<T> *f= (*(*this)[pos]);
  p->next_=f->next_;
  f->next_=p;

  }

    void add(T t) // добавить в конец
     {
        if(root)
            root->add(new Node<T>(t));
   else root=new Node<T>(t);
 size_++;
    }

    void remove(T key)
    { // пройти по дереву,
        // если какая то data_==key удалить эту ноду
        Node<T>* r=root;
        // проверить на корень
        if(r&&memcmp(&r->data_,&key,sizeof (key)))
        {
          root=root->next_;
          r->next_=nullptr;
          delete r;
          size_--;
          return;

        }
        while (r->next_)
         {
           if(memcmp(&r->next_->data_,&key,sizeof (key)))
           {
               Node<T>* n=r->next_->next_;
              r->next_->next_=nullptr;
                delete r->next_;
               r->next_=n;
               size_--;
               break;
           }
 r=r->next_;
        }

    }

    void print()const
    {
      Node<T>* r=root;
      while(r)
      {
       std::cout<<r->data_<<" ";
       r=r->next_;
      }std::cout<<"\n";

    }
    // лист может быть пустым, и вернуть ссылку из пустого листа ??
    //iterator
   iter_t operator[](size_t i)
    { Node<T>* n=root;
       if(!n) return iter_t(nullptr);
       while(i--){
           if(n)
              n=n->next_;
          else
               return iter_t(nullptr);//iterator (nullptr);
       }
       return iter_t(&n->data_);// iterator(n);//->data_);
    }
   // iterator
   iter_t operator[](size_t i) const
    {
        Node<T>* n=root;
               while(i--){
                   if(n)
                      n=n->next_;
                  else
                       return       iter_t(nullptr); //iterator (nullptr);
               }
               return  iter_t(&n->data_);//iterator(n);//->data_);

    }

    size_t size()const{return size_;}
};

//*****************************************************
// not -tempalte list


 class list{

     struct Node{
         virtual~Node(){}
         virtual Node* next(){return nullptr;}
         virtual void remove()=0;
     };

     template<typename  T>
     struct Node_r:public  Node{
    T data_;
    Node_r* next_{nullptr};
   public:
    Node_r(T t):data_(t){}

    ~Node_r(){
              if(next_) delete  next_;
           }
//    void remove( Node* r)
//    {
////        if(r==this)
////            return;
//    Node_r* rem=this;
//        while (rem->next()) {

//       if(rem->next_==r) {
//       Node*d=rem->next();
//        rem->next_=static_cast<Node_r<T>*>(d->next());
//       if(d->next()){
//         static_cast<Node_r<T>*>(d)->next_=nullptr;
//       } delete d;

//       return;
//      }
//     //next()->remove(r);
//rem=static_cast<Node_r<T>*>(rem->next());
//    }
//    }

    void remove(){
       if(next_)
            delete(next_);//remove();
    }

    void add(T t){
    // Node_r*p=next_;
     if(next_)
      {  next_->add(t);
       //  return;
      } else
       next_=(new Node_r(t));
      }


    Node* next(){return next_;}

//    void remove(T t)
//    {

//      Node* rem=this;
//      // ищем следующий
//      while(rem->next_ && rem->data_!=rem->next_.data_)
//      {
//        rem=rem->next_;
//      } // r==rem->next
//      //
//      if(rem->next_->next_) // если у удаляемого элемента есть следующий, сохраним указатель на него
//           rem->next_=rem->next_->next;
//      delete r;
//    }
   };

   Node* root{nullptr};
    public:
    list(){}
    ~list(){
          delete  root;
       }
    template<typename T>
    void add(T t){
        if(root)
           static_cast<Node_r<T>*>(root)->add(t);
         else
      root=new Node_r<T>(t);
                 }
    template<typename T>
   void remove(T key) {
     Node_r<T> *rem= static_cast<Node_r<T>*>(root);
     // если в корне :
      if(rem->data_==key)
      {
        root= rem->next_;
        rem->next_=nullptr;
        delete rem;
      }
       else {
     while(rem->next_)
        { if(rem->next_->data_==key)
           { //
              Node_r<T>* del=rem->next_;
              rem->next_=rem->next_->next_;
             // delete del;
               del->next_=nullptr;
              delete  del;
              break;
          }
      rem=rem->next_;
      }
      }
    // delete rem;
      //root->remove(key);


   }
   template<typename T>
    Node* next(){return dynamic_cast<Node_r<T>>(root)->next();}


    template<typename T>
    void print() const {
        Node_r<T>*p=static_cast<Node_r<T>*>(root);
        while(p){
          std:: cout<< p->data_<<" ";
                  p=p->next_;
        } std::cout<<"\n";
    }
  // если root == nullptr вернет true, иначе false
    bool isEmpty(){return !root;}
};


}


#endif // SIMPLE_ITEM_H
