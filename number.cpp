#include "number.hpp"
#include "graphics.hpp"
#include <iostream>



using namespace genv;

number::number(int x,int y, int sx, int sy,int maximum,int minimum):Widget(x,y,sx,sy)
{
    textval=0;
    chosen=false;
    minval=minimum;
    maxval=maximum;
    ss<<textval;
    fuggolegesvonal.push_back(_x+0.8*_sx);  ///x1
    fuggolegesvonal.push_back(_y);          ///y1
    fuggolegesvonal.push_back(_x+(0.8*_sx));///x2
    fuggolegesvonal.push_back(_y+_sy-1);    ///y2

    vizszintesvonal.push_back(_x+0.8*_sx);
    vizszintesvonal.push_back(_y+0.5*_sy);
    vizszintesvonal.push_back(_x+_sx-1);
    vizszintesvonal.push_back(_y+0.5*_sy);

    felnyil.push_back(_x+0.85*_sx); ///x_bal
    felnyil.push_back(_y+0.4*_sy);  ///y_bal
    felnyil.push_back(_x+0.9*_sx);  ///x_közép
    felnyil.push_back(_y+0.2*_sy);  ///y_közép
    felnyil.push_back(_x+0.95*_sx); ///x_jobb
    felnyil.push_back(_y+0.4*_sy);  ///y_jobb

    lenyil.push_back(_x+0.85*_sx);
    lenyil.push_back(_y+0.6*_sy);
    lenyil.push_back(_x+0.9*_sx);
    lenyil.push_back(_y+0.8*_sy);
    lenyil.push_back(_x+0.95*_sx);
    lenyil.push_back(_y+0.6*_sy);
}

void number::draw()
{
    if (chosen){
        gout << move_to(_x, _y) << color(255,185,0) << box(_sx, _sy);
    }
    else {
        gout << move_to(_x, _y) << color(255,255,255) << box(_sx, _sy);
    }
    gout << move_to(_x+2,_y+2) << color(0,0,0) << box(_sx-4, _sy-4);
    vonalrajzolo(fuggolegesvonal);
    vonalrajzolo(vizszintesvonal);
    nyilrajzolo(felnyil);
    nyilrajzolo(lenyil);
    gout << move_to(_x+0.05*_sx,_y+0.5*_sy)<<color(255,255,255)<<text(ss.str());

}

void number::handle(event ev)
{
    _up=false;
    _down=false;
    upkey=false;
    downkey=false;
    uppage=false;
    downpage=false;
    if (ev.type==ev_mouse&&selected(ev.pos_x,ev.pos_y) &&ev.button>0)
    {
        if (ev.pos_x<_x+_sx and ev.button==btn_left) {
           chosen=true;
        }
        if (chosen) {
            if (ev.pos_x>fuggolegesvonal[0] &&ev.pos_y<vizszintesvonal[3])
                {
                    _up=true;
                }
            if (ev.pos_x>fuggolegesvonal[0] &&ev.pos_y>vizszintesvonal[3])
                {
                    _down=true;
                }
        }

    }
    else
    {
        _down=false;
        _up=false;
        if (ev.type==ev_mouse&& selected(ev.pos_x,ev.pos_y)==false &&ev.button>0) chosen=false;
    }
    if (ev.type==ev_key &&chosen )
    {
            if (ev.keycode==key_up){
                upkey=true;
            }
            if (ev.keycode==key_down){
                downkey=true;
            }
            if (ev.keycode==key_pgup){
               uppage=true;
            }
            if (ev.keycode==key_pgdn){
                downpage=true;
            }
    }
    else
    {
        upkey=false;
        downkey=false;
        uppage=false;
        downpage=false;
    }

}

bool number::is_upkey()
{
    return upkey;
}

bool number::is_downkey()
{
    return downkey;
}

bool number::is_uppage()
{
    return uppage;
}

bool number::is_downpage()
{
    return downpage;
}

void number::do_the_job()
{
    if (is_up() or is_upkey()) {
        textval++;
    }
    if (is_down() or is_downkey()) {
      textval--;
    }
    if (is_uppage()) {
      textval+=10;
    }
    if (is_downpage()) {
      textval-=10;
    }
    if (textval>maxval) {
        textval=maxval;
    }
    if (textval<minval) {
      textval=minval;
    }
    ss.str("");
    ss<<textval;
}

void number::nullaz()
{
    textval=0;
}

bool number::is_chosen()
{
    return chosen;
}

std::string number::value_of_widget()
{
    return ss.str();
}

std::string number::widget_type() {
    return "number";
}

