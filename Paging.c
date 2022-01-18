// Program to calculate the physical address of entered logical addres of a program which is stored as pages in main memory using the paging technique.

#include <stdio.h>

void main()
{
  int numPages, memSize, pageSize;
  int pageTable[20];
  printf("Enter memory size(Bytes): ");
  scanf("%d", &memSize);
  printf("Enter page size(Bytes): ");
  scanf("%d", &pageSize);
  if (pageSize > memSize)
  {
    printf("page size cannot be greater than the total memory size!\nExiting...\n");
    return;
  }

  int maxPages = memSize / pageSize;
  printf("Maximum number of frames possible = %d\n", maxPages);

  printf("How many pages does the process have? ");
  scanf("%d", &numPages);
  if (numPages > maxPages)
  {
    printf("Error! Number of pages cannot be more than %d. Overflow\nExiting!!\n", maxPages);
    return;
  }

  printf("\nPage Table Entry:\n");
  int temp;
  for (int i = 0; i < numPages; i++)
  {
    printf("Enter frame address of page %d: ", i + 1);
    scanf("%d", &temp);

    for (int j = 0; j < i; j++)
    { // loop to check if the same frame address was entered before
      if (pageTable[j] == temp)
      {
        printf("Multiple pages cannot have the same frame address.\nPage %d already has %d as frame address.", j, temp);
        printf("\nPlease try again:\n");
        i--;
        continue;
      }
    }
    pageTable[i] = temp;
  }

  int logicalAddress;
  printf("\nPhysical Address calculation\n");
  while (1)
  {
    printf("Enter logical address: ");
    scanf("%d", &logicalAddress);
    int pageNum = logicalAddress / pageSize;
    int offset = logicalAddress % pageSize;
    if (pageNum > numPages)
    {
      printf("Logic address out of bounds for the current program.\nMax logic address available for the entered process is %d\nPlease try again...\n", pageTable[numPages - 1] * pageSize + offset);
      continue;
    }
    printf("Page Number = %d; Offset = %d\n", pageNum, offset);
    int physicalAddress = pageTable[pageNum] * pageSize + offset;
    printf("The physical address corresponding to %d is %d\n", logicalAddress, physicalAddress);
  }
}