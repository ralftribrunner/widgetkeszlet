#ifndef WIDGET_HPP_INCLUDED
#define WIDGET_HPP_INCLUDED
#include <sstream>
#include<vector>
#include "graphics.hpp"

class Widget {
    protected:
        int _x, _y, _sx, _sy;
        bool _up, _down;
    public:
        Widget(int x, int y, int sx, int sy);
        void vonalrajzolo(std::vector<int> vonal);
        void nyilrajzolo(std::vector<int> nyil);
        void dobozrajzolo(std::vector<int> doboz, int r, int g, int b);
        bool selected(int mouse_x, int mouse_y);
        bool is_up();
        bool is_down();
        virtual void draw() = 0;
        virtual void handle(genv::event ev)=0;
        virtual void do_the_job()=0;
        virtual std::string value_of_widget()=0;
        virtual std::string widget_type()=0;
};

#endif // WIDGET_HPP_INCLUDED
