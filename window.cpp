#include "graphics.hpp"
#include "window.hpp"
#include "widget.hpp"
#include <fstream>
#include <iostream>
using namespace genv;
using namespace std;

window::window(int x, int y):X(x),Y(y)
{
    gout.open(x,y);
}



void window::kepernyotorlo() {
    gout<<move_to(0,0)<<color(255,255,255)<<box(X,Y);
}

 void window::event_loop()
 {
    //std::ofstream ki("allapot.txt");
    event ev;
    gin.timer(40);
    while(gin >> ev ) {
        if (ev.type==ev_timer) {
           kepernyotorlo();
            for (auto a:widgets)
            {
                a->draw();
            }
        }
        if (ev.type==ev_key or ev.type==ev_mouse) {
            for (auto a:widgets)
            {
                a->handle(ev);
                a->do_the_job();
            }

        }
        if (ev.type==ev_key and ev.keycode==key_f1){
            for (auto a:widgets)
            {
                cout<<a->value_of_widget()<<endl;
            }
            cout<<"\\\\\\\\\\\\\\"<<endl;
        }
        gout<<refresh;
    }
 }
