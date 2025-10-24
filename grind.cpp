#include "grind.h"

using namespace std;

void grind::create(int row, int column){
    cells[row][column].create();
}

void grind::draw(){

    cout << "\x1b[2J";

    for(int row = 0; row < rowmax; row++){
        for(int col = 0; col < colmax; col++){
            cells[row][col].draw(row, col);
        }
    }
    
}

void grind::randomize(){
    const int factor = 5;
    const int cutoff = RAND_MAX/factor;
    time_t now;
    time(&now);
    srand(now);

    for (int row = 1; row < rowmax; row++)
    {
        for (int col = 1; col < colmax; col++)
        {
            if(rand()/cutoff == 0){
                create(row, col);
            }
        }    
    } 
}

bool grind::will_survive(int row, int col){
    if(!cells[row][col].is_alive()){
        return false;
    }
    // find the number of live neighbours
    //  x x x
    //  x o x
    //  x x x
    int neighbours = cells[row-1][col-1].is_alive()+
        cells[row-1][col].is_alive() +
        cells[row-1][col+1].is_alive() +
        cells[row][col-1].is_alive() +
        cells[row][col+1].is_alive() +
        cells[row+1][col-1].is_alive() +
        cells[row+1][col].is_alive() +
        cells[row+1][col+1].is_alive();

        if(neighbours < min_neighbours || neighbours > max_neighbours){
            return false;
        }
    // if we get here, the cell has survived
    return true;
}

bool grind::will_create(int row, int col){
    if(cells[row][col].is_alive()){
        return false;
    }
   
    int parents = cells[row-1][col-1].is_alive()+
        cells[row-1][col].is_alive() +
        cells[row-1][col+1].is_alive() +
        cells[row][col-1].is_alive() +
        cells[row][col+1].is_alive() +
        cells[row+1][col-1].is_alive() +
        cells[row+1][col].is_alive() +
        cells[row+1][col+1].is_alive();

    if(parents < min_parents || parents > max_parents){
        return false;
    }

    return true;
}

void grind::update(const grind& next){
    for(int row = 1; row < rowmax; row++){
        for(int col = 1; col < colmax; col++){
            cells[row][col] = next.cells[row][col];
        }
    }
}

// by default, all cells in the next generation are initially unpopulated
// calculate which live cells survive to the next generation
// and unpopulated cells are popolutated in the next generation
void calculate(grind& old_generation, grind& next_generation){
    for(int row = 1; row < rowmax; row++){
        for (int col = 1; col < colmax; col++)
        {
            // will this live cell survive to the nexr generation?
            if(old_generation.will_survive(row, col)){
                next_generation.create(row, col);
            }
            // will this unpopulated cell be populated in the next generation?
            else if(old_generation.will_create(row, col)){
                next_generation.create(row, col);
            } 
        } 
    }
}