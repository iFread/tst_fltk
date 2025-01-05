#include "item_menu.h"

#include "menu_.h"

 //using namespace Graph2;


namespace Core
{
 using  menu_=Graph2::menu_;

 menu_ *sub_menu::create_menu()
 {

    Graph2::menu_*m= new  Graph2::menu_ ;

for(auto el=l_.begin(),e=l_.end();el!=e;++el)
    m->add(*el);

return m;
 }





}
