#include <stdio.h>
#include <stdint.h>
#include <float.h>

double pow_r(int32_t base, int32_t powr);
#define SET 0XFFFFFFFFFFFFFFFF

double pow_r(int32_t base, int32_t powr){
    if (!base)
	return 0;
    if (base == 1)
	return 1;
    if (!powr)
	return 1;
    if (powr == 1)
	return base;
    return base * pow_r(base, powr - 1);
}
int main(){
    union {
	double x;
	uint64_t gg;
    } op;
    double resetdbl_k;
    double fracdec;
    int32_t i, count;
    uint64_t bits, revBit;
    uint64_t frop;
    int64_t expon;
    int32_t sign;
    double mantissa;

    op.x = 1.999999999;

    fracdec = count = 0;
    sign = (int64_t)op.gg >> 63;
    printf("%d\n", sign);
    !(sign) ? sign = 1 : 0;
    op.gg <<= 1;

    /* extract exponent */
    expon = (op.gg >> 53) - 0X3FF;  /*  bias */
    op.gg <<= 11;
    bits = op.gg; /* save bit state for mantissa */

    printf("expon %Ld\n", expon);

    /** if possibility of fraction :- 0 < @expon < 64
     * @fracdec: decimal part, @frop: decimal fraction */
    if (expon < 64){
	/* exponential */
	frop = op.gg;
	frop = expon > 0 ? frop << expon : frop; /* shift out decimal part */
	if (expon < 0)
	    frop = (frop >> 1) | (1LL << 63);

	/* extract only fractional. expel backward zeros */
	while (frop && !(frop & 1)){
	    count++;
	    frop >>= 1;
	}
	/** @expon < 0: remove sign @count: denomalizing power to base 2 */
	count -= expon < 0 ? (-expon - 1) : 0;

	/* divide by number of bits to power of radix(2) */
	fracdec = (frop / (pow_r(2, 64 - count))) * sign;

	printf("%f\n", fracdec);

        /* Extract decimal */
	op.gg = ((op.gg >> 1) | (1LL << 63))>>(64 - (expon + 1));
	printf("dec %Ld\n", op.gg * sign);
    }
    /* else reset bits to double representation */
    else if (expon > 63){
	expon += 1023;
	op.gg = (op.gg >> 12) | (expon << 52); /* add exp */
	resetdbl_k = *(volatile double *)&op.gg; /* copy bits */

	printf("p2 %f\n", resetdbl_k);
    }
    /* To conclude extract mantissa */
    revBit = count = i = 0;
    count |= 64;
    /* reverse bits */
    while (i < count){
	revBit |= bits & (1LL << i) ? 1LL << ((count - 1) - i) : 0;
	i++;
    }
    /* convert bits in base 2 to floating point */
    mantissa = i = 0;
    while (revBit){
	mantissa += (revBit % 2) * (1/(double)(2LL << i++));
	revBit >>= 1; /* revBit/2 */
    }
    mantissa += 1;
    printf("mantissa %a\n", mantissa * sign);

    return 0;
}
