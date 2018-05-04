#ifndef LIST_HPP_INCLUDED
#define LIST_HPP_INCLUDED

#include <string>
#include <sstream>
#include <vector>
#include "graphics.hpp"
#include "widget.hpp"
#include "window.hpp"

class list: public Widget {
protected:
// public:
    std::vector<std::string> elements;
    int focus;
    int iter;
    int capacity;
    double scrollsize;
    int scroll_place_size;
    int chosen;
    int szoveg_kezdete_x;
    std::vector<int> fuggolegesvonal;
    std::vector<int> also_kapcsolo;
    std::vector<int> felso_kapcsolo;
    std::vector<int> scroll_oszlop;
    std::vector<int> felnyil;
    std::vector<int> lenyil;
public:
    list(int x, int y, int sx, int sy,std::vector<std::string> _elements);
    void draw() ;
    void handle(genv::event ev);
    void do_the_job();
    std::string value_of_widget();
    std::string widget_type();
    void elem_hozzaad(std::string sz);
};

#endif // LIST_HPP_INCLUDED
