#!/bin/bash

while getopts i:t:f:m: flag
do
    case "${flag}" in
        i) iterations=${OPTARG};;
        t) threads=${OPTARG};;
        f) filename=${OPTARG};;
        m) maxIterations=${OPTARG};;
    esac
done

echo "Running: $iterations iterations of the program";
echo "Mandelbrot is run with: $maxIterations max-iterations";
echo "Running: $threads threads";
echo "Saving to: $filename";

for j in $(seq 1 $iterations);
do
   ./cmake-build-debug/fh_ppr_mandelbrot $threads $maxIterations  >> $filename
done