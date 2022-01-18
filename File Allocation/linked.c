//  Program to simulate the linked file allocation strategy
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

typedef struct
{
  char name;
  int isAllocated;
} memBlock;

memBlock memoryAllocatedList[MAX_SIZE]; // array to kkep track if the memory block is allocated.
struct file
{
  char processName;
  int memoryIndex;
  struct file *next;
};

void insertAtEnd(struct file **head, struct file *node)
{
  node->next = NULL;
  if (*head == NULL)
  {
    *head = node;
    return;
  }
  struct file *temp = *head;
  while (temp->next)
    temp = temp->next;
  temp->next = node;
}

struct file files[20];

int main()
{
  int n;
  int alpha = 65;
  int startAddr;
  printf("\t\tLinked File Allocation.\nMax Memory = %d", MAX_SIZE);
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

    if (memoryAllocatedList[startAddr].isAllocated == 1)
    {
      printf("Memory already allocated to process %c.Aborting!", memoryAllocatedList[startAddr].name);
      i--;
      continue;
    }

    int length;
    printf("Enter length of process %c: ", processName);
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

    files[i].next = NULL;
    for (int j = startAddr, count = 0; count < length; j = (j + 1) % MAX_SIZE, count++)
    {
      if (memoryAllocatedList[j].isAllocated == 1)
      {
        count--;
        continue;
      }
      memoryAllocatedList[j].isAllocated = 1;
      memoryAllocatedList[j].name = processName;
      struct file *temp = (struct file *)malloc(sizeof(struct file));
      temp->memoryIndex = j;
      temp->processName = processName;
      insertAtEnd(&files[i].next, temp);
    }
  }

  // output first version
  printf("Memory Location   | Allocated Process");
  for (int i = 0; i < MAX_SIZE; i++)
  {
    char prcsName = '_';
    if (memoryAllocatedList[i].isAllocated)
      prcsName = memoryAllocatedList[i].name;
    printf("\n\t%d \t -> \t %c", i, prcsName);
  }

  // output linked list version
  printf("\nFile Name | Linked memory locations");
  for (int processCount = 0; processCount < n; processCount++)
  {
    struct file *temp = files[processCount].next;
    printf("\n%c: ", temp->processName);
    while (temp)
    {
      printf("%d", temp->memoryIndex);
      if (temp->next != NULL)
        printf("->");
      temp = temp->next;
    }
  }
  printf("\n");
}