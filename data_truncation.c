#include <limits.h>
#include <inttypes.h>
#include <stdio.h>

/* Avoid Assigning longs to ints */
void dont_assign_long_int(void)
{
	int a = INT_MAX;
	printf("%s: a = %d(0x%x)\n", __FUNCTION__, a, a);

	long b = LONG_MAX;
	printf("%s: b = %ld(ox%lx)\n", __FUNCTION__, b, b);

	a = b; /* b is 8bytes and a is 4bytes */

	printf("%s: after truncation a = %d(0x%x)\n", __FUNCTION__, a, a);
}

/* Avoid Storing/casting Pointers in ints or ints/hexadecimal literal to pointer */
void avoid_storing_ptr_in_int(void)
{
	int a = INT_MAX;
	printf("%s: a = %d(0x%x)\n", __FUNCTION__, a, a);

	int b = &a;
	printf("%s: &a = %p, b = %d(0x%x)\n", __FUNCTION__, &a, b, b);

	// same goes vise versa dont store int into a pointer
	int *ptr;
	int i;
	ptr = (int *) i;

	// use: intptr_t b = &a

}

/* Avoid Truncating Function Return Values */
static inline int get_offset(int* base, int* ptr)
{
	return (ptr - base);
}

void avoid_func_return_truncation(void)
{
	int *base, *ptr;  // Assume base and ptr have a valid addressess

	int offset = get_offset(base, ptr);  // See the problem here

	printf("%s: The value of the pointer offset is %d\n",
		__FUNCTION__, offset);

	// use: ptrdiff_t ssize_t size_t
}

/* Use Appropriate Print Specifiers */
void use_appropriate_print_specifiers(void)
{
	/*
	 * c   - write a single character
	 * s   - write a character string
	 * d/i - convert a signed int into decimal
	 * o   - convert a unsigned int into octal
	 * x/X - convert a unsigned int into hexadecimal
	 * u   - convert a unsigned int into decimal
	 * f/F - convert floating point into decimal
	 * e/E - convert floating point into decimal exponent
	 * a/A - convert floating point into hexadecimal exponent
	 * g/G - convert floating point into decimal/decimal exponent
	 *       based on value & precision
	 * n   - number of characters written so far
	 * p   - write a pointer(void*) portable
	 */

	/* What is the issue here? */
	long a;
	printf("%s: a = %x\n", __FUNCTION__, a);

	/* how about this? */
	int64_t offset = INT_MAX; /* its it not long long */
	printf("%s: offset = %" PRIx64 "\n", __FUNCTION__, offset);

	/* Dont not use below approach with using types from inttypes.h */
	printf("%s: offset = %llx\n", __FUNCTION__, offset);

	/* Use of a %p */
	char c = 'a';
	char *ptr = &c;
	printf("%s: ptr = %p\n", __FUNCTION__, ptr);
}

int main(int argc, char** argv) {
	dont_assign_long_int();
	avoid_storing_ptr_in_int();
	avoid_func_return_truncation();
	use_appropriate_print_specifiers();
	return 0;
}

/**
 * Some important points:
 * Pointers are not always 32 bits
 * A size_t is not always 32 bits
 * A long is not always 32 bits
 * An integer that can hold a pointer is an intptr_t
 * A pointer in a structure needs 8-byte alignment on 64-bit
 * That can make for some very big holes
 * An int32_t is not a long (or printed with %ld)
 * An int64_t is not a long long (or printed with %lld)
*/

