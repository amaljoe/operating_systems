#include <stdio.h>
#include <conio.h>
#define max 30
void main()
{
    int i, j, n, temp, bt[max], p[max], wt[max], tat[max];
    float awt = 0, atat = 0;
    printf("enter no of process");
    scanf("%d", &n);
    printf("enter process number");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &p[i]);
    }
    printf("enter bt");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &bt[i]);
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (bt[j] > bt[j + 1])
            {
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    printf("process \t burst time \t waiting time \t turnaroundtime\n");
    for (i = 0; i < n; i++)
    {
        wt[i] = 0;
        tat[i] = 0;
        for (j = 0; j < i; j++)
        {
            wt[i] = wt[i] + bt[j];
        }
        tat[i] = wt[i] + bt[i];
        awt = awt + wt[i];
        atat = atat + tat[i];
        printf("%d\t %d\t\t %d\t\t %d\n", p[i], bt[i], wt[i], tat[i]);
    }
    awt = awt / n;
    atat = atat / n;
    printf("avg wt is %f", awt);
    printf("avg tat is %f", atat);
}

// 5
// 1 2 3 4 5
// 1 5 1 6 3