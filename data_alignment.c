#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

struct node {
	size_t count;           /* 8byte */
	uint8_t data;           /* 1byte */
	/* 7byte padding */
	struct node *left;   /* 8byte */
	uint16_t id;             /* 2byte */
	/* 6byte padding */
	struct node *right;  /* 8byte */
};
/* total size is struct tnode is 40bytes in 64-bit */

/* Another Example */
struct mixed {
	int a;       /* 4bytes */
	/* 4byte padding */
	double b;    /* 8bytes */
	int c;       /* 4bytes */
	/* 4byte padding */
	long d;      /* 8bytes */
};
/* total size of struct mingled is 32bytes in 64-bit */


/* issues in struct */
void issues_in_struct(void)
{
    const unsigned MAX_POOL_SIZE = 10u;
    struct void_ptr_pool_t {
        size_t count;
        void* ptrs[1];
    } *void_ptr_pool_inst;

    /* Allocating void_ptr_pool_inst with 5 void * pointers */
    void_ptr_pool_inst = malloc( sizeof(unsigned) + MAX_POOL_SIZE * sizeof(void*));
    void_ptr_pool_inst->count = 10u;

    free(void_ptr_pool_inst);
}

/* issue in union */
void issues_in_union(void)
{
    size_t offset = 3u;
	char a[] = {'s', 'r', 'i', 'd', 'h', 'a', 'r', '\0'};


	union PtrNumUnion {
		char *m_p;
		unsigned m_n;
	} u;
	u.m_p = a;
	u.m_n += offset;

    printf("%s: u.m_p = %s : u.m_p + %lu = %c\n", __FUNCTION__, a, offset, *u.m_p);

	union SizetToBytesUnion {
		size_t value;
		struct {
			unsigned char b0, b1, b2, b3;
		} bytes;
	} t;

	size_t value = 10u;
	t.value = value;
	size_t zeroBitsN = t.bytes.b0 +
			   t.bytes.b1 +
			   t.bytes.b2 +
		       t.bytes.b3;
    printf("%s: t.value = 0x%lx\n", __FUNCTION__, t.value);
    printf("%s: t.bypes.b0 = %d\n", __FUNCTION__, (int)t.bytes.b0);
    printf("%s: t.bytes.b1 = %d\n", __FUNCTION__, (int)t.bytes.b1);
    printf("%s: t.bytes.b2 = %d\n", __FUNCTION__, (int)t.bytes.b2);
    printf("%s: t.bytes.b3 = %d\n", __FUNCTION__, (int)t.bytes.b3);
}

int main(int argc, char **argv)
{
	printf("sizeof struct tnode64 = %lu\n", sizeof(struct node));
	printf("sizeof struct mingled = %lu\n", sizeof(struct mixed));

    issues_in_struct();
	issues_in_union();

	return 0;
}
