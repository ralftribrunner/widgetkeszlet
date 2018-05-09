#include "graphics.hpp"
#include "grid.hpp"
#include "widget.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <sstream>
#include <random>
#include <time.h>

///Az sx, sy az egy sorban levo negyzetek szamat adja meg, nem a widget meretet.

const int cell_size=30;
const int flotta_size=5;
const int number_cruiser=2;
const int number_destroyer=2;
int felallitott_hajok_player=0;

using namespace genv;
using namespace std;

struct koord{
    int a,b;
};

grid::grid(int x,int y, int sx, int sy, std::string type):Widget(x,y,sx,sy)
{
    grid_type=type;
    public_cell_size=cell_size;
    hp=flotta_size+number_destroyer;
    public_flotta_size=flotta_size;
    for (size_t i=0;i<sy;i++) {
        std::vector<mezo> b;
            for (size_t j=0;j<sx;j++) {
                mezo a;
                a.hajo=false;
                a.volt_mar=false;
                a.talalt=false;
                b.push_back(a);
            }
        mezok.push_back(b);
    }
    chosen_x=-1;
    chosen_y=-1;
    player_ready=false;
    if (grid_type=="computer") {
        srand(time(0));
        std::vector<koord> gepi_hajok;
        for (int i=0;i<number_destroyer;i++) {
            koord c;
            koord d;
            c.a=rand()%_sx;
            c.b=rand()%_sy;
            int irany=rand()%4;
            if (irany==0) {
                d.a=c.a-1;
                d.b=c.b;
                if (d.a==-1) d.a+=2;
            }
            if (irany==1) {
                d.a=c.a+1;
                d.b=c.b;
                if (d.a==_sx) d.a-=2;
            }
            if (irany==2) {
                d.a=c.a;
                d.b=c.b-1;
                if (d.b==-1) d.b+=2;
            }
            if (irany==3) {
                d.a=c.a;
                d.b=c.b+1;
                if (d.b==_sy) d.b-=2;
            }
            bool ugyanaz=false;
            do {
                ugyanaz=false;
                for (auto v:gepi_hajok) {
                    if ((v.a==c.a and v.b==c.b) or (v.a==d.a and v.b==d.b) ) {
                         c.a=rand()%_sx;
                         c.b=rand()%_sy;
                         irany=rand()%4;
                            if (irany==0) {
                                d.a=c.a-1;
                                d.b=c.b;
                                if (d.a==0) d.a+=2;
                            }
                            if (irany==1) {
                                d.a=c.a+1;
                                d.b=c.b;
                                if (d.a==_sx) d.a-=2;
                            }
                            if (irany==2) {
                                d.a=c.a;
                                d.b=c.b-1;
                                if (d.b==0) d.b+=2;
                            }
                            if (irany==3) {
                                d.a=c.a;
                                d.b=c.b+1;
                                if (d.b==_sy) d.b-=2;
                            }
                         ugyanaz=true;
                    }
                }
            } while (ugyanaz==true);
            gepi_hajok.push_back(c);
            gepi_hajok.push_back(d);
        }
        for (int i=0;i<flotta_size-number_destroyer;i++) {
            koord c;
            c.a=rand()%_sx;
            c.b=rand()%_sy;
            bool ugyanaz=false;
            do {
                ugyanaz=false;
                for (auto v:gepi_hajok) {
                    if (v.a==c.a and v.b==c.b) {
                         c.a=rand()%_sx;
                         c.b=rand()%_sy;
                         ugyanaz=true;
                    }
                }

            } while (ugyanaz==true);
            gepi_hajok.push_back(c);
        }
        if (gepi_hajok.size()>0) {
           for (auto v:gepi_hajok) {
            mezok[v.a][v.b].hajo=true;
           }
        }
    }

}



void grid::draw()
{
     if (hp==0) {
    gout<<move_to(100,400)<<color(0,0,0)<<text("Over!");
    }
    for (size_t i=0;i<_sy+1;i++) {
        gout<<move_to(_x,_y+i*cell_size)<<color(0,0,0)<<line_to(_x+_sx*cell_size,_y+i*cell_size);
    }
    for (size_t i=0;i<_sx+1;i++) {
        gout<<move_to(_x+i*cell_size,_y)<<color(0,0,0)<<line_to(_x+i*cell_size,_y+_sx*cell_size);
    }
    for (size_t i=0;i<mezok.size();i++) {
        for (size_t j=0;j<mezok[i].size();j++) {
            if (mezok[i][j].hajo==true /*and grid_type=="player"*/) {
                gout<<move_to(_x+j*cell_size,_y+5+i*cell_size)<<color(0,255,0)<<box(10,10);
            }
            if (mezok[i][j].volt_mar==true) {
                if (mezok[i][j].talalt==true) {
                    gout<<move_to(_x+j*cell_size,_y+i*cell_size)<<color(255,0,0)<<line_to(_x+(j+1)*cell_size,_y+(i+1)*cell_size);
                    gout<<move_to(_x+(j+1)*cell_size,_y+i*cell_size)<<color(255,0,0)<<line_to(_x+j*cell_size,_y+(i+1)*cell_size);

                }
                else {
                    gout<<move_to(_x+j*cell_size,_y+i*cell_size)<<color(0,0,255)<<line_to(_x+(j+1)*cell_size,_y+(i+1)*cell_size);
                    gout<<move_to(_x+(j+1)*cell_size,_y+i*cell_size)<<color(0,0,255)<<line_to(_x+j*cell_size,_y+(i+1)*cell_size);
                }
            }
        }
    }
    gout<<move_to(_x,_y+cell_size*_sy+gout.cascent())<<color(0,0,0)<<text(value_of_widget());
}

bool grid::racs_selected(int x, int y)
{
    if (x>_x and x<_x+_sx*cell_size and y>_y and y<_y+_sy*cell_size) return true;
    else return false;
}


void grid::flotta_allitas_player(event ev)
{
     int aktx=-1;
     int akty=-1;
     if (ev.button==btn_left and ev.button>0 and racs_selected(ev.pos_x,ev.pos_y))
    {
        aktx=floor((ev.pos_x-_x)/cell_size);
        akty=floor((ev.pos_y-_y)/cell_size);
    }
    if (aktx>=0 and akty>=0 and mezok[akty][aktx].hajo==false and felallitott_hajok_player<number_destroyer) {
        bool siker=false;
        if (aktirany=="fel") {
            if (akty!=0 and mezok[akty-1][aktx].hajo==true) gout<<move_to(10,10)<<color(255,0,0)<<text("Ezt így nem lehet!");
            else if (akty==0) gout<<move_to(10,10)<<text("Ezt így nem lehet!");
            else {
                mezok[akty-1][aktx].hajo=true;
                siker=true;
            }
        }
        if (aktirany=="le") {
            if (akty!=_sy-1 and mezok[akty+1][aktx].hajo==true)gout<<move_to(10,10)<<text("Ezt így nem lehet!");
            else if (akty==_sy-1) gout<<move_to(10,10)<<text("Ezt így nem lehet!");
            else {
                siker=true;
                mezok[akty+1][aktx].hajo=true;
            }
        }
        if (aktirany=="jobbra") {
            if (aktx!=_sx-1 and mezok[akty][aktx+1].hajo==true) gout<<move_to(10,10)<<text("Ezt így nem lehet!");
            else if (aktx==_sx-1) gout<<move_to(10,10)<<color(255,0,0)<<text("Ezt így nem lehet!");
            else {
              mezok[akty][aktx+1].hajo=true;
              siker=true;
            }
        }
        if (aktirany=="balra") {
            if (aktx!=0 and mezok[akty][aktx-1].hajo==true) gout<<move_to(10,10)<<text("Ezt így nem lehet!");
            else if (aktx==0) gout<<move_to(10,10)<<text("Ezt így nem lehet!");
            else {
                siker=true;
                mezok[akty][aktx-1].hajo=true;
            }
        }
        if (siker==true) {
             mezok[akty][aktx].hajo=true;
            felallitott_hajok_player++;
        }
    }
    if (aktx>=0 and akty>=0 and mezok[akty][aktx].hajo==false and felallitott_hajok_player>=number_destroyer) {
        mezok[akty][aktx].hajo=true;
        felallitott_hajok_player++;
    }
    if (felallitott_hajok_player==flotta_size)
        {
            action_stations();
            player_ready=true;
        }
}

void grid::handle(event ev)
{
    if (hp>0) {
        if (grid_type=="computer") {
           if (player_ready==true) {
                if (ev.button==btn_left and ev.button>0 and racs_selected(ev.pos_x,ev.pos_y)) {
                    chosen_x=floor((ev.pos_x-_x)/cell_size);
                    chosen_y=floor((ev.pos_y-_y)/cell_size);
                }
                else {
                    chosen_x=-1;
                    chosen_y=-1;
                }
                for (size_t i=0;i<mezok.size();i++) {
                    for (size_t j=0;j<mezok[i].size();j++) {

                        if (chosen_y>-1 and chosen_x>-1 and chosen_y==i and chosen_x==j and mezok[i][j].hajo==true and mezok[i][j].volt_mar==false ) {
                            mezok[i][j].talalt=true;
                            hp--;
                        }
                        if (chosen_y>-1 and chosen_x>-1 and chosen_y==i and chosen_x==j) mezok[i][j].volt_mar=true;
                    }
                }
            }
        }
        if (grid_type=="player") {
            if (player_ready==false) {
                irany_lekerdezes();
                flotta_allitas_player(ev);
            }
            if (player_ready==true) {
                if (ev.button==btn_left and ev.button>0 and another_selected(ev.pos_x,ev.pos_y)) {
                    srand(time(0));
                    int fire_x=rand()%_sx;
                    int fire_y=rand()%_sy;
                    bool same=false;
                    do {
                        same=false;
                        if (mezok[fire_y][fire_x].volt_mar==true) {
                            fire_x=rand()%_sx;
                            fire_y=rand()%_sy;
                            same=true;
                        }
                    }   while (same==true);
                    mezok[fire_y][fire_x].volt_mar=true;
                    if (mezok[fire_y][fire_x].hajo==true) {
                        mezok[fire_y][fire_x].talalt=true;
                        hp--;
                    }
                }

            }
       }
    }
    else {
        over();
    }
}

void grid::do_the_job()
{

}

std::string grid::value_of_widget()
{
    std::stringstream ss;
    ss<<hp;
    return ss.str();
}

std::string grid::widget_type()
{
    return "racs";
}
