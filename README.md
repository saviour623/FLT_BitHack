
# <div align="center"> FLT_BITHACK </div>
This is a program that extracts the component parts of a floating point number.
For precision and compatibility, the double precision floating point type is used. 
The parts of the number is stored in a struct, `float_prop`, with elements:
``` C
* int32_t exponent;
* double fraction;
* double decimal;
* double mantissa;
```
The output are constricted based on the IEEE standard for floating point numbers.
Reference: 
Author: Michael Saviour (saviour623@github.com)
