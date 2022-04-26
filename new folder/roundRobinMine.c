/*.................C Program to Implement SJF ( Shortest Job First) CPU SCheduling Algorithm.....................
SJF - A Non Preemptive Algorithm
This Program works for same as well as different arrival times
based on: https://www.youtube.com/watch?v=UdO5RdHxDJQ&list=PLVKIC9j3jSYtCEAffM_51qVWeQus70cqc&index=8
*/
// working !YESSSSSSS

#include <stdio.h>
#include <stdlib.h> // for exit function

#define MAX_LENGTH 15

typedef struct
{
  int pid;
  int arrivalTime;
  int burstTime;
  int completionTime;
  int waitingTime;
  int turnAroundTime;
  int start_time;
  int isDone;
  int remainingTime;
} process_struct;
process_struct ps[100];

process_struct queue[MAX_LENGTH];       // queue of processes
process_struct finalAnswer[MAX_LENGTH]; // queue of processes
int front = -1, rear = -1;              // for the queue of processes

int isFull()
{
  return (front == rear + 1) || (front == 0 && rear == MAX_LENGTH - 1);
}

int isEmpty()
{
  return (front == -1);
}

void enQueue(process_struct el)
{
  if (isFull())
  {
    printf("Queue full. Aborting.");
    return;
  }
  if (rear == -1)
  {
    rear = 0;
    front = 0;
  }
  else
    rear = (rear + 1) % MAX_LENGTH;
  queue[rear] = el;
  // printf("\nAdded process p%d to queue.", el.pid);
}

process_struct deQueue()
{
  if (isEmpty())
  {
    printf("Queue empty. Aborting..");
    exit(0);
  }

  process_struct el = queue[front];
  if (front == rear)
  {
    front = -1;
    rear = -1;
  }
  else
    front = (front + 1) % MAX_LENGTH;
  return el;
}

void sort(process_struct a[], int l)
{
  process_struct temp;
  for (int i = 0; i < l; i++)
    for (int j = 0; j < l - i - 1; j++)
    {
      if (a[j].arrivalTime > a[j + 1].arrivalTime)
      {
        temp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = temp;
      }
    }
}
int timeQuantum;
int main()
{
  int n;
  printf("Enter total number of processes: ");
  scanf("%d", &n);
  printf("Enter time quantum: ");
  scanf("%d", &timeQuantum);
  int totalTurnAroundTime = 0, totalWaitingTime = 0;
  int max_completion_time, min_arrival_time;

  for (int i = 0; i < n; i++)
  {
    printf("\nEnter Process %d Arrival Time: ", i);
    scanf("%d", &ps[i].arrivalTime);
    printf("Enter Process %d Burst Time: ", i);
    scanf("%d", &ps[i].burstTime);
    ps[i].pid = i;
    ps[i].isDone = 0;
    ps[i].remainingTime = ps[i].burstTime;
  }

  sort(ps, n);

  int current_time = 0;
  int completed = 0;
  int processPointer = 0;
  current_time = ps[processPointer].arrivalTime;
  enQueue(ps[processPointer]);

  processPointer++;
  process_struct currProcess;
  while (completed != n)
  {
    currProcess = deQueue();
    if (currProcess.remainingTime > timeQuantum)
    {
      currProcess.remainingTime -= timeQuantum;
      current_time += timeQuantum;

      for (; processPointer < n; processPointer++)
      {
        if (ps[processPointer].arrivalTime > current_time)
          break;
        else
          enQueue(ps[processPointer]);
      }

      enQueue(currProcess);
    }
    else
    {
      current_time += currProcess.remainingTime;
      currProcess.remainingTime = 0;
      currProcess.isDone = 1;
      currProcess.completionTime = current_time;
      currProcess.turnAroundTime = currProcess.completionTime - currProcess.arrivalTime;
      currProcess.waitingTime = currProcess.turnAroundTime - currProcess.burstTime;
      finalAnswer[completed++] = currProcess;
      totalTurnAroundTime += currProcess.turnAroundTime;
      totalWaitingTime += currProcess.waitingTime;

      for (; processPointer < n; processPointer++)
      {
        if (ps[processPointer].arrivalTime > current_time)
          break;
        else
          enQueue(ps[processPointer]);
      }
    }
  }

  //Output
  printf("\nPID.\tArrival Time\tBurst Time\tCT\tTAT\tWT\n");
  for (int i = 0; i < n; i++)
    printf("%d\t\t%d\t%d\t\t%d\t%d\t%d\t\n", finalAnswer[i].pid, finalAnswer[i].arrivalTime, finalAnswer[i].burstTime, finalAnswer[i].completionTime, finalAnswer[i].turnAroundTime, finalAnswer[i].waitingTime);

  printf("\n");

  printf("\nAverage Turn Around time= %f", (float)totalTurnAroundTime / n);
  printf("\nAverage Waiting Time= %f\n", (float)totalWaitingTime / n);
  return 0;
}
