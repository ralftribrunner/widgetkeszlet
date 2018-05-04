#include "widget.hpp"
#include "graphics.hpp"

using namespace genv;

Widget::Widget(int x, int y, int sx, int sy) : _x(x), _y(y), _sx(sx), _sy(sy)
{
    _down=false;
    _up=false;
}

bool Widget::selected(int mouse_x, int mouse_y)
{
    return mouse_x>_x && mouse_x<_x+_sx && mouse_y>_y && mouse_y<_y+_sy;
}

bool Widget::is_up()
{
    return _up;
}

bool Widget::is_down()
{
    return _down;
}

void Widget::vonalrajzolo(std::vector<int> vonal)
{
    if (vonal.size()==4){
        gout<<move_to(vonal[0],vonal[1])<<color(255,255,255)<<line_to(vonal[2],vonal[3]);
    }
}

void Widget::nyilrajzolo(std::vector<int> nyil)
{
    if (nyil.size()==6) {
      gout << move_to(nyil[0], nyil[1]) <<color(255,0,0)<<line_to(nyil[2],nyil[3])<<line_to(nyil[4],nyil[5]);
    }
}

void Widget::dobozrajzolo(std::vector<int> doboz, int r, int g,int b)
{
    if (doboz.size()==4)
    {
        gout<<move_to(doboz[0],doboz[1])<<color(r,g,b)<<box(doboz[2],doboz[3]);
    }
}
