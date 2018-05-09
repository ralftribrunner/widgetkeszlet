#include "widget.hpp"
#include "number.hpp"
#include "list.hpp"
#include "button.hpp"
#include "statictext.hpp"
#include "window.hpp"
#include "grid.hpp"
#include <fstream>
#include <sstream>
#include <math.h>
#include <time.h>
#include <random>
#include <iostream>
#include <iterator>

using namespace genv;
using namespace std;

class racs_attack;
class racs_defense;

racs_attack* attack;
racs_defense* defense;
list* irany_lista;

class mywindow:public window {
public:
mywindow();
};

class racs_attack:public grid {
public:
    racs_attack(int x, int y, int sx, int sy, string type):grid(x,y,sx,sy,type) {}
    friend class racs_defense;
    void action_stations() {}
    virtual void over() {
//        defense->hp=0;
        }
    bool another_selected(int x, int y) {}
    void irany_lekerdezes() {}
};

class racs_defense:public grid {
public:
    racs_defense(int x, int y, int sx, int sy, string type):grid(x,y,sx,sy,type) {}
    friend class racs_attack;
    virtual void action_stations() {
        attack->player_ready=true;
    }
    virtual void over() {
        attack->hp=0;
    }
    virtual bool another_selected(int x, int y) {
        int aktualx=floor((x-attack->_x)/attack->public_cell_size);
        int aktualy=floor((y-attack->_y)/attack->public_cell_size);
        if (x>attack->_x and x<attack->_x+attack->_sx*attack->public_cell_size and y>attack->_y and y<attack->_y+attack->_sy*attack->public_cell_size
        and attack->mezok[aktualy][aktualx].volt_mar==false) return true;
    }
    virtual void irany_lekerdezes() {
        defense->aktirany=irany_lista->value_of_widget();
    }
};

mywindow::mywindow() : window(800,500) {
    attack=new racs_attack(400,30,3,3,"computer");
    defense=new racs_defense(50,30,3,3,"player");
    vector<string> iranyok;
    iranyok.push_back("fel");
    iranyok.push_back("le");
    iranyok.push_back("jobbra");
    iranyok.push_back("balra");
    irany_lista=new list(100,400,100,80,iranyok);
    widgets.push_back(irany_lista);
    widgets.push_back(defense);
    widgets.push_back(attack);

}


int main()
{
    mywindow* ablak = new mywindow();
    ablak->event_loop();
    return 0;
}

