#include<stdio.h>

int main()
{
    int p[20], bt[20], su[20], wt[20], tat[20], priority[20], i, k, n, temp;
    float wtavg, tatavg;
    int threshold = 5; // Set the waiting time threshold for priority boosting

    printf("Enter the number of processes:");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        p[i] = i;
        printf("Enter the Burst Time of Process%d:", i);
        scanf("%d", &bt[i]);
        printf("System/User Process (0/1) ? ");
        scanf("%d", &su[i]);
        priority[i] = su[i]; // Initialize priority level same as system/user process indicator
    }

    for(i = 0; i < n; i++)
    {
        for(k = i + 1; k < n; k++)
        {
            // Sort based on system/user process indicator and priority level
            if(su[i] > su[k] || (su[i] == su[k] && priority[i] > priority[k]))
            {
                temp = p[i];
                p[i] = p[k];
                p[k] = temp;

                temp = bt[i];
                bt[i] = bt[k];
                bt[k] = temp;

                temp = su[i];
                su[i] = su[k];
                su[k] = temp;

                temp = priority[i];
                priority[i] = priority[k];
                priority[k] = temp;
            }
        }
    }

    wtavg = wt[0] = 0;
    tatavg = tat[0] = bt[0];

    for(i = 1; i < n; i++)
    {
        // Check if process has been waiting for threshold time, increase priority if true
        if(wt[i-1] >= threshold)
        {
            priority[i]++; // Boost priority
        }

        wt[i] = wt[i-1] + bt[i-1];
        tat[i] = tat[i-1] + bt[i];
        wtavg = wtavg + wt[i];
        tatavg = tatavg + tat[i];
    }

    printf("\nPROCESS\t\t SYSTEM/USER PROCESS \t PRIORITY \t BURST TIME \t WAITING TIME \t TURNAROUND TIME");
    for(i = 0; i < n; i++)
    {
        printf("\n%d \t\t %d \t\t\t %d \t\t %d \t\t %d \t\t %d", p[i], su[i], priority[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time is --- %f", wtavg/n);
    printf("\nAverage Turnaround Time is --- %f", tatavg/n);

    return 0;
}
