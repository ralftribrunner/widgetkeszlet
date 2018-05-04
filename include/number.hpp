#ifndef NUMBER_HPP_INCLUDED
#define NUMBER_HPP_INCLUDED

#include <string>
#include <sstream>
#include "graphics.hpp"
#include "widget.hpp"
#include "button.hpp"

class number: public Widget {
 public:
    bool upkey;
    bool downkey;
    bool uppage;
    bool downpage;
    std::stringstream ss;
    int textval;
    int minval;
    int maxval;
    bool chosen;
    std::vector<int> fuggolegesvonal;
    std::vector<int> vizszintesvonal;
    std::vector<int> felnyil;
    std::vector<int> lenyil;
public:
    number(int x, int y, int sx, int sy,int maximum,int minimum);
    void draw() ;
    void handle(genv::event ev);
    bool is_upkey();
    bool is_downkey();
    bool is_uppage();
    bool is_downpage();
    void do_the_job();
    void nullaz();
    std::string value_of_widget();
    bool is_chosen();
    bool is_on_number();
    std::string widget_type();
};

#endif // NUMBER_HPP_INCLUDED
