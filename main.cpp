#include <iostream>
#include <omp.h>
#include <fstream>
#include <string>
#include <complex>
#include "tga.h"
#include <tuple>

using namespace std;
using Complex = std::complex<double>;

#define NUM_THREADS 1

bool writeToDisk = false;
int w = 1024, h = 1024;
double min_x = -2, min_y = -1, max_x = 1, max_y = 1;
int maxIterations = 100;

int mandelbrot(Complex c) {
    double zReal = c.real();
    double zImag = c.imag();

    for (int i = 0; i < maxIterations; ++i) {
        double r2 = zReal * zReal;
        double i2 = zImag * zImag;

        if (r2 + i2 > 4.0) return i;

        zImag = 2.0 * zReal * zImag + c.imag();
        zReal = r2 - i2 + c.real();
    }

    return maxIterations;
}

std::tuple<double, double> normalizeToViewRectangle(int px, int py) {
    double dx = (max_x - min_x) / (w - 1);
    double dy = (max_y - min_y) / (h - 1);

    return std::make_tuple(dx, dy);
}

void plot(std::vector<unsigned char> &colors, const char *filename) {
    tga::TGAImage s;
    s.width = w;
    s.height = h;
    s.bpp = 24;
    s.type = 1;
    s.imageData = colors;

    tga::saveTGA(s, filename);
}

unsigned char *getColor(int mandel, unsigned char rgb[]) {
    if (mandel >= maxIterations) {
        rgb[0] = '100';
        rgb[1] = '100';
        rgb[2] = '100';
    } else if (mandel > maxIterations * 0.9) {
        rgb[0] = '0';
        rgb[1] = '0';
        rgb[2] = '0';
    } else if (mandel > maxIterations * 0.7) {
        rgb[0] = '0';
        rgb[1] = '0';
        rgb[2] = '0';
    } else if (mandel > maxIterations * 0.5) {
        rgb[0] = '0';
        rgb[1] = '0';
        rgb[2] = '0';
    } else if (mandel > maxIterations * 0.3) {
        rgb[0] = '0';
        rgb[1] = '0';
        rgb[2] = '0';
    } else if (mandel > maxIterations * 0.1) {
        rgb[0] = '100';
        rgb[1] = '100';
        rgb[2] = '100';
    } else {
        rgb[0] = '255';
        rgb[1] = '255';
        rgb[2] = '255';
    }

    return rgb;
}

void calcPix(int px, int py, std::vector<unsigned char> &colors, int idx) {
    auto tuple = normalizeToViewRectangle(px, py);

    double x = min_x + py * std::get<0>(tuple); // current real value
    double y = max_y - px * std::get<1>(tuple); // current imaginary value

    Complex res(x, y);

    int mandel = mandelbrot(res);

    unsigned char color[3];
    getColor(mandel, color);

    colors[idx] = color[0];
    colors[idx + 1] = color[1];
    colors[idx + 2] = color[2];
}

void readCommandLineInput() {
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
}

int main() {
//    readCommandLineInput();

    double wtime = omp_get_wtime();
    omp_set_num_threads(NUM_THREADS);

    std::vector<unsigned char> imageData(h * w * 3);
    int k = 0;

#pragma omp parallel for shared(imageData) firstprivate(k) collapse(2)
    for (int px = 0; px < w; px++) {
        for (int py = 0; py < h; py++) {
            calcPix(px, py, imageData, k);
            k = px + py + 3;
        }
    }

    if (writeToDisk) {
        plot(imageData, "./output.tga");
    }

    wtime = omp_get_wtime() - wtime;
    cout << "\n";
    cout << "  Time = " << wtime << " seconds.\n";

    return 0;
}
