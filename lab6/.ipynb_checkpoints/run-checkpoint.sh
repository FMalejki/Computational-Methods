#!/bin/bash

# Kompilacja bez optymalizacji
echo "Kompilacja bez optymalizacji..."
make clean
make

# Uruchomienie programu bez optymalizacji i zapis wyników
echo "Uruchamianie testu bez optymalizacji..."
./matrix_multiplication > results_no_opt.csv

# Kompilacja z optymalizacją (dla chętnych)
echo "Kompilacja z optymalizacją..."
make clean
make optimized

# Uruchomienie programu z optymalizacją i zapis wyników (dla chętnych)
echo "Uruchamianie testu z optymalizacją..."
./matrix_multiplication_optimized > results_opt.csv

echo "Testy zakończone. Wyniki zapisane do plików CSV."
echo "Możesz teraz uruchomić analizę w notebooku Julia."