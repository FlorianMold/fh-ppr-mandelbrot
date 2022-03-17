# Getting started

Execute the program and fill out the questions:

For example:
```bash
./fh_ppr_mandelbrot

Please enter the height and width of the target picture: (h, w)
512
512
Height: 512
Width: 512
Please enter the view rectangle: (min_x, min_y, max_x, max_y)
-2
-1
1
1
min_x: -2
min_y: -1
max_x: 1
max_y: 1
Please enter the number of iterations: 
512
maxIterations: 512
Elapsed time: 0.443209 seconds
```

After the program has executed a file named `output.tga` is generated where the script ist executed.

## Options

Some program options can be configured at the top of the `main.cpp` file

```c++
#define NUM_THREADS 1 // Number of threads to execute the program.
#define IS_TESTED false // test-mode: disables the input of the parameters from the terminal.
#define WRITE_TO_DISK true // Whether the image is written to the disk.
```