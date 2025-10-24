#include <iostream>
#include "grind.h"

using namespace std;

int main() {

    cout << "Conway's game of life Matteo" << endl;
    cout << "press the return key to display each generation" << endl;

    // we need to wait until the user press the return key
    cin.get();

    grind current_generation;

    current_generation.randomize();

    while (true)
    {
        current_generation.draw();

        cin.get();

        grind next_generation;

        calculate(current_generation, next_generation);

        current_generation.update(next_generation);
    }
    

    
    return 0;
}