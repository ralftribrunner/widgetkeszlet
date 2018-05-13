#ifndef CONSTTEXT_HPP_INCLUDED
#define CONSTTEXT_HPP_INCLUDED


#include <string>
#include <sstream>
#include "graphics.hpp"
#include "widget.hpp"
#include "window.hpp"


class consttext: public Widget {
//protected:
 public:
    std::string text1;
public:
    consttext(int x, int y, int sx, int sy, std::string alap);
    void draw();
    void handle(genv::event ev);
    void do_the_job();
    std::string value_of_widget();
    std::string widget_type();
};



#endif // CONSTTEXT_HPP_INCLUDED
