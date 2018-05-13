#include "widget.hpp"
#include "list.hpp"
#include "window.hpp"
#include "grid.hpp"
#include "consttext.hpp"
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
consttext* allapot;
list* tipus_lista;

class mywindow:public window {
public:
mywindow();
};

class racs_attack:public grid {
public:
    racs_attack(int x, int y, int sx, int sy, string type):grid(x,y,sx,sy,type) {}
    friend class racs_defense;
    void action_stations() {}
    virtual void over();
    bool another_selected(int x, int y) {}
    void irany_lekerdezes() {}
    void tipus_lekerdezes() {}
};

class racs_defense:public grid {
public:
    racs_defense(int x, int y, int sx, int sy, string type):grid(x,y,sx,sy,type) {}
    friend class racs_attack;
    virtual void action_stations() {
        attack->player_ready=true;
        allapot->text1="Action Stations!";
    }
    virtual void over() {
        attack->battle=false;
        allapot->text1="The battle is over!";

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
    virtual void tipus_lekerdezes() {
        defense->akttipus=tipus_lista->value_of_widget();
    }
};

void racs_attack::over(){
    defense->battle=false;
    allapot->text1="The battle is over!";
}

mywindow::mywindow() : window(800,500) {
    attack=new racs_attack(400,30,10,10,"computer");
    defense=new racs_defense(50,30,10,10,"player");
    allapot=new consttext(450,400,200,30,"Flotta felallitasa");
    vector<string> iranyok;
    iranyok.push_back("fel");
    iranyok.push_back("le");
    iranyok.push_back("jobbra");
    iranyok.push_back("balra");
    irany_lista=new list(100,400,100,60,iranyok);
    vector<string> hajotipusok;
    hajotipusok.push_back("Battleship");
    hajotipusok.push_back("Cruiser");
    hajotipusok.push_back("Destroyer");
    hajotipusok.push_back("Singleton");
    tipus_lista=new list(300,400,100,60,hajotipusok);
    widgets.push_back(tipus_lista);
    widgets.push_back(irany_lista);
    widgets.push_back(allapot);
    widgets.push_back(defense);
    widgets.push_back(attack);

}


int main()
{
    mywindow* ablak = new mywindow();
    ablak->event_loop();
    return 0;
}

