#include "list.hpp"
#include "graphics.hpp"
#include <vector>
#include <string>

using namespace genv;

list::list(int x,int y, int sx, int sy,std::vector<std::string> _elements):Widget(x,y,sx,sy)
{
    elements=_elements;
    focus=-1;
    iter=0;
    capacity=_sy/gout.cascent();
    scrollsize= (double)capacity/elements.size();
    scroll_place_size=_sy*0.8-_sy*0.2;
    chosen=-1;

    szoveg_kezdete_x=_x+0.05*_sx;

    fuggolegesvonal.push_back(_x+_sx*0.9);  ///x1
    fuggolegesvonal.push_back(_y);          ///y1
    fuggolegesvonal.push_back(_x+_sx*0.9);///x2
    fuggolegesvonal.push_back(_y+_sy);    ///y2

    felso_kapcsolo.push_back(_x+_sx*0.9); ///x_kezdeti
    felso_kapcsolo.push_back(_y); ///y_kezdeti
    felso_kapcsolo.push_back(_sx*0.1); ///x_meret
    felso_kapcsolo.push_back(_sy*0.2); ///y_meret

    also_kapcsolo.push_back(_x+_sx*0.9);
    also_kapcsolo.push_back(_y+_sy*0.8);
    also_kapcsolo.push_back(_sx*0.1);
    also_kapcsolo.push_back(_sy*0.2);

    scroll_oszlop.push_back(_x+_sx*0.91);
    scroll_oszlop.push_back(_y+_sy*0.2);
    scroll_oszlop.push_back(0.09*_sx);
    scroll_oszlop.push_back(0.6*_sy);

    felnyil.push_back(_x+_sx*0.92); ///x_bal
    felnyil.push_back(_y+_sy*0.1); ///y_bal
    felnyil.push_back(_x+_sx*0.95); ///x_közép
    felnyil.push_back(_y+_sy*0.05); ///y_közép
    felnyil.push_back(_x+_sx*0.98); ///x_jobb
    felnyil.push_back(_y+_sy*0.1); ///y_jobb

    lenyil.push_back(_x+_sx*0.92);
    lenyil.push_back(_y+_sy*0.9);
    lenyil.push_back(_x+_sx*0.95);
    lenyil.push_back(_y+_sy*0.95);
    lenyil.push_back(_x+_sx*0.98);
    lenyil.push_back(_y+_sy*0.9);
}

void list::draw()
{
    gout << move_to(_x, _y-1) << color(255,255,255) << box(_sx, _sy+1);
    gout << move_to(_x+1,_y+1) << color(0,0,0) << box(_sx-2, _sy-2);
    vonalrajzolo(fuggolegesvonal);
    dobozrajzolo(felso_kapcsolo,255,255,255);
    dobozrajzolo(also_kapcsolo,255,255,255);
    nyilrajzolo(felnyil);
    nyilrajzolo(lenyil);
    if (elements.size()<=capacity)
    {
        dobozrajzolo(scroll_oszlop,0,200,0);
    }
    else {
        gout << move_to(scroll_oszlop[0],scroll_oszlop[1]+iter*(scroll_place_size/elements.size()))
        << color(0,200,0) <<box(scroll_oszlop[2],scrollsize*scroll_place_size);
    }

    int i=0;
    int j=0;
    for (auto a:elements) {
        if (_y+i+gout.cascent()<_y+_sy&&iter<=j) {
            if (j==chosen) {
                gout<<move_to( szoveg_kezdete_x,_y+i+gout.cascent())<<color(0,255,0)<<text(a);
            }

            else {
               gout<<move_to( szoveg_kezdete_x,_y+i+gout.cascent())<<color(255,255,255)<<text(a);
            }
            i+=gout.cascent();
        }
        j++;
    }
    if (focus>-1 && focus<elements.size() && _y+focus*gout.cascent()+gout.cascent()<_y+_sy &&iter+focus<elements.size()) {
        gout<<move_to(_x+1,_y+focus*gout.cascent())<<color(255,0,0)<<box(0.89*_sx,gout.cascent())<<
        move_to( szoveg_kezdete_x,_y+focus*gout.cascent()+gout.cascent())<<color(255,255,255)<<text(elements[iter+focus]);
    }

}

void list::handle(event ev)
{
    if (ev.type==ev_mouse && selected(ev.pos_x,ev.pos_y) && ev.button>0)
    {
        if (ev.pos_x>fuggolegesvonal[2] && ev.pos_x<_x+_sx )
            {
                if (ev.pos_y<felso_kapcsolo[1]+felso_kapcsolo[3] ) {
                    _up=true;
                }
                if (ev.pos_y>also_kapcsolo[1] ) {
                   _down=true;
                }
            }
        if (ev.button==btn_wheelup){
            _up=true;
        }
        if (ev.button==btn_wheeldown){
            _down=true;
        }

    }
    else
    {
        _up=false;
        _down=false;
    }
    if (ev.type==ev_mouse && selected(ev.pos_x,ev.pos_y) && ev.pos_x<fuggolegesvonal[2])
        {
            focus=(ev.pos_y-_y)/gout.cascent();
            if (ev.button>0 and ev.button==btn_left){
               chosen=iter+focus;
            }
            return;
        }

    else
        {
        focus=-1;
        }
}

void list::do_the_job()
{
    if (is_up()){
        if (!(iter==0)) {
          iter--;
        }
    }
    if (is_down()){
        if (elements.size()-iter<=capacity) {
          return;
        }
        else {
          iter++;
        }
    }
}

std::string list::value_of_widget()
{
    if (chosen>-1) {
      return elements[chosen];
    }
    else {
      return ("-");
    }
}

std::string list::widget_type() {
    return "list";
}

void list::elem_hozzaad(std::string sz) {
    elements.push_back(sz);
}
