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
#define IS_TESTED true
#define WRITE_TO_DISK true

int w = 1024, h = 1024;
double min_x = -2, min_y = -1, max_x = 1, max_y = 1;
int maxIterations = 255;

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
//        black
        rgb[0] = ((unsigned char) 0);
        rgb[1] = ((unsigned char) 0);
        rgb[2] = ((unsigned char) 0);
    } else if (mandel > maxIterations * 0.9) {
//        red
        rgb[0] = ((unsigned char) 255);
        rgb[1] = ((unsigned char) 0);
        rgb[2] = ((unsigned char) 0);
    } else if (mandel > maxIterations * 0.7) {
//        light red
        rgb[0] = ((unsigned char) 255);
        rgb[1] = ((unsigned char) 160);
        rgb[2] = ((unsigned char) 122);
    } else if (mandel > maxIterations * 0.5) {
//        orange
        rgb[0] = ((unsigned char) 255);
        rgb[1] = ((unsigned char) 165);
        rgb[2] = ((unsigned char) 0);
    } else if (mandel > maxIterations * 0.3) {
//        yellow
        rgb[0] = ((unsigned char) 255);
        rgb[1] = ((unsigned char) 255);
        rgb[2] = ((unsigned char) 0);
    } else if (mandel > maxIterations * 0.2) {
//        light green
        rgb[0] = ((unsigned char) 144);
        rgb[1] = ((unsigned char) 238);
        rgb[2] = ((unsigned char) 144);
    } else if (mandel > maxIterations * 0.1) {
//        green
        rgb[0] = ((unsigned char) 0);
        rgb[1] = ((unsigned char) 128);
        rgb[2] = ((unsigned char) 0);
    } else if (mandel > maxIterations * 0.05) {
//        light cyan
        rgb[0] = ((unsigned char) 224);
        rgb[1] = ((unsigned char) 255);
        rgb[2] = ((unsigned char) 255);
    } else if (mandel > maxIterations * 0.04) {
//        cyan
        rgb[0] = ((unsigned char) 0);
        rgb[1] = ((unsigned char) 255);
        rgb[2] = ((unsigned char) 255);
    } else if (mandel > maxIterations * 0.03) {
//        light blue
        rgb[0] = ((unsigned char) 173);
        rgb[1] = ((unsigned char) 216);
        rgb[2] = ((unsigned char) 230);
    } else if (mandel > maxIterations * 0.02) {
//        blue
        rgb[0] = ((unsigned char) 0);
        rgb[1] = ((unsigned char) 0);
        rgb[2] = ((unsigned char) 255);
    } else if (mandel > maxIterations * 0.01) {
//        magenta
        rgb[0] = ((unsigned char) 238);
        rgb[1] = ((unsigned char) 130);
        rgb[2] = ((unsigned char) 238);
    } else {
//        light magenta
        rgb[0] = ((unsigned char) 255);
        rgb[1] = ((unsigned char) 0);
        rgb[2] = ((unsigned char) 255);
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

    int location = (px + py * h) * 3;

    colors[location] = color[0];
    colors[location + 1] = color[1];
    colors[location + 2] = color[2];
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

int main(int argc, char *argv[]) {
    int threadNum = NUM_THREADS;
    if (argc > 2) {
        threadNum = atoi(argv[1]);
        maxIterations = atoi(argv[2]);
    }

    if (!IS_TESTED) {
        readCommandLineInput();
    }

    double wtime = omp_get_wtime();
    omp_set_num_threads(threadNum);

    std::vector<unsigned char> imageData(h * w * 3);
    int k = 0;

#pragma omp parallel for shared(imageData) firstprivate(k) collapse(2) shared(w, h) default(none)
    for (int px = 0; px < w; px++) {
        for (int py = 0; py < h; py++) {
            calcPix(px, py, imageData, k);
            k = px + py + 3;
        }
    }

    if (WRITE_TO_DISK) {
        plot(imageData, "./output.tga");
    }

    wtime = omp_get_wtime() - wtime;

    if (IS_TESTED) {
        cout << wtime << endl;
    } else {
        cout << "Elapsed time: " << wtime << " seconds" << endl;
    }

    return 0;
}
