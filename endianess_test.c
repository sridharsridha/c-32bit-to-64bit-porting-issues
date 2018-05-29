#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
	int i = 0x12345678;
	printf("Mac Host Little indian - 0x%x\n", (i));

	if (*(char *)&i == 0x12)
		printf ("Big endian\n");
	else if (*(char *)&i == 0x78)
		printf ("Little endian\n");

	printf("Network Big Indian - 0x%x\n", htonl(i));
}
