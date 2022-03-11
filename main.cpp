#include <iostream>
#include <omp.h>

int main() {
#pragma omp parallel
    {
        int ID = omp_get_thread_num();
        printf("hello  %d\n", ID);
        printf("hello again %d\n", ID);
    }
    return 0;
}
