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
const int number_battleship=2;
const int number_cruiser=2;
const int number_destroyer=2;
const int number_singleton=2;
int flotta_size;
int felallitott_hajok_player=0;
int felallitott_hajok_player_singleton=0;
int felallitott_hajok_player_destroyer=0;
int felallitott_hajok_player_cruiser=0;
int felallitott_hajok_player_battleship=0;

using namespace genv;
using namespace std;

struct koord{
    int a,b;
};

grid::grid(int x,int y, int sx, int sy, std::string type):Widget(x,y,sx,sy)
{
    grid_type=type;
    public_cell_size=cell_size;
    hp=number_singleton+number_destroyer*2+number_cruiser*3+number_battleship*4;
    flotta_size=number_singleton+number_destroyer+number_cruiser+number_battleship;
    battle=true;
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
            for (int i=0;i<number_cruiser;i++) {
            koord e;
            koord f;
            koord g;
            e.a=rand()%_sx;
            e.b=rand()%_sy;
            int irany=rand()%4;
            if (irany==0) {
                f.a=e.a-1;
                f.b=e.b;
                g.a=e.a-2;
                g.b=e.b;
                if (g.a<0 and f.a<0) {
                    f.a=abs(f.a);
                    g.a=abs(g.a);
                }
                else if (g.a<0 and f.a==0) g.a=2;

            }
            if (irany==1) {
                f.a=e.a+1;
                f.b=e.b;
                g.a=e.a+2;
                g.b=e.b;
                if (f.a>_sx-1 and g.a>_sx-1) {
                    e.a-=2;
                    f.a-=2;
                    g.a-=2;
                }
                else if (f.a==_sx-1 and g.a>_sx-1) {
                    e.a-=1;
                    f.a-=1;
                    g.a-=1;
                }
            }
            if (irany==2) {
                f.a=e.a;
                f.b=e.b-1;
                g.a=e.a;
                g.b=e.b-2;
                if (g.b<0 and f.b<0) {
                    f.b=abs(f.b);
                    g.b=abs(g.b);
                }
                else if (g.b<0 and f.b==0) g.b=2;
            }
            if (irany==3) {
                f.a=e.a;
                f.b=e.b+1;
                g.a=e.a;
                g.b=e.b+2;
                if (f.b>_sx-1 and g.b>_sx-1) {
                    e.b-=2;
                    f.b-=2;
                    g.b-=2;
                }
                else if (f.b==_sx-1 and g.b>_sx-1) {
                    e.b-=1;
                    f.b-=1;
                    g.b-=1;
                }
            }
            bool ugyanaz=false;
            do {
                ugyanaz=false;
                for (auto v:gepi_hajok) {
                    if ((v.a==e.a and v.b==e.b) or (v.a==f.a and v.b==f.b) or (v.a==g.a and v.b==g.b) ) {
                         e.a=rand()%_sx;
                            e.b=rand()%_sy;
                            int irany=rand()%4;
                            if (irany==0) {
                                f.a=e.a-1;
                                f.b=e.b;
                                g.a=e.a-2;
                                g.b=e.b;
                                if (g.a<0 and f.a<0) {
                                    f.a=abs(f.a);
                                    g.a=abs(g.a);
                                }
                                else if (g.a<0 and f.a==0) g.a=2;

                            }
                            if (irany==1) {
                                f.a=e.a+1;
                                f.b=e.b;
                                g.a=e.a+2;
                                g.b=e.b;
                                if (f.a>_sx-1 and g.a>_sx-1) {
                                    e.a-=2;
                                    f.a-=2;
                                    g.a-=2;
                                }
                                else if (f.a==_sx-1 and g.a>_sx-1) {
                                    e.a-=1;
                                    f.a-=1;
                                    g.a-=1;
                                }
                            }
                            if (irany==2) {
                                f.a=e.a;
                                f.b=e.b-1;
                                g.a=e.a;
                                g.b=e.b-2;
                                if (g.b<0 and f.b<0) {
                                    f.b=abs(f.b);
                                    g.b=abs(g.b);
                                }
                                else if (g.b<0 and f.b==0) g.b=2;
                            }
                            if (irany==3) {
                                f.a=e.a;
                                f.b=e.b+1;
                                g.a=e.a;
                                g.b=e.b+2;
                                if (f.b>_sx-1 and g.b>_sx-1) {
                                    e.b-=2;
                                    f.b-=2;
                                    g.b-=2;
                                }
                                else if (f.b==_sx-1 and g.b>_sx-1) {
                                    e.b-=1;
                                    f.b-=1;
                                    g.b-=1;
                                }
                            }
                         ugyanaz=true;
                    }
                }
            } while (ugyanaz==true);
            gepi_hajok.push_back(e);
            gepi_hajok.push_back(f);
            gepi_hajok.push_back(g);
        }
        /// //////////////////////////////////
        for (int i=0;i<number_battleship;i++) {
            koord h;
            koord j;
            koord k;
            koord l;
            h.a=rand()%_sx;
            h.b=rand()%_sy;
            int irany=rand()%4;
            if (irany==0) {
                j.a=h.a-1;
                j.b=h.b;
                k.a=h.a-2;
                k.b=h.b;
                l.a=h.a-3;
                l.b=h.b;
                if (j.a<0 and k.a<0 and l.a<0) {
                    j.a=abs(j.a);
                    k.a=abs(k.a);
                    l.a=abs(l.a);
                }
                else if (k.a<0 and l.a<0) {
                    k.a+=3;
                    l.a+=4;
                }
                else if (l.a<0) l.a+=4;
            }
            if (irany==1) {
                j.a=h.a+1;
                j.b=h.b;
                k.a=h.a+2;
                k.b=h.b;
                l.a=h.a+3;
                l.b=h.b;
                if (j.a>_sx-1 and k.a>_sx-1 and l.a>_sx-1) {
                    h.a-=3;
                    j.a-=3;
                    k.a-=3;
                    l.a-=3;
                }
                else if (k.a>_sx-1 and l.a>_sx-1) {
                    h.a-=2;
                    j.a-=2;
                    k.a-=2;
                    l.a-=2;
                }
                else if (l.a>_sx-1) {
                    h.a-=1;
                    j.a-=1;
                    k.a-=1;
                    l.a-=1;
                }
            }
            if (irany==2) {
                j.a=h.a;
                j.b=h.b-1;
                k.a=h.a;
                k.b=h.b-2;
                l.a=h.a;
                l.b=h.b-3;
                if (j.b<0 and k.b<0 and l.b<0) {
                    j.b=abs(j.b);
                    k.b=abs(k.b);
                    l.b=abs(l.b);
                }
                else if (k.b<0 and l.b<0) {
                    k.b+=3;
                    l.b+=4;
                }
                else if (l.b<0) l.b+=4;
            }
            if (irany==3) {
                j.a=h.a;
                j.b=h.b+1;
                k.a=h.a;
                k.b=h.b+2;
                l.a=h.a;
                l.b=h.b+3;
                if (j.b>_sy-1 and k.b>_sy-1 and l.b>_sy-1) {
                    h.b-=3;
                    j.b-=3;
                    k.b-=3;
                    l.b-=3;
                }
                else if (k.b>_sy-1 and l.b>_sy-1) {
                    h.b-=2;
                    j.b-=2;
                    k.b-=2;
                    l.b-=2;
                }
                else if (l.b>_sy-1) {
                    h.b-=1;
                    j.b-=1;
                    k.b-=1;
                    l.b-=1;
                }
            }
            bool ugyanaz=false;
            do {
                ugyanaz=false;
                for (auto v:gepi_hajok) {
                    if ((v.a==h.a and v.b==h.b) or (v.a==j.a and v.b==j.b) or (v.a==k.a and v.b==k.b) or (v.a==l.a and v.b==l.b) ) {
                            h.a=rand()%_sx;
                            h.b=rand()%_sy;
                            int irany=rand()%4;
                            if (irany==0) {
                                j.a=h.a-1;
                                j.b=h.b;
                                k.a=h.a-2;
                                k.b=h.b;
                                l.a=h.a-3;
                                l.b=h.b;
                                if (j.a<0 and k.a<0 and l.a<0) {
                                    j.a=abs(j.a);
                                    k.a=abs(k.a);
                                    l.a=abs(l.a);
                                }
                                else if (k.a<0 and l.a<0) {
                                    k.a+=3;
                                    l.a+=4;
                                }
                                else if (l.a<0) l.a+=4;
                            }
                            if (irany==1) {
                                j.a=h.a+1;
                                j.b=h.b;
                                k.a=h.a+2;
                                k.b=h.b;
                                l.a=h.a+3;
                                l.b=h.b;
                                if (j.a>_sx-1 and k.a>_sx-1 and l.a>_sx-1) {
                                    h.a-=3;
                                    j.a-=3;
                                    k.a-=3;
                                    l.a-=3;
                                }
                                else if (k.a>_sx-1 and l.a>_sx-1) {
                                    h.a-=2;
                                    j.a-=2;
                                    k.a-=2;
                                    l.a-=2;
                                }
                                else if (l.a>_sx-1) {
                                    h.a-=1;
                                    j.a-=1;
                                    k.a-=1;
                                    l.a-=1;
                                }
                            }
                            if (irany==2) {
                                j.a=h.a;
                                j.b=h.b-1;
                                k.a=h.a;
                                k.b=h.b-2;
                                l.a=h.a;
                                l.b=h.b-3;
                                if (j.b<0 and k.b<0 and l.b<0) {
                                    j.b=abs(j.b);
                                    k.b=abs(k.b);
                                    l.b=abs(l.b);
                                }
                                else if (k.b<0 and l.b<0) {
                                    k.b+=3;
                                    l.b+=4;
                                }
                                else if (l.b<0) l.b+=4;
                            }
                            if (irany==3) {
                                j.a=h.a;
                                j.b=h.b+1;
                                k.a=h.a;
                                k.b=h.b+2;
                                l.a=h.a;
                                l.b=h.b+3;
                                if (j.b>_sy-1 and k.b>_sy-1 and l.b>_sy-1) {
                                    h.b-=3;
                                    j.b-=3;
                                    k.b-=3;
                                    l.b-=3;
                                }
                                else if (k.b>_sy-1 and l.b>_sy-1) {
                                    h.b-=2;
                                    j.b-=2;
                                    k.b-=2;
                                    l.b-=2;
                                }
                                else if (l.b>_sy-1) {
                                    h.b-=1;
                                    j.b-=1;
                                    k.b-=1;
                                    l.b-=1;
                                }
                            }
                         ugyanaz=true;
                    }
                }
            } while (ugyanaz==true);
            gepi_hajok.push_back(h);
            gepi_hajok.push_back(j);
            gepi_hajok.push_back(k);
            gepi_hajok.push_back(l);
        }
        /// /////////////////////////////////////////
        for (int i=0;i<number_singleton;i++) {
            koord w;
            w.a=rand()%_sx;
            w.b=rand()%_sy;
            bool ugyanaz=false;
            do {
                ugyanaz=false;
                for (auto v:gepi_hajok) {
                    if (v.a==w.a and v.b==w.b) {
                         w.a=rand()%_sx;
                         w.b=rand()%_sy;
                         ugyanaz=true;
                    }
                }

            } while (ugyanaz==true);
            gepi_hajok.push_back(w);
        }
        if (gepi_hajok.size()>0) {
           for (auto v:gepi_hajok) {
            mezok[v.b][v.a].hajo=true;
           }
        }
    }

}

void grid::draw()
{
    for (size_t i=0;i<_sy+1;i++) {
        gout<<move_to(_x,_y+i*cell_size)<<color(0,0,0)<<line_to(_x+_sx*cell_size,_y+i*cell_size);
    }
    for (size_t i=0;i<_sx+1;i++) {
        gout<<move_to(_x+i*cell_size,_y)<<color(0,0,0)<<line_to(_x+i*cell_size,_y+_sx*cell_size);
    }
    for (size_t i=0;i<mezok.size();i++) {
        for (size_t j=0;j<mezok[i].size();j++) {
            if (mezok[i][j].hajo==true and grid_type=="player") {
                gout<<move_to(_x+j*cell_size+5,_y+5+i*cell_size)<<color(0,255,0)<<box(10,10);
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
    if (aktx>=0 and akty>=0 and mezok[akty][aktx].hajo==false and felallitott_hajok_player_battleship<number_battleship and akttipus=="Battleship") {
        if (aktirany=="fel") {
            if (akty>2 and mezok[akty-1][aktx].hajo==false and mezok[akty-2][aktx].hajo==false and mezok[akty-3][aktx].hajo==false) {
                mezok[akty-3][aktx].hajo=true;
                mezok[akty-2][aktx].hajo=true;
                mezok[akty-1][aktx].hajo=true;
                mezok[akty][aktx].hajo=true;
                felallitott_hajok_player++;
                felallitott_hajok_player_battleship++;
            }
        }
        if (aktirany=="le") {
            if (akty<_sy-1-2 and mezok[akty+1][aktx].hajo==false and mezok[akty+2][aktx].hajo==false and mezok[akty+3][aktx].hajo==false) {
                mezok[akty+3][aktx].hajo=true;
                mezok[akty+2][aktx].hajo=true;
                mezok[akty+1][aktx].hajo=true;
                mezok[akty][aktx].hajo=true;
                felallitott_hajok_player++;
                felallitott_hajok_player_battleship++;
            }
        }
        if (aktirany=="balra") {
            if (aktx>2 and mezok[akty][aktx-1].hajo==false and mezok[akty][aktx-2].hajo==false and mezok[akty][aktx-3].hajo==false) {
                mezok[akty][aktx-3].hajo=true;
                mezok[akty][aktx-2].hajo=true;
                mezok[akty][aktx-1].hajo=true;
                mezok[akty][aktx].hajo=true;
                felallitott_hajok_player++;
                felallitott_hajok_player_battleship++;
            }
        }
        if (aktirany=="jobbra") {
            if (aktx<_sx-1-2 and mezok[akty][aktx+1].hajo==false and mezok[akty][aktx+2].hajo==false and  mezok[akty][aktx+3].hajo==false) {
                 mezok[akty][aktx+3].hajo=true;
                mezok[akty][aktx+2].hajo=true;
                mezok[akty][aktx+1].hajo=true;
                mezok[akty][aktx].hajo=true;
                felallitott_hajok_player++;
                felallitott_hajok_player_battleship++;
            }
        }
    }
    if (aktx>=0 and akty>=0 and mezok[akty][aktx].hajo==false and felallitott_hajok_player_cruiser<number_cruiser and akttipus=="Cruiser") {
        if (aktirany=="fel") {
            if (akty>1 and mezok[akty-1][aktx].hajo==false and mezok[akty-2][aktx].hajo==false) {
                mezok[akty-2][aktx].hajo=true;
                mezok[akty-1][aktx].hajo=true;
                mezok[akty][aktx].hajo=true;
                felallitott_hajok_player++;
                felallitott_hajok_player_cruiser++;
            }
        }
        if (aktirany=="le") {
            if (akty<_sy-1-1 and mezok[akty+1][aktx].hajo==false and mezok[akty+2][aktx].hajo==false) {
                mezok[akty+2][aktx].hajo=true;
                mezok[akty+1][aktx].hajo=true;
                mezok[akty][aktx].hajo=true;
                felallitott_hajok_player++;
                felallitott_hajok_player_cruiser++;
            }
        }
        if (aktirany=="balra") {
            if (aktx>1 and mezok[akty][aktx-1].hajo==false and mezok[akty][aktx-2].hajo==false) {
                mezok[akty][aktx-2].hajo=true;
                mezok[akty][aktx-1].hajo=true;
                mezok[akty][aktx].hajo=true;
                felallitott_hajok_player++;
                felallitott_hajok_player_cruiser++;
            }
        }
        if (aktirany=="jobbra") {
            if (aktx<_sx-1-1 and mezok[akty][aktx+1].hajo==false and mezok[akty][aktx+2].hajo==false) {
                mezok[akty][aktx+2].hajo=true;
                mezok[akty][aktx+1].hajo=true;
                mezok[akty][aktx].hajo=true;
                felallitott_hajok_player++;
                felallitott_hajok_player_cruiser++;
            }
        }
    }
    if (aktx>=0 and akty>=0 and mezok[akty][aktx].hajo==false and felallitott_hajok_player_destroyer<number_destroyer and akttipus=="Destroyer") {
        if (aktirany=="fel") {
            if (akty!=0 and mezok[akty-1][aktx].hajo==false) {
                mezok[akty-1][aktx].hajo=true;
                mezok[akty][aktx].hajo=true;
                felallitott_hajok_player++;
                felallitott_hajok_player_destroyer++;
            }
        }
        if (aktirany=="le") {
            if (akty!=_sy-1 and mezok[akty+1][aktx].hajo==false) {
                felallitott_hajok_player++;
                felallitott_hajok_player_destroyer++;
                mezok[akty+1][aktx].hajo=true;
                mezok[akty][aktx].hajo=true;
            }
        }
        if (aktirany=="jobbra") {
            if (aktx!=_sx-1 and mezok[akty][aktx+1].hajo==false) {
              mezok[akty][aktx+1].hajo=true;
              mezok[akty][aktx].hajo=true;
              felallitott_hajok_player++;
                felallitott_hajok_player_destroyer++;
            }
        }
        if (aktirany=="balra") {
            if (aktx!=0 and mezok[akty][aktx-1].hajo==false) {
                mezok[akty][aktx-1].hajo=true;
                mezok[akty][aktx].hajo=true;
                felallitott_hajok_player++;
                felallitott_hajok_player_destroyer++;
            }
        }
    }
    if (aktx>=0 and akty>=0 and mezok[akty][aktx].hajo==false and felallitott_hajok_player_singleton<number_singleton and akttipus=="Singleton") {
        mezok[akty][aktx].hajo=true;
        felallitott_hajok_player++;
        felallitott_hajok_player_singleton++;
    }
    if (felallitott_hajok_player==flotta_size)
        {
            action_stations();
            player_ready=true;
        }
}

void grid::handle(event ev)
{
    if (battle==true) {
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
                            if (hp==0) battle=false;
                        }
                        if (chosen_y>-1 and chosen_x>-1 and chosen_y==i and chosen_x==j) mezok[i][j].volt_mar=true;
                    }
                }
            }
        }
        if (grid_type=="player") {
            if (player_ready==false) {
                tipus_lekerdezes();
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
                        if (hp==0) battle=false;
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
