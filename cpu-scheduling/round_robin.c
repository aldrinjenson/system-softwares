// Program to input an array of processes with their arrival times & burst times, and schedule them using Round Robin CPU Scheduling
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#define MAX_LENGTH 15

typedef struct
{
  int id;
  int arrivalTime;
  int burstTime;
  int completionTime;
  int turnAroundTime;
  int waitingTime;
  int remainingTime;
} pcb;

pcb input[MAX_LENGTH];      // array of input processes (not a queue)
pcb queue[MAX_LENGTH];      // queue of processes
pcb finalOrder[MAX_LENGTH]; // array to store the processes in correct order

int f = 0;                 // index of the final array
int front = -1, rear = -1; // for the queue of processes
int count = 1, n, timeQuantum;
int currTime = 0;

int isFull()
{
  return (front == rear + 1) || (front == 0 && rear == MAX_LENGTH - 1);
}

int isEmpty()
{
  return (front == -1);
}

void enQueue(pcb el)
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
  printf("\nAdded process p%d to queue.", el.id);
}

pcb deQueue()
{
  if (isEmpty())
  {
    printf("Queue empty. Aborting..");
    exit(0);
  }

  pcb el = queue[front];
  if (front == rear)
  {
    front = -1;
    rear = -1;
  }
  else
    front = (front + 1) % MAX_LENGTH;
  return el;
}

void sort(pcb a[], int l)
{
  pcb temp;
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

void display(pcb a[], int l)
{
  printf("\nProces Id | Arrival Time | Burst Time | Completion Time | TurnAroundTime | WaitingTime");
  for (int i = 0; i < l; i++)
    printf("\np%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d", a[i].id, a[i].arrivalTime, a[i].burstTime, a[i].completionTime, a[i].turnAroundTime, a[i].waitingTime);
}

void executeTopProcess()
{
  pcb el = deQueue(); // pop the top most process from the queue
  printf("\nExecuting process p%d  ", el.id);

  if (el.remainingTime <= timeQuantum)
  {
    currTime += el.remainingTime;
    el.remainingTime = 0;
    el.completionTime = currTime;
    el.turnAroundTime = el.completionTime - el.arrivalTime;
    el.waitingTime = el.turnAroundTime - el.burstTime;
    finalOrder[f++] = el; // add the process to finalArray once finished executing
    printf("Finished executing process %d", el.id);
  }
  else
  {
    currTime += timeQuantum;
    el.remainingTime -= timeQuantum;
    printf("%d seconds remaining; current Time = %d; count = %d", el.remainingTime, currTime, count);

    for (; count < n; count++)
    {
      if (input[count].arrivalTime <= currTime)
      {
        // add all process to queue from input array which have arrived while this process is being executed
        enQueue(input[count]);
      }
      else
        break;
    }
    enQueue(el); // add the current process to the end
  }
}

void roundRobin(int timeQuantum)
{
  enQueue(input[0]); // add the first process to queue
  currTime = input[0].arrivalTime;
  while (f < n)
  {
    executeTopProcess();
  }
}

void getData(int n)
{
  pcb el;
  for (int i = 0; i < n; i++)
  {
    printf("\nEnter arrival time of process %d: ", i + 1);
    scanf("%d", &el.arrivalTime);
    printf("Enter burst time of process %d: ", i + 1);
    scanf("%d", &el.burstTime);
    el.id = i + 1;
    el.remainingTime = el.burstTime;
    el.waitingTime = 0;
    el.completionTime = 0;
    el.turnAroundTime = 0;
    input[i] = el;
  }
}

void printAverages()
{
  float avgWaitingTime = 0;
  float avgTurnAroundTime = 0;
  for (int i = 0; i < n; i++)
  {
    avgWaitingTime += finalOrder[i].waitingTime;
    avgTurnAroundTime += finalOrder[i].turnAroundTime;
  }
  printf("\nAverage Waiting Time = %f", avgWaitingTime / n);
  printf("\nAverage Turn Around Time = %f", avgTurnAroundTime / n);
}

int main()
{
  printf("----Round Robin CPU SCHEDULING ALGORITHM----\n");
  printf("Enter the number of processes: ");
  scanf("%d", &n);
  printf("Enter Time Quantum: ");
  scanf("%d", &timeQuantum);
  getData(n);

  printf("\nInput order:");
  display(input, n);
  printf("\nAfter sorting:");
  sort(input, n);
  display(input, n);
  roundRobin(timeQuantum);

  printf("\n\nAfter applying Round Robin algorithm, the processes in the order of completion:");
  display(finalOrder, f);
  printAverages();
  printf("\n");
}
