#ifndef MAIN_H
#define MAIN_H
#include <stdint.h>

typedef struct float_properties {
    int32_t exponent;
    double fraction;
    double decimal;
    double mantissa;
} float_prop;

double pow_r(int32_t base, int32_t powr);
double floatmanipul(double, float_prop *);
#endif
