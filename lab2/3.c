#include <stdio.h>
#include <stdint.h>

void print_float_bits(float x) {
    union { float f; uint32_t i; } u;
    u.f = x;
    for (int i = 31; i >= 0; i--) {
        printf("%d", (u.i >> i) & 1);
        if (i == 31 || i == 23) printf(" ");
    }
    printf("\n");
}

int main() {
    float x = 1.0;
    for (int i = 0; i < 30; i++) {
        print_float_bits(x);
        x /= 2;
    }
    return 0;
}