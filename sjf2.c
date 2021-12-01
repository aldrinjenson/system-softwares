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
  int isDone; // flag to mark a process once it has been executed
} pcb;

pcb p[10]; // array of processes.

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
    for (int j = 0; j < l - i - 1; j++)
    {
      if (a[j].arrivalTime > a[j + 1].arrivalTime)
      {
        swap(&a[j], &a[j + 1]);
      }
    }
}

pcb finalOrder[10];
int f = 0;

void execute(int processIndex, int n)
{
  p[processIndex].isDone = 1;
  finalOrder[f] = p[processIndex];
  f++;
  printf("\nExecuting Process %d", p[processIndex].id);
}

void sjf(pcb p[], int n)
{
  int currTime = 0;
  int index = 0;

  // loop to ensure that all the processes gets executed
  for (int i = 0; i < n; i++)
  {
    index = 0;
    int minBurstTime = INT_MAX; // assume Infinite burst time
    int minBurstTimeProcessIndex;

    // loop to find the process of minimum burst time among the process having arrival time less than currentTime
    while (index < n)
    {
      // ignore all the processes which are marked as done
      if (p[index].isDone == 0 && p[index].arrivalTime <= currTime && p[index].burstTime < minBurstTime)
      {
        // printf("\nHere with pid %d; isDone = %d ", p[index].id, p[index].isDone);
        minBurstTimeProcessIndex = index;
      }
      index++;
    }
    // execute the process with minimum burst time and mark it as done
    execute(minBurstTimeProcessIndex, n);
    // cpu will take the (burst time of the process) seconds from the current time to execute the process.
    currTime += p[minBurstTimeProcessIndex].burstTime;
  }
}

void calculateValues(pcb a[], int l)
{
  a[0].completionTime = a[0].arrivalTime + a[0].burstTime;
  for (int i = 0; i < l; i++)
  {
    a[i].completionTime = a[i - 1].completionTime + a[i].burstTime;
    int diff = a[-1].completionTime - a[i].arrivalTime;
    if (diff > 0)
      a[i].completionTime += diff;
    a[i].turnAroundTime = a[i].completionTime - a[i].arrivalTime;
    a[i].waitingTime = a[i].turnAroundTime - a[i].burstTime;
  }
}

void display(pcb a[], int l)
{
  printf("\nProces Id | Arrival Time | Burst Time | Completion Time | TurnAroundTime | WaitingTime");
  for (int i = 0; i < l; i++)
    printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d", a[i].id, a[i].arrivalTime, a[i].burstTime, a[i].completionTime, a[i].turnAroundTime, a[i].waitingTime);
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
  calculateValues(finalOrder, f);

  printf("\n\nAfter applying SJF algorithm:");
  display(finalOrder, f);
  printf("\n");
}