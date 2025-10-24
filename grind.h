#ifndef GRIND_H
#define GRIND_H

#include <string>
#include <vector>
#include <cstdlib>

#include "cell.h"

class grind{
    cell cells[rowmax+2][colmax+2];
public:
    void create(int row, int col);

    void draw();

    void randomize();

    // will the cell at (row, column) survice to the next generation?
    bool will_survive(int row, int column);

    // will the cell be born at (row, column) in the next generation?
    bool will_create(int row, int column);

    void update(const grind& next);
};

void calculate(grind& old_generation, grind& new_generation);

#endif