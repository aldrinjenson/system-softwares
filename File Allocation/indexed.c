//  Program to simulate the indexed file allocation strategy
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

struct
{
  char name;
  int isAllocated;
} memoryAllocatedList[MAX_SIZE]; // array to kkep track if the memory block is allocated.
struct file
{
  int startingAddress;
  int length;
  char fileName;
  int *memoryIndices; // dynamic array
};
struct file files[20];

int main()
{
  int n;
  int alpha = 65;
  int startAddr;
  printf("\t\tIndexed File Allocation.\nMax Memory = %d", MAX_SIZE);
  printf("\nEnter the number of files to be allocated: ");
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    char fileName = alpha + i;
    printf("\nEnter starting address of file %c: ", fileName);
    scanf("%d", &startAddr);
    if (startAddr < 0 || startAddr > MAX_SIZE)
    {
      printf("Please enter a valid addres between 0 and %d", MAX_SIZE);
      i--;
      continue;
    }

    if (memoryAllocatedList[startAddr].isAllocated == 1)
    {
      printf("Memory already allocated to file %c.Aborting!", memoryAllocatedList[startAddr].name);
      i--;
      continue;
    }

    int length;
    printf("Enter length of file %c: ", fileName);
    scanf("%d", &length);
    int freeBlocksNum = 0;
    for (int j = 0; j < MAX_SIZE; j++)
    {
      if (memoryAllocatedList[j].isAllocated != 1)
        freeBlocksNum++;
    }
    if (length > freeBlocksNum)
    {
      printf("Memory overflow!! Free memory blocks avilable now = %d. Aborting!", freeBlocksNum);
      i--;
      continue;
    }

    files[i].length = length;
    files[i].fileName = fileName;
    files[i].startingAddress = startAddr;
    files[i].memoryIndices = (int *)malloc(length * sizeof(int)); // allocate memory to the dynamic array
    for (int j = startAddr, count = 0; count < length; j = (j + 1) % MAX_SIZE, count++)
    {
      if (memoryAllocatedList[j].isAllocated == 1)
      {
        count--;
        continue;
      }
      memoryAllocatedList[j].isAllocated = 1;
      memoryAllocatedList[j].name = fileName;
      *(files[i].memoryIndices + count) = j;
    }
  }

  // output first version
  printf("Memory Location   | Allocated file");
  for (int i = 0; i < MAX_SIZE; i++)
  {
    char prcsName = '_';
    if (memoryAllocatedList[i].isAllocated)
      prcsName = memoryAllocatedList[i].name;
    printf("\n\t%d \t -> \t %c", i, prcsName);
  }

  // output indexed version
  printf("\nFile Name | Indexed memory locations");
  for (int fileCount = 0; fileCount < n; fileCount++)
  {
    printf("\n\t%c: ", files[fileCount].fileName);
    for (int i = 0; i < files[fileCount].length; i++)
    {
      printf("%d", *(files[fileCount].memoryIndices + i));
      if (i != files[fileCount].length - 1)
        printf(", ");
    }
  }
  printf("\n");
}