#include <iostream>
#include <omp.h>
#include <fstream>
#include <string>
#include <complex>
#include "tga.h"

using namespace std;
using Complex = std::complex<double>;

int w, h;
int min_x, min_y, max_x, max_y;
int maxIterations;

Complex scale(int px, int py, Complex c) {
    int width = max_x - min_x;
    int height = max_y - min_y;
    Complex aux(c.real() / w * width * min_x, c.imag() / h * height + min_y);
    return aux;
}

int mandelbrot(Complex c) {
    Complex z(0);
    int currentIteration = 0;

    while (abs(z) <= 2.0 && currentIteration < maxIterations) {
        z = z * z + c;
        currentIteration++;
    }

    return currentIteration;
}

Complex normalizeToViewRectangle(int px, int py) {
    Complex c(px, py);
    return c = scale(px, py, c);
}

void plot(std::vector<int> &colors) {

}

void calcPix(int px, int py, std::vector<int> &colors, int idx) {
    Complex c = normalizeToViewRectangle(px, py);
    colors[idx] = mandelbrot(c);
    plot(colors);
}

int main() {
    cout << "Please enter the height and width of the target picture: (h, w)" << endl;
    cin >> h >> w;

    cout << "Height: " << h << endl << "Width: " << w << endl;

    cout << "Please enter the view rectangle: (min_x, min_y, max_x, max_y)" << endl;

    cin >> min_x >> min_y >> max_x >> max_y;

    cout << "min_x: " << min_x << endl << "min_y: " << min_y << endl << "max_x: " << max_x << endl << "max_y: "
         << max_y << endl;

    cout << "Please enter the number of iterations: " << endl;

    cin >> maxIterations;

    cout << "maxIterations: " << maxIterations << endl;

    std::vector<int> imageData(h * w);

    int k = 0;
    for (int px = 0; px < w; px++) {
        for (int py = 0; py < h; py++) {
            calcPix(px, py, imageData, k);
            k++;
        }
    }

    return 0;
}
