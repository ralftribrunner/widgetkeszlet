#ifndef GRID_HPP_INCLUDED
#define GRID_HPP_INCLUDED
#include "graphics.hpp"
#include "widget.hpp"
#include "window.hpp"
#include <vector>
#include <random>
#include <time.h>

using namespace genv;

struct mezo {
    bool hajo;
    bool volt_mar;
    bool talalt;
};

class grid:public Widget {
    public:
    std::vector<std::vector<mezo>> mezok;
    double chosen_x, chosen_y;
    bool player_ready;
    std::string grid_type;
    int hp;
    int public_flotta_size;
    int public_cell_size;
    std::string aktirany;
public:
    grid(int x, int y, int sx, int sy, std::string type);
    bool racs_selected(int x,int y);
    void draw();
    void do_the_job();
    void handle(event ev);
    void flotta_allitas_player(event ev);
    virtual void action_stations()=0;
    virtual void over()=0;
    virtual bool another_selected(int x, int y)=0;
    virtual void irany_lekerdezes()=0;
    std::string value_of_widget();
    std::string widget_type();
};

#endif // GRID_HPP_INCLUDED
