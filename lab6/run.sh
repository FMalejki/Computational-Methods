#!/bin/bash

echo "Kompilacja bez optymalizacji..."
make clean
make

echo "Uruchamianie testu bez optymalizacji..."
./matrix_multiplication > results_no_opt.csv

echo "Kompilacja z optymalizacją..."
make clean
make optimized

echo "Uruchamianie testu z optymalizacją..."
./matrix_multiplication_optimized > results_opt.csv

echo "Testy zakończone. Wyniki zapisane do plików CSV."
