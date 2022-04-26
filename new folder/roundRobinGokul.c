#include <stdio.h>

// to sort the processes
void sortProcess(int at[], int bt[], int n)
{
  int i, j;
  int temp;
  for (i = 0; i < n - 1; i++)
  {
    int small = i;
    for (j = i + 1; j < n; j++)
    {
      if (at[small] > at[j])
        small = j;
    }
    if (small != i)
    {
      temp = at[small];
      at[small] = at[i];
      at[i] = temp;

      temp = bt[small];
      bt[small] = bt[i];
      bt[i] = temp;
    }
  }
}

// queue functions
#define qmax 5

int queue[qmax];
int rear = -1, front = -1;
int isEmpty()
{

  if (front < 0)
    return 1;
  else
    return 0;
}

int isFull()
{
  if (rear == front - 1 || (front == 0 && rear == qmax - 1))
    return 1;
  else
    return 0;
}

void enqueue(int a)
{
  if (isFull() == 0)
  {
    if (front < 0)
      front++;
    rear = (rear + 1) % qmax;
    queue[rear] = a;
  }
}

void dequeue()
{
  if (isEmpty() == 0)
  {
    int element = queue[front];

    if (front == rear)
    {
      rear = -1;
      front = -1;
    }

    if (front != -1)
      front = (front + 1) % qmax;
  }
}

int peak()
{
  return queue[front];
}

void main()
{

  int i, j, n, qt;

  printf("\nEnter the number of processes: ");
  scanf("%d", &n);

  int at[n], bt[n];
  printf("\nEnter the arrival and burst times for each process: \n");
  for (i = 0; i < n; i++)
  {
    scanf("%d %d", &at[i], &bt[i]);
  }
  printf("\nEnter the time quantum: ");
  scanf("%d", &qt);

  int rem_t[n], wt[n], tat[n], ct[n];
  int inQ[n];
  int avg_wt = 0, avg_tat = 0, time = 0;

  // function written above
  sortProcess(at, bt, n);

  for (i = 0; i < n; i++)
  {
    rem_t[i] = bt[i];
    wt[i] = 0;
    tat[i] = 0;
    ct[i] = 0;
    inQ[i] = 0;
  }

  printf("\n");
  // in case the first process doesn't arrive at time 0
  time = at[0];

  enqueue(0);
  int queue_n = 1;

  while (queue_n != 0)
  {
    i = peak();
    if (rem_t[i] > qt)
    {
      rem_t[i] -= qt;
      time += qt;
    }
    else
    {
      time += rem_t[i];
      rem_t[i] = 0;
      ct[i] = time;
      tat[i] = ct[i] - at[i];
      avg_tat += tat[i];
      wt[i] = tat[i] - bt[i];
      avg_wt += wt[i];
    }
    dequeue();
    queue_n--;
    j = i + 1;
    while (j < n && time >= at[j])
    {
      if (inQ[j] == 0)
      {
        enqueue(j);
        queue_n++;
        inQ[j] = 1;
      }
      j++;
    }
    //  if the process hasn't reached completion
    if (ct[i] == 0)
    {
      enqueue(i);
      queue_n++;
    }
  }

  printf("\nAT\t\tBT\t\tCT\t\tTAT\t\tWT");

  for (i = 0; i < n; i++)
    printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", at[i], bt[i], ct[i], tat[i], wt[i]);

  printf("\n\nTurnAround Time = %0.3f", ((float)avg_tat / n));
  printf("\nAverage Waiting Time = %0.3f", ((float)avg_wt / n));
}
