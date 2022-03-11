#include <iostream>
#include <omp.h>
#include <fstream>
#include <string>
#include "tga.h"

using namespace std;

int main() {

    int w, h;
    cout << "Please enter the height and width of the target picture: (h, w)" << endl;
    cin >> h >> w;

    cout << "Height: " << h << endl << "Width: " << w << endl;

    cout << "Please enter the view rectangle: (min_x, min_y, max_x, max_y)" << endl;

    int min_x, min_y, max_x, max_y;

    cin >> min_x >> min_y >> max_x >> max_y;

    cout << "min_x: " << min_x << endl << "min_y: " << min_y << endl << "max_x: " << max_x << endl << "max_y: "
         << max_y << endl;

    cout << "Please enter the number of iterations: " << endl;
    int maxIterations;

    cin >> maxIterations;

    cout << "maxIterations: " << maxIterations << endl;

    return 0;
}
