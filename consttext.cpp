#include "consttext.hpp"
#include "graphics.hpp"
#include <iostream>

using namespace genv;

consttext::consttext(int x,int y, int sx, int sy, std::string alap):Widget(x,y,sx,sy)
{
    text1=alap;
}

void consttext::draw()
{
    gout << move_to(_x,_y) << color(255,255,255) << box(_sx, _sy);
    gout << move_to(_x+2,_y+2) << color(0,0,0) << box(_sx-4, _sy-4);
    gout << move_to(_x+0.05*_sx,_y+0.5*_sy)<<color(255,255,255)<<text(text1);
}

void consttext::handle(event ev)
{
}

void consttext::do_the_job() {
}

std::string consttext::value_of_widget() {
    return text1;
}

std::string consttext::widget_type() {
    return "consttext";
}
