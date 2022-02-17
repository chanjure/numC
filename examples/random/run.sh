#!/bin/bash

rm -rf ./results
mkdir -p ./results/plots
g++ main.C -I../../numC
./a.out
python3 plot.py
