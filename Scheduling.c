#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

//    /*FIFO*/
void FIFO(int *arr1, int *arr2, int *arr3)
{
   int x = sizeof(arr1)/2;
   int y = sizeof(arr2)/2;
   int z = sizeof(arr3)/2;

   int bt[100], waitTime[100], turnaroundTime[100], startTime[100], endTime[100], avgWaitTime = 0, avgTurnaroundTime = 0, i, j;
   int temp1, temp2, temp3;
   waitTime[0] = 0; //waiting time for first process is 0

   //sorting arrival time in ascending order using selection sort
   for(i = 0; i < y; i++) {
      for(j=i+1; j < y; j++) {
         if(arr2[j]< arr2[i])
         {
            temp1 = arr1[i];
            arr1[i] = arr1[j];
            arr1[j] = temp1;

            temp2 = arr2[i];
            arr2[i] = arr2[j];
            arr2[j] = temp2;

            temp3 = arr3[i];
            arr3[i] = arr3[j];
            arr3[j] = temp3;
         }
      }
      printf("\n%d\t\t%d\t\t%d", arr1[i], arr2[i], arr3[i]);
   }

   //calculating waiting time
   for (i = 0; i < y; i++)
   {
      waitTime[i] = 0;
      for (j = 0; j <= i; j++){
         waitTime[i] += arr2[j];
      }
   }

   printf("\nProcess\t\tWait Time\tT.A Time\tStart Time\t\tEnd Time");
   //calculating turnaround time
   for (i = 0; i < y; i++)
   {
      
      startTime[i] = waitTime[i] + arr2[i];
      endTime[i] = startTime[i] + arr3[i];
      turnaroundTime[i] = endTime[i] - startTime[i];
      avgWaitTime += waitTime[i];
      avgTurnaroundTime += turnaroundTime[i];
      printf("\nP[%d]\t\t\t%d\t\t\t\t\t\t%d\t\t%d\t\t%d", arr1[i], waitTime[i], turnaroundTime[i], startTime[i], endTime[i]);
   }

   avgWaitTime /= i;
   avgTurnaroundTime /= i;
   printf("\n\nAverage Waiting Time:%d", avgWaitTime);
   printf("\nAverage Turnaround Time:%d", avgTurnaroundTime);
}
/*SJF*/
int SJF(int *arr1, int *arr2, int *arr3)
{
   int x = sizeof(arr1)/2;
   int y = sizeof(arr2)/2;
   int z = sizeof(arr3)/2;

   int bt[100], waitTime[100], turnaroundTime[100], startTime[100], endTime[100], avgWaitTime = 0, avgTurnaroundTime = 0, i, j;
   int n, total = 0, pos1, pos2, pos3, temp1, temp2, temp3;
   int a;

   //sorting duration in ascending order using selection sort
   for(i = 0; i < y; i++) {
      for(j=i+1; j < y; j++) {
         if(arr2[j]< arr2[i] && arr3[j] < arr3[i])
         {
            temp1 = arr1[i];
            arr1[i] = arr1[j];
            arr1[j] = temp1;

            temp2 = arr2[i];
            arr2[i] = arr2[j];
            arr2[j] = temp2;

            temp3 = arr3[i];
            arr3[i] = arr3[j];
            arr3[j] = temp3;
         }
      }
      printf("\n%d\t\t%d\t\t%d", arr1[i], arr2[i], arr3[i]);
   }
   waitTime[0] = 0; //waiting time for first process will be zero

   //calculate waiting time
   for (i = 1; i < y; i++)
   {
      waitTime[i] = 0;
      for (j = 0; j <= i; j++)
         waitTime[i] += arr2[j];
   }

   printf("\nProcess\t\tWaiting Time\tTurnaround Time");
   for (i = 0; i < n; i++)
   {
      startTime[i] = waitTime[i] + arr2[i];
      endTime[i] = startTime + arr3[i];
      turnaroundTime[i] = endTime[i] - startTime[i]; //calculate turnaround time
      avgWaitTime += waitTime[i];
      avgTurnaroundTime += turnaroundTime[i];
      printf("\np%d\t\t     %d\t\t\t%d", arr1[i], waitTime[i], turnaroundTime[i]);
   }

   avgWaitTime /= i;
   avgTurnaroundTime /= i;
   printf("\n\nAverage Waiting Time:%d", avgWaitTime);
   printf("\nAverage Turnaround Time:%d", avgTurnaroundTime);
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
         a=a+2;
         y++;
      }
      /*Take the third int of each line and put it in Duration array*/
      for (int a = 2; a < i; a++)
      {
         duration[z] = integers[a];
         a=a+2;
         z++;
      }
      fclose(fp);

      //Calling each scheduling algorithm
      FIFO(jobIDs, arrivalTime, duration);
      SJF(jobIDs, arrivalTime, duration);
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