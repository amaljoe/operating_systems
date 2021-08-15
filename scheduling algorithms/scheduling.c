#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10
#define DEV true

typedef struct Process
{
    int num;
    int at;
    int bt;
    int priority;

    int wt;
    int tat;
} Process;

Process p[MAX];
int size;
double avg_wt;
double avg_tat;

void fcfs();
void sjf();
void round_robin(int);
void priority();
void input(bool);
void output();

int main()
{
    int ch;
    printf("\nEnter your scheduling algorithm choice:\n1. FCFS 2. SJF 3. Round Robin 4. Priority\n");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        input(false);
        fcfs();
        break;
    case 2:
        input(false);
        sjf();
        break;
    case 3:
        input(false);
        int ts;
        printf("\nEnter the time slice:\n");
        scanf("%d", &ts);
        round_robin(ts);
        break;
    case 4:
        input(true);
        priority();
        break;
    default:
        printf("Invalid option\n");
        return 1;
    }
    output();
    return 0;
}

void input(bool get_priority)
{
    if (DEV)
    {
        size = 4;
        Process p0 = {0, 0, 13, 1};
        Process p1 = {1, 2, 9, 1};
        Process p2 = {2, 2, 5, 1};
        Process p3 = {3, 3, 7, 1};
        p[0] = p0;
        p[1] = p1;
        p[2] = p2;
        p[3] = p3;
        return;
    }

    printf("Enter the number of processes:\n");
    scanf("%d", &size);

    for (int i = 0; i < size; i++)
    {
        Process temp;
        temp.num = i;
        printf("Enter the arrival time of p%d:\n", i);
        scanf("%d", &temp.at);
        printf("Enter the burst time of p%d:\n", i);
        scanf("%d", &temp.bt);
        if (get_priority)
        {
            printf("Enter the priority of p%d:\n", i);
            scanf("%d", &temp.priority);
        }
        else
        {
            temp.priority = 1;
        }
        p[i] = temp;
    }
}

void fcfs()
{
    int t = 0;
    double total_wt = 0;
    double total_tat = 0;
    int completed = 0;
    Process *active = NULL;
    while (true)
    {
        if (active != NULL && active->bt <= 0)
        {
            active = NULL;
        }
        completed = 0;
        for (int i = 0; i < size; i++)
        {
            if (p[i].bt <= 0)
            {
                printf("inactive, already finished\n");
                completed++;
                continue;
            }
            if (t < p[i].at)
            {

                printf("inactive, yet to come\n");
                continue;
            }
            printf("already came and is not finished\n");
            if (active == NULL)
            {
                active = &p[i];
            }
            if (active == &p[i])
            {
                p[i].bt--;
            }
            else
            {
                p[i].wt--;
                total_wt++;
            }
            p[i].tat--;
            total_tat++;
        }
        if (completed >= size)
        {
            break;
        }
        t++;
        printf("\n");
    }
    avg_wt = total_wt / size;
    avg_tat = total_tat / size;
}

void sjf()
{
    int t = 0;
    double total_wt = 0;
    double total_tat = 0;
    int completed = 0;
    Process *active = NULL;
    while (true)
    {
        if (active != NULL && active->bt <= 0)
        {
            active = NULL;
        }
        completed = 0;
        Process *shortest = NULL;
        for (int i = 0; i < size; i++)
        {
            if (p[i].bt <= 0)
            {
                printf("inactive, already finished\n");
                completed++;
                continue;
            }
            if (t < p[i].at)
            {

                printf("inactive, yet to come\n");
                continue;
            }

            printf("already came and is not finished\n");
            if (active == NULL)
            {
                if (shortest == NULL || p[i].bt < shortest->bt)
                {
                    shortest = &p[i];
                }
                else if (shortest == NULL || p[i].bt == shortest->bt)
                {
                    // Tie breaker for SJF is arrival time
                    if (p[i].at < shortest->at)
                    {
                        shortest = &p[i];
                    }
                }
            }

            if (active == &p[i])
            {
                p[i].bt--;
            }
            else
            {
                p[i].wt++;
                total_wt++;
            }
            p[i].tat++;
            total_tat++;
        }
        if (active == NULL && shortest != NULL)
        {
            active = shortest;
            active->bt--;
            active->wt--;
            total_wt--;
        }
        if (completed >= size)
        {
            break;
        }
        t++;
        printf("\n");
    }
    avg_wt = total_wt / size;
    avg_tat = total_tat / size;
}

void round_robin(int time_slice)
{
    int t = 0;
    double total_wt = 0;
    double total_tat = 0;
    int completed = 0;
    Process *active = NULL;
    int ts = time_slice;
    while (true)
    {
        int n = 0;
        // if the active process is completed or if its time slice is over, remove it
        if (active != NULL && active->bt <= 0 || ts <= 0)
        {
            n = active->num + 1;
            printf("p%d exiting at %d", n, t);
            active = NULL;
            ts = time_slice;
        }
        completed = 0;
        int i = n % size;
        do
        {
            if (p[i].bt <= 0)
            {
                // process already completed
                printf("inactive, already finished\n");
                completed++;
                i = ++i % size;
                continue;
            }
            if (t < p[i].at)
            {
                // process yet to arrive
                printf("inactive, yet to come %d %d\n", t, p[i].at);
                i = ++i % size;
                continue;
            }
            printf("already came and is not finished\n");
            // if no process is running, run the current process
            if (active == NULL)
            {
                active = &p[i];
            }
            if (active == &p[i])
            {
                // this process is running
                p[i].bt--;
                ts--;
            }
            else
            {
                // this process is waiting
                p[i].wt--;
                total_wt++;
            }
            p[i].tat--;
            total_tat++;
            i = ++i % size;
        } while (i != n);
        if (completed >= size)
        {
            break;
        }
        t++;
        printf("\n");
    }
    avg_wt = total_wt / size;
    avg_tat = total_tat / size;
}

void priority()
{
    avg_wt = 1;
    avg_tat = 3;
}

void output()
{
    printf("\nAverage waiting time: %f\n", avg_wt);
    printf("Average turn around time: %f\n", avg_tat);
}