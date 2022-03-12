#!/bin/bash

while getopts i:t:f: flag
do
    case "${flag}" in
        i) iterations=${OPTARG};;
        t) threads=${OPTARG};;
        f) filename=${OPTARG};;
    esac
done

echo "Running: $iterations iterations";
echo "Running: $threads threads";
echo "Saving to: $filename threads";

for j in  $(seq 1 $iterations);
do
   ./cmake-build-debug/fh_ppr_mandelbrot $threads >> $filename
done