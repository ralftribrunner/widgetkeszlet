#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

#include "graphics.hpp"
#include "widget.hpp"
#include <vector>

class window {
 protected:
     const int X;
     const int Y;
    std::vector<Widget*> widgets;
public:
   window(int x, int y);
  void event_loop();
    void kepernyotorlo();
   //virtual void kalandkezelo()=0;
};


#endif // WINDOW_HPP_INCLUDED
