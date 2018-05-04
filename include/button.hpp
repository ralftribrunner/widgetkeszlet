#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED
#include "graphics.hpp"
#include "widget.hpp"
#include "window.hpp"

class button: public Widget {
protected:
 //public:
bool is_on;
std::string text_of_widget;
public:
    button(int x, int y, int sx, int sy);
    void draw();
    void handle(genv::event ev);
    void do_the_job();
    virtual void kaland()=0;
    std::string value_of_widget();
    std::string widget_type();
};

#endif // BUTTON_HPP_INCLUDED
