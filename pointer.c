#include <limits.h>
#include <inttypes.h>
#include <stdio.h>

/* Understanding pointer arithmetics */
void pointer_arith(void)
{
    struct foo {
        long d;
        int i;
    };

    struct foo a[10];
    struct foo *x = a;
    x = (struct foo *)((uintptr_t)x + sizeof(x)); /* dont do it */

    x++; /* elegant! */
}

/* Avoid Pointer Arithmetic between longs and ints */
void avoid_pointer_arith_btw_long_int(void)
{
    long array[5];
    int i; /* i: index for array */
    int *j; /* j: pointer to int */
    long *k; /* k: pointer to long */
    for (i = 0; i < 4; i++)
        array[i]=i + 1;

    j = array + 2; /* incrementing pointer */
    printf ( "The address of j is %p\n", &j );
    printf ( "The contents of j are %p\n", j );
    printf ("The dereferenced value of j is %d\n", *j );

    k = array + 2; /* incrementing pointer */
    printf ( "The address of k is %p\n", &k );
    printf ( "The contents of k are %p\n", k );
    printf ( "The dereferenced value of k is %ld\n", *k );
}

/* Use of functions with a variable number of arguments */
void avoid_buffer_overflow(void)
{
    int x;
    char buf[12];
    sprintf(buf, "%p", &x);
    printf("%s: buff = %s\n", __FUNCTION__, buf);
}

int main(int argc, char **argv)
{
    pointer_arith();
    avoid_pointer_arith_btw_long_int();
    avoid_buffer_overflow();
    return 0;
}

/**
 * Some key points:
 *
 * Never put a long or a size_t in an IPC message
 * Learn the beauty of PRIdPTR and PRId64
 * Learn about C pointer arithmetic
 * Pointers are printed with %p
 * A pointer minus a pointer is an ssize_t
 * Learn the difference between ssize_t vs ptrdiff_t
 */

/*
 * The type ssize_t is capable of storing values at least in the range [-1, SSIZE_MAX].
 */
