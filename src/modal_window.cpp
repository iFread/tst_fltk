#include "modal_window.h"

namespace Graph2 {
//********************************************************
//base_modal
void base_modal::set_callback(Core::base_cb *b, const std::string &s)
{
  lb_.text(s);
  cb_=b;
  bn_ok.callback([](Address,Address w2)
  { //PS: здесь теряется весь смысл аргументов
      Graph::reference_to<Core::base_cb>(w2).callback();

  },cb_) ;

}

void base_modal::init(){
    hide();
    set_modal();
    attach(bn_ok);
    attach(bn_cncl);
    attach(lb_);
    show();


    }
}


