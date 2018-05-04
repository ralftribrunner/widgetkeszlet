#ifndef STATICTEXT_HPP_INCLUDED
#define STATICTEXT_HPP_INCLUDED

#include <string>
#include <sstream>
#include "graphics.hpp"
#include "widget.hpp"
#include "window.hpp"
class statictext: public Widget {
//protected:
 public:
    std::string text1;
    std::string password;
    int code;
    bool backspace;
    int iter;
    bool is_mouse;
public:
    statictext(int x, int y, int sx, int sy);
    void draw();
    void handle(genv::event ev);
    void do_the_job();
    std::string value_of_widget();
    bool is_backspace();
    std::string widget_type();
};


#endif // STATICTEXT_HPP_INCLUDED
