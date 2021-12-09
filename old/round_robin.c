// Program to input an array of processes with their arrival times & burst times, and schedule them using Round Robin CPU Scheduling
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#define MAX_LENGTH 10

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

pcb queue[MAX_LENGTH]; // circular queue of processes
int front = -1, rear = -1;

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

pcb finalOrder[MAX_LENGTH]; // array to store the processes in correct order
int f = 0;                  // index of the final array
int currTime = 0;

void execute(pcb el, int timeQuantum)
{
  if (el.remainingTime < timeQuantum)
  {
    printf("\nExecuting Process %d for %d seconds; ", el.id, el.remainingTime);
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
    enQueue(el); // execute the process and add it back in the queue
    printf("\nExecuting Process %d for %d seconds; %d seconds remaining", el.id, timeQuantum, el.remainingTime);
  }
}

void roundRobin(int timeQuantum)
{
  while (!isEmpty())
  {
    pcb el = deQueue();
    execute(el, timeQuantum);
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
  pcb el;
  for (int i = 0; i < n; i++)
  {
    printf("\nEnter arrival time of process %d: ", i + 1);
    scanf("%d", &el.arrivalTime);
    printf("Enter burst time of process %d: ", i + 1);
    scanf("%d", &el.burstTime);
    el.id = i + 1;
    el.remainingTime = el.burstTime;
    enQueue(el);
  }
}

int main()
{
  int n, q;
  printf("----Round Robin CPU SCHEDULING ALGORITHM----\n");
  printf("Enter the number of processes: ");
  scanf("%d", &n);
  printf("Enter Time Quantum: ");
  scanf("%d", &q);
  getData(n);

  printf("\nInput order:");
  display(queue, n);
  sort(queue, n);
  roundRobin(q);

  printf("\n\nAfter applying SJF algorithm, the processes in the order of completion:");
  display(finalOrder, f);
  printf("\n");
}
