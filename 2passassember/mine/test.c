#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{

  FILE *f1 = fopen("test.txt", "w");
  fprintf(f1, "yo");
}