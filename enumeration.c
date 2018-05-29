#include <stdio.h>

// Signed unsigned test for types and values
//
#define ISUNSIGNED_VAL(a) (a >= 0 && ~a >= 0)
#define ISUNSIGNED_TYPE(type) ((type)0 - 1 > 0)

int main(int argc, char **argv)
{
	int array[4] = { 1, 2, 3, 4 };
	typedef enum enegative { MONE = -1, MTWO, MTHREE, MFOUR } enegative_t;

    printf("%s: sizeof enegative = %zu is_unsigned = %u\n", __FUNCTION__, sizeof(enegative_t), !!ISUNSIGNED_TYPE(enegative_t));

	typedef enum epositive { ONE = 1, TWO, THREE, FOUR } epositive_t;

    printf("%s: sizeof enegative = %zu is_unsigned = %u\n", __FUNCTION__, sizeof(enegative_t), !!ISUNSIGNED_TYPE(epositive_t));

	epositive_t *enum_ptr = (epositive_t *)(array);
	printf("%s: %u ", __FUNCTION__, enum_ptr[1]);

	size_t *size_ptr = (size_t *)(array);
	printf("%zu \n", size_ptr[1]);
}
