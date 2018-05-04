//#include "graphics.hpp"
#include "widget.hpp"
#include "number.hpp"
#include "list.hpp"
#include "button.hpp"
#include "statictext.hpp"
#include "window.hpp"
#include <fstream>
#include <sstream>
#include <math.h>
#include<time.h>
#include<random>
#include<iostream>
#include<iterator>
using namespace genv;
using namespace std;

class nyomobutton;
class hozzad_button;

hozzad_button* gomb_hozzaad;
nyomobutton* gomb;
number* numb;
statictext* szoveg;
list* lista;
list* lista2;

class mywindow:public window {
public:
mywindow();
};


class hozzad_button:public button {

public:
    hozzad_button(int x, int y, int sx, int sy):button(x,y,sx,sy) {}
    virtual void kaland(){
        lista2->elem_hozzaad(szoveg->value_of_widget());
    }
};

class nyomobutton:public button {

public:
    nyomobutton(int x, int y, int sx, int sy):button(x,y,sx,sy) {}
    virtual void kaland(){
        numb->nullaz();
    }
};

mywindow::mywindow() : window(800,500) {
    vector<string> elemek;
    elemek.push_back("Prokofiev");
    elemek.push_back("Schumann");
    elemek.push_back("Mozart");
    elemek.push_back("Haydn");
    elemek.push_back("Strauss");
    elemek.push_back("Wagner");
    elemek.push_back("Beethoven");
    elemek.push_back("Brahms");
    elemek.push_back("Dvorak");
    elemek.push_back("Liszt");
    elemek.push_back("Schubert");
    elemek.push_back("Chopin");
    vector<string> elemek2;
    elemek2.push_back("Audi");
    elemek2.push_back("Skoda");
    elemek2.push_back("Mercedes-Benz");
    elemek2.push_back("Renault");
    elemek2.push_back("Ferrari");
    elemek2.push_back("Porsche");
    elemek2.push_back("Toyota");
    elemek2.push_back("Kia");
    lista=new list(200,300,120,100,elemek);
    lista2=new list(400,300,130,60,elemek2);
    gomb=new nyomobutton(20,450,130,40);
    gomb_hozzaad=new hozzad_button(10,10,20,20);
    numb=new number(300,100,200,100,20,-10);
    szoveg=new statictext(150,10,200,50);
    widgets.push_back(gomb_hozzaad);
    widgets.push_back(szoveg);
    widgets.push_back(lista);
    widgets.push_back(lista2);
    widgets.push_back(gomb);
    widgets.push_back(numb);
}


int main()
{
    mywindow* ablak = new mywindow();
    ablak->event_loop();
    return 0;
}
