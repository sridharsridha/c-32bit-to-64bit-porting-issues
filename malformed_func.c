#include <stdio.h>

int main(int argc, char **argv)
{
  const size_t Gbyte = 1024 * 1024 * 1024;
  size_t i;
  char *Pointers[3];

  /* Allocate */
  for (i = 0; i != 3; ++i) {
    Pointers[i] = (char *)malloc(Gbyte);
  }

  /* Use */
  for (i = 0; i != 3; ++i)
    Pointers[i][0] = 1;

  /* Free */
  for (i = 0; i != 3; ++i)
    free(Pointers[i]);

  return 0;
}
