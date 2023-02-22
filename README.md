
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
</footer>
</p>Reference: "IEEE Arithmetic" https://docs.oracle.com/cd/E19957-01/806-3568/ncg_math.html </p>
</n>Author: Michael Saviour <n\>
</n>Repo: https://github.com/saviour623/FLT_BitHack<n\>
<footer\>
