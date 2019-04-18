#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

//    /*FIFO*/
void FIFO(int *arr1, int *arr2, int *arr3)
{
   int x = sizeof(arr1)/2;
   int y = sizeof(arr2)/2;
   int z = sizeof(arr3)/2;

   int bt[100], waitTime[100], turnaroundTime[100], avgWaitTime = 0, avgTurnaroundTime = 0, i, j;
   waitTime[0] = 0; //waiting time for first process is 0

   //calculating waiting time
   for (i = 1; i < y; i++)
   {
      waitTime[i] = 0;
      for (j = 0; j <= i; j++){
         waitTime[i] += arr2[j];
      }
      printf("%d\n", waitTime[i]);
   }

   printf("\nProcess\t\tWaiting Time\tTurnaround Time");
   //calculating turnaround time
   for (i = 0; i < y; i++)
   {
      turnaroundTime[i] = bt[i] + waitTime[i];
      avgWaitTime += waitTime[i];
      avgTurnaroundTime += turnaroundTime[i];
      printf("\nP[%d]\t\t\t%d\t\t%d", arr1[i], waitTime[i], turnaroundTime[i]);
   }

   avgWaitTime /= i;
   avgTurnaroundTime /= i;
   printf("\n\nAverage Waiting Time:%d", avgWaitTime);
   printf("\nAverage Turnaround Time:%d", avgTurnaroundTime);
}
/*SJF*/
int SJF(int *arr1, int *arr2, int *arr3, size_t max)
{
   int bt[20], p[20], wt[20], tat[20], i, j, n, total = 0, pos, temp;
   float avg_wt, avg_tat;
   printf("Enter number of process:");
   scanf("%d", &n);

   printf("\nEnter Burst Time:\n");
   for (i = 0; i < n; i++)
   {
      printf("p%d:", i + 1);
      scanf("%d", &bt[i]);
      p[i] = i + 1; //contains process number
   }

   //sorting burst time in ascending order using selection sort
   for (i = 0; i < n; i++)
   {
      pos = i;
      for (j = i + 1; j < n; j++)
      {
         if (bt[j] < bt[pos])
            pos = j;
      }

      temp = bt[i];
      bt[i] = bt[pos];
      bt[pos] = temp;

      temp = p[i];
      p[i] = p[pos];
      p[pos] = temp;
   }

   wt[0] = 0; //waiting time for first process will be zero

   //calculate waiting time
   for (i = 1; i < n; i++)
   {
      wt[i] = 0;
      for (j = 0; j < i; j++)
         wt[i] += bt[j];

      total += wt[i];
   }

   avg_wt = (float)total / n; //average waiting time
   total = 0;

   printf("\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
   for (i = 0; i < n; i++)
   {
      tat[i] = bt[i] + wt[i]; //calculate turnaround time
      total += tat[i];
      printf("\np%d\t\t  %d\t\t    %d\t\t\t%d", p[i], bt[i], wt[i], tat[i]);
   }

   avg_tat = (float)total / n; //average turnaround time
   printf("\n\nAverage Waiting Time=%f", avg_wt);
   printf("\nAverage Turnaround Time=%f\n", avg_tat);
   return 0;
}
//    /*BJF*/
int BJF(int *arr1, int *arr2, int *arr3, size_t max)
{
   return 0;
}

//    /*STCF*/
int STCF(int *arr1, int *arr2, int *arr3, size_t max)
{
   return 0;
}

//    /*RR*/
int RR(int *arr1, int *arr2, int *arr3, size_t max)
{
   return 0;
}

int main(int argc, char **argv)
{
   static const char filename[] = "jobs.dat";
   FILE *fp = fopen(filename, "r");
   if (fp != NULL)
   {
      int integers[100];
      int i = 0;
      int num;
      int *jobIDs; //JOB_ID
      int *arrivalTime; //Arrival_Time
      int *duration; //Duration
      int len=100;

      jobIDs = (int*)calloc(len,sizeof(int));
      arrivalTime = (int*)calloc(len,sizeof(int));
      duration = (int*)calloc(len,sizeof(int));

      //Scan file for all ints excluding whitespaces and new lines
      while (fscanf(fp, "%d", &num) != EOF)
      {
         integers[i] = num;
         i++;

      }
      int x,y,z = 0;

      /*Take the first int of each line and put it in JOB_ID array*/
      for (int a = 0; a < i; a++)
      {
         *(jobIDs + x) = integers[a];
         a=a+2;
         x++;
      }
      /*Take the second int of each line and put it in Arrival_Time array*/
      for (int a = 1; a < i; a++)
      {
         arrivalTime[y] = integers[a];
         // printf("\n%d\n", arr2[y]);
         a=a+2;
         y++;
      }
      /*Take the third int of each line and put it in Duration array*/
      for (int a = 2; a < i; a++)
      {
         duration[z] = integers[a];
         // printf("\n%d\n", arr3[z]);
         a=a+2;
         z++;
      }
      fclose(fp);
      //Printing arrays to verify numbers are correct
      // for (int i = 0; i < x; i++){
      //    printf("\n%d\n", arr1[i]);
      //    printf("\n%d\n", arr2[i]);
      //    printf("\n%d\n", arr3[i]);
      // }

      //Calling each scheduling algorithm
      FIFO(jobIDs, arrivalTime, duration);
      // SJF(arr1, arr2, arr3);
      // BJF(arr1, arr2, arr3);
      // STCF(arr1, arr2, arr3);
      // RR(arr1, arr2, arr3);
      free(jobIDs);
      free(arrivalTime);
      free(duration);
   }
   else
   {
      perror(filename); /* why didn't the file open? */
   }
   return 0;
}