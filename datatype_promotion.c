#include <limits.h>
#include <inttypes.h>
#include <stdio.h>

/* Data Promotion */
void implicit_data_promotion(void)
{
	char a = 30, b = 40, c = 10;
	char d = (a * b) / c;
	printf ("%s: d = (%d * %d)/%d = %d\n", __FUNCTION__, a, b, c, d);
}
/*
 * In an expression with mixed datatypes,
 * lower datatypes are promoted to match the highest datatypes in the expression
 */

/* Sign extension */
void signed_nums_as_unsigned(void)
{
	long result;

	int i = -2;
	printf("%s: i = %d(0x%08x)\n", __FUNCTION__, i, i);

	unsigned int j = 1;
	printf("%s: j = %u(0x%08x)\n", __FUNCTION__, j, j);

	result = i + j; /* sign extension does not occur */
	printf("%s: result = %ld(0x%016lx)\n", __FUNCTION__, result, result);
}

/* Sign extension is the operation, in computer arithmetic,
 * of increasing the number of bits of a binary number while preserving
 * the number's sign (positive/negative) and value.
 *
 * This is done by appending digits to the most significant side of the number,
 * following a procedure dependent on the particular signed number representation used.
 */

/* use:
 * Explicit cast of largest data types or
 * Explicit case of whole expression to smallest data type
 */

/* Avoid Arithmetic between Signed and Unsigned Numbers */ 
void arith_sign_unsign(void)
{
	long a = -1;
	unsigned int b = 1;

	printf("%s: a = %ld\n", __FUNCTION__, a);
	printf("%s: b = %u\n", __FUNCTION__, b);

	if (a > b)
		printf("%s: a is greater than b\n", __FUNCTION__);
	else
		printf("%s: a is less than b\n", __FUNCTION__);
}
/*
 * If one of the operands is unsigned and the other is a signed int,
 * the expression becomes an unsigned
 * To avoid unintended data promotion problems, C programs should
 * perform arithmetic operations and comparisons only when all operands
 * are signed or when all operands are unsigned.
 */

int main(int argc, char **argv)
{
	implicit_data_promotion();
	signed_nums_as_unsigned();
	arith_sign_unsign();
	return 0;
}
