#ifndef CELL_H
#define CELL_H

#include <iostream>

#include "life.h"

class cell {
    // cell status
    bool alive;
public:
    // construct to set a cell to empty by default
    cell(): alive(false) {};

    void draw(int row, int col) const;

    // Bring cell alive
    void create(){
        alive = true;
    }
   
    // End cell's life
    void erase(){
        alive = false;
    }

    bool is_alive() const { return alive;} 
};

#endif