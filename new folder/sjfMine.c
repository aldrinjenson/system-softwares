/*.................C Program to Implement SJF ( Shortest Job First) CPU SCheduling Algorithm.....................
SJF - A Non Preemptive Algorithm
This Program works for same as well as different arrival times
based on: https://www.youtube.com/watch?v=UdO5RdHxDJQ&list=PLVKIC9j3jSYtCEAffM_51qVWeQus70cqc&index=8
*/
// working !YESSSSSSS

#include <stdio.h>
#include <limits.h>

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
} process_struct;
process_struct ps[100];

int main()
{
  int n;
  int current_time = 0;
  int completed = 0;

  printf("Enter total number of processes: ");
  scanf("%d", &n);
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
  }

  while (completed != n)
  {
    int minBurstTimeProcessIndex = -1;
    int minBurstTime = INT_MAX;

    for (int i = 0; i < n; i++)
    {
      if (ps[i].isDone == 1 || ps[i].arrivalTime > current_time)
        continue;

      if (ps[i].burstTime < minBurstTime)
      {
        minBurstTime = ps[i].burstTime;
        minBurstTimeProcessIndex = i;
      }
      else if (ps[i].burstTime == minBurstTime)
      {
        minBurstTime = ps[i].burstTime;
        minBurstTimeProcessIndex = i;
      }
    }

    if (minBurstTimeProcessIndex == -1)
      current_time++;
    else
    {
      ps[minBurstTimeProcessIndex].start_time = current_time;
      ps[minBurstTimeProcessIndex].completionTime = ps[minBurstTimeProcessIndex].start_time + ps[minBurstTimeProcessIndex].burstTime;
      ps[minBurstTimeProcessIndex].turnAroundTime = ps[minBurstTimeProcessIndex].completionTime - ps[minBurstTimeProcessIndex].arrivalTime;
      ps[minBurstTimeProcessIndex].waitingTime = ps[minBurstTimeProcessIndex].turnAroundTime - ps[minBurstTimeProcessIndex].burstTime;

      totalTurnAroundTime += ps[minBurstTimeProcessIndex].turnAroundTime;
      totalWaitingTime += ps[minBurstTimeProcessIndex].waitingTime;

      ps[minBurstTimeProcessIndex].isDone = 1;
      completed++;
      current_time = ps[minBurstTimeProcessIndex].completionTime;
    }
  }

  process_struct temp;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n - i - 1; j++)
      if (ps[j].completionTime > ps[j + 1].completionTime)
      {
        temp = ps[j];
        ps[j] = ps[j + 1];
        ps[j + 1] = temp;
      }
  }
  //Output
  printf("\nPID.\tArrival Time\tBurst Time\tCT\tTAT\tWT\n");
  for (int i = 0; i < n; i++)
    printf("%d\t\t%d\t%d\t\t%d\t%d\t%d\t\n", ps[i].pid, ps[i].arrivalTime, ps[i].burstTime, ps[i].completionTime, ps[i].turnAroundTime, ps[i].waitingTime);

  printf("\n");

  printf("\nAverage Turn Around time= %f", (float)totalTurnAroundTime / n);
  printf("\nAverage Waiting Time= %f\n", (float)totalWaitingTime / n);
  return 0;
}
