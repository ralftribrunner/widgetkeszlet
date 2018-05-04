#include "statictext.hpp"
#include "graphics.hpp"
#include <iostream>

using namespace genv;

statictext::statictext(int x,int y, int sx, int sy):Widget(x,y,sx,sy)
{
    text1="";
    password="";
    backspace=false;
    iter=text1.length();
}

void statictext::draw()
{
    gout << move_to(_x,_y) << color(255,255,255) << box(_sx, _sy);
    gout << move_to(_x+2,_y+2) << color(0,0,0) << box(_sx-4, _sy-4);
    gout << move_to(_x+0.05*_sx,_y+0.5*_sy)<<color(255,255,255)<</*text(password)*/text(text1);
    //gout << move_to(_x,_y+_sy+gout.cascent())<<color(255,255,255)<<text(text1);
}

void statictext::handle(event ev)
{
    if (ev.type==ev_mouse or ((ev.keycode<31 or ev.keycode>256) and ev.keycode!=key_backspace) ) is_mouse=true;
    else is_mouse=false;
    if (ev.type==ev_key && ev.keycode>0 && ev.keycode!=key_backspace) {
            code=ev.keycode;
            backspace=false;
    }
    if (ev.keycode==key_backspace) backspace=true;
}

bool statictext::is_backspace() {
    return backspace;
}

void statictext::do_the_job() {
    if (!is_mouse) {
      if (is_backspace() && text1.length()>0 )
    {
        text1.pop_back();
        password.pop_back();
    }
    else if (gout.twidth(text1)+_x+0.05*_sx<_x+0.95*_sx && !is_backspace()) {
        text1+=code;
        password+="*";
    }
    }

}

std::string statictext::value_of_widget() {
    return text1;
}

std::string statictext::widget_type() {
    return "statictext";
}


