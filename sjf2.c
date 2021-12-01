#include <stdio.h>
#include <limits.h>

typedef struct
{
  int id;
  int arrivalTime;
  int burstTime;
  int completionTime;
  int turnAroundTime;
  int waitingTime;
  int isDone;
} pcb;

pcb p[10];
void swap(pcb *a, pcb *b)
{
  pcb temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

void sort(pcb a[], int l)
{
  for (int i = 0; i < l; i++)
  {
    for (int j = 0; j < l - i - 1; j++)
    {
      if (a[j].arrivalTime > a[j + 1].arrivalTime)
      {
        swap(&a[j], &a[j + 1]);
      }
    }
  }
}

pcb finalOrder[10];
int f = 0;

void execute(pcb el)
{
  el.isDone = 1;
  finalOrder[f] = el;
  f++;
}

void sjf(pcb p[], int n)
{
  int currTime = 0;
  int index = 0;
  pcb minBurstProcess;

  for (int i = 0; i < n; i++)
  {
    index = 0;
    minBurstProcess = p[index];
    while (p[index].arrivalTime < currTime)
    {
      if (p[index].isDone == 0 && p[index].burstTime < minBurstProcess.burstTime)
      {
        minBurstProcess = p[index];
      }
      index++;
    }
    execute(minBurstProcess);
    currTime += minBurstProcess.burstTime;
  }
}

void display(pcb a[], int l)
{
  printf("\nProces Id | Arrival Time | Burst Time | Completion Time | TurnAroundTime | WaitingTime");
  for (int i = 0; i < l; i++)
    printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d", p[i].id, p[i].arrivalTime, p[i].burstTime, p[i].completionTime, p[i].turnAroundTime, p[i].waitingTime);
}

void getData(int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("\nEnter arrival time of process %d: ", i);
    scanf("%d", &p[i].arrivalTime);
    printf("Enter burst time of process %d: ", i);
    scanf("%d", &p[i].burstTime);
    p[i].id = i + 1;
    p[i].isDone = 0;
  }
}

int main()
{

  int n;
  printf("Enter the number of processes: ");
  scanf("%d", &n);
  getData(n);

  printf("Input order");
  display(p, n);
  sort(p, n);
  sjf(p, n);

  printf("\n\nAfter applying SJF algorithm:");
  display(finalOrder, f);
  printf("\n");
}