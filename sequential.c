//  Program to simulate the sequential file allocation strategy
#include <stdio.h>
#define MAX_SIZE 10

typedef struct
{
  char name;
  int startingAddress;
  int length;
  int isAllocated;
} pcb;

pcb p[MAX_SIZE];

void main()
{
  int n;
  int alpha = 65;
  int startAddr;
  printf("\t\tSequential File Allocation.\nMax Memory = %d", MAX_SIZE);
  printf("\nEnter the number of processes to be allocated: ");
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    char processName = alpha + i;
    printf("\nEnter starting address of process %c: ", processName);
    scanf("%d", &startAddr);
    if (startAddr < 0 || startAddr > MAX_SIZE)
    {
      printf("Please enter a valid addres between 0 and %d", MAX_SIZE);
      i--;
      continue;
    }
    if (p[startAddr].isAllocated)
    {
      printf("Memory already allocated to process %c.Aborting!", p[startAddr].name);
      i--;
      continue;
    }
    int length;
    printf("Enter length of process %c: ", processName);
    scanf("%d", &length);
    if (startAddr + length > MAX_SIZE)
    {
      printf("Memory overflow!! Max memory size = %d", MAX_SIZE);
      i--;
      continue;
    }
    // checking if contiguous memory allocation is available
    int isContiguousMemFree = 1;
    for (int x = startAddr; x < startAddr + length; x++)
    {
      if (p[x].isAllocated)
      {
        isContiguousMemFree = 0;
        break;
      }
    }
    if (isContiguousMemFree == 0)
    {
      printf("Contiguous memory of %d length not available from location %d. Aborting!", length, startAddr);
      i--;
      continue;
    }
    for (int x = startAddr; x < startAddr + length; x++)
    {
      p[x].isAllocated = 1;
      p[x].name = processName;
    }
  }

  // output
  printf("Memory Location   | Allocated Process");
  for (int i = 0; i < MAX_SIZE; i++)
  {
    char prcsName = '_';
    if (p[i].isAllocated)
      prcsName = p[i].name;
    printf("\n\t%d \t -> \t %c", i, prcsName);
  }
  printf("\n");
}