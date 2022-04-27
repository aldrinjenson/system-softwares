// sequential

#include <stdio.h>
#define MAX_SIZE 10

typedef struct
{
  char storedProcessName;
  int isAllocated
} locationBlock;

locationBlock locations[MAX_SIZE];

void main()
{

  int n;
  printf("\t\tSequential File Allocation.\nMax Memory = %d", MAX_SIZE);
  printf("\nEnter the number of processes to be allocated: ");

  scanf("%d", &n);
  int alpha = 65, startAddr;
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
    if (locations[startAddr].isAllocated)
    {
      printf("Memory already allocated to process %c.Aborting!", locations[startAddr].storedProcessName);
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
    int isContiguousMemFree = 1;

    for (int j = startAddr; j < startAddr + length; j++)
    {
      if (locations[j].isAllocated)
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
      locations[x].isAllocated = 1;
      locations[x].storedProcessName = processName;
    }
  }

  printf("Memory Location   | Allocated Process");
  for (int i = 0; i < n; i++)
  {
    printf(" ");
  }
}