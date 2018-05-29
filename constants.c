#include <limits.h>
#include <stdio.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdlib.h>
#include <memory.h>

/* Common constant uses */
/*
 * 4              - bytes for pointer
 * 32             - bits for pointer
 * 0x7fffffff     - max value of 32-bit signed int
 * 0x80000000     - min value of 32-bit signed int
 * 0xffffffff     - max value of unsigned 32-bit int (-1) as error indicator
 */

/* using literals and masks that assume 32 bit */
void literals_issue(void)
{
	/* set all bits to 1 -> 1111..1111 */
	const size_t N = 0xFFFFFFFFu;
	printf("%s: N = 0x%016lx\n", __FUNCTION__, N);

	/* portable way of setting all bits to 1 */
	long p = -1L;
	size_t q = (size_t)(-1);

	printf("%s: p = 0x%016lx\n", __FUNCTION__, p);
	printf("%s: q = 0x%016lx\n", __FUNCTION__, q);

	/* Unset last four bits -> '1111..110000' */
	const size_t M = 0xFFFFFFF0u;

	printf("%s: M = 0x%016lx\n", __FUNCTION__, M);

	long r = ~0xFL;
	printf("%s: r = 0x%016lx\n", __FUNCTION__, r);

    /*
	 * so how (size_t)-1 is in 0xFFFFFFFFu in 32-bit and
	 * 0xFFFFFFFFFFFFFFFF in 64-bit
	 */
    int a = -1;           // 0xFFFFFFFF
    ptrdiff_t b = a;      // 0xFFFFFFFFFFFFFFFFu
    size_t c = (size_t)b; // 0xFFFFFFFFFFFFFFFF

    int x = 100000;
    int y = 100000;
    int z = 100000;
    intptr_t size = 1;                  // Result:
    intptr_t v1 = x * y * z;            // -1530494976
    intptr_t v2 = (intptr_t)x * y * z;  // 1000000000000000
    intptr_t v3 = x * y * (intptr_t)z;  // 141006540800000
    intptr_t v4 = size * x * y * z;     // 1000000000000000
    intptr_t v5 = x * y * z * size;     // -1530494976
    intptr_t v6 = size * (x * y * z);   // -1530494976
    intptr_t v7 = size * (x * y) * z;   // 141006540800000
    intptr_t v8 = ((size * x) * y) * z; // 1000000000000000
    intptr_t v9 = size * (x * (y * z)); // -1530494976
    // intptr_t v2 = intptr_t(x) + intptr_t(y) * intptr_t(z);

}

/* Avoid using mixed datatype usage */
void mixed_datatype_usage(void)
{
    const size_t MAX_TYPES = ~(size_t)0; //SIZE_MAX
    for (unsigned types = 0; types != MAX_TYPES; ++types)
    {
        /*  do something here */
    }

    ptrdiff_t a = -1;
    unsigned int b = 1;
    if (a > b)
        printf ("a is greater than b\n");
    else
        printf ("a is not greater than b\n");

    //Output on 32-bit system: "a is greater than b"
    //Output on 64-bit system: "a is not greater than b"
}

/* hardcoding size of datatypes */
void hardcoding_datatype_size(void)
{
	/* what is the problem in below code snippets */
	const size_t N = 5u;
	size_t ArraySize = N * 4;
	intptr_t *Array = (intptr_t *)malloc(ArraySize);

	const size_t ARRAY_SIZE = 5u;
	size_t values[ARRAY_SIZE];
	memset(values, 0, ARRAY_SIZE * 4);
	for (size_t i = 0; i < ARRAY_SIZE; ++i)
		printf("%s: values[%lu] = %lu\n", __FUNCTION__, i, values[i]);

	size_t n, newexp;
	n = n >> (32 - newexp);
}

static inline ptrdiff_t SetBitN(ptrdiff_t value, unsigned bitNum) {
	ptrdiff_t mask = 1 << bitNum;
    // ptrdiff_t mask = (ptrdiff_t)1 << bitNum;
	return value | mask;
}

/* hardcoding bitshift values */
void hardcoding_bitshift_and_bitmask_values(void)
{
	unsigned long y;
	y = (1 << 32); /* Overflows in both data models. */
	printf("%s: y = 0x%016lx\n", __FUNCTION__, y);

	y = (1L << 32); /* 2^32 in LP64. Overflows in ILP32. */
	printf("%s: y = 1x%016lx\n", __FUNCTION__, y);

	printf("%s: bitshift: 0x%016tx\n", __FUNCTION__, SetBitN(0, 32));

	/* ptrdiff_t mask = (ptrdiff_t)1 << bitNum; */

    /* What will be the result of the uncorrected function SetBitN(0, 31) call?
     * The right answer is 0xffffffff80000000.
     * The result of 1 << 31 expression is negative number -2147483648.
     *
     *  ptrdiff_t Result; Result = 1 << 31; -2147483648 0xffffffff80000000
     *  Result = ptrdiff_t(1) << 31;         2147483648 0x0000000080000000
     *  Result = 1U << 31;                   2147483648 0x0000000080000000
     *  Result = 1 << 32;                             0 0x0000000000000000
     *  Result = ptrdiff_t(1) << 32;         4294967296 0x0000000100000000
     */
}

int main(int argc, char **argv)
{
	literals_issue();
	hardcoding_datatype_size();
	hardcoding_bitshift_and_bitmask_values();
    mixed_datatype_usage();
	return 0;
}
