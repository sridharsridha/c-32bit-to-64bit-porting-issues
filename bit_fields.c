#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void print_bits(u_int64_t num) {
    printf("%s: 0x%016zx = ", __FUNCTION__, (size_t)num);
    for(int i = CHAR_BIT * sizeof(num) - 1; i >= 0; i--) {
        printf("%u", !!(num & (u_int64_t)(1llu << i)));
        if (i % CHAR_BIT == 0)
			printf(" ");
    }
    printf("\n");
}

int main(int argc, char **argv)
{
	struct bit_field {
		unsigned short a:15;
		unsigned short b:13;
	};
	struct bit_field tmp;
	tmp.a = 0x4000;
	printf("%s: tmp.a = 0x%016zx\n", __FUNCTION__, (size_t)tmp.a);
	print_bits((u_int64_t)tmp.a);
	size_t addr = tmp.a << 17; //Sign Extension
	printf("%s: addr 0x%016zx\n", __FUNCTION__, addr);
	print_bits((u_int64_t)addr);


	/* use: */
	size_t addr1 = (size_t)tmp.a << 17;
	printf("%s: addr1 0x%016zx\n", __FUNCTION__, addr1);
	print_bits((u_int64_t)addr1);
}
