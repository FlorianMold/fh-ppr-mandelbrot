#include <omp.h>
#include "tga.h"

int main() {

    tga::TGAImage _test;
    _test.bpp = 1;
    tga::saveTGA(_test, "asdad");
    
    return 0;
}
