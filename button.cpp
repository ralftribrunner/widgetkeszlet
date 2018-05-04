#include "graphics.hpp"
#include "widget.hpp"
#include "button.hpp"
#include <string>

using namespace genv;

button::button(int x,int y, int sx, int sy):Widget(x,y,sx,sy)
{
    is_on=false;
    text_of_widget="Ooookay!";
}

void button::draw()
{
    if (!is_on) {
        gout<<move_to(_x,_y)<<color(255,238,191)<<box(_sx,_sy);
        gout<<move_to(_x,_y+_sy/2)<<color(0,0,0)<<text(text_of_widget);
    }
    if (is_on) {
        gout<<move_to(_x,_y)<<color(37,176,83)<<box(_sx,_sy);
        gout<<move_to(_x,_y+_sy/2)<<color(0,0,0)<<text(text_of_widget);
    }

}

void button::handle(event ev)
{
    if (selected(ev.pos_x,ev.pos_y) and ev.button>0 and ev.button==btn_left){
       is_on=!is_on;
       kaland(); ///is_on=!is_on;
    }
}

void button::do_the_job()
{

}

std::string button::value_of_widget()
{
    if (is_on) {
      return ("true");
    }
    if (!is_on) {
      return ("false");
    }
}

std::string button::widget_type() {
    return "button";
}
