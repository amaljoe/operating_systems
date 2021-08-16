#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10
#define DEV true

typedef struct Process
{
    int id;
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
        size = 5;
        Process p0 = {0, 0, 8, 4};
        Process p1 = {1, 2, 6, 1};
        Process p2 = {2, 2, 1, 2};
        Process p3 = {3, 1, 9, 2};
        Process p4 = {4, 3, 3, 3};
        p[0] = p0;
        p[1] = p1;
        p[2] = p2;
        p[3] = p3;
        p[4] = p4;
        return;
    }

    printf("Enter the number of processes:\n");
    scanf("%d", &size);

    for (int i = 0; i < size; i++)
    {
        Process temp;
        temp.id = i;
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
    // loop over every processes at all instances of time
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
                // process already completed
                completed++;
                continue;
            }
            if (t < p[i].at)
            {
                // process yet to arrive
                continue;
            }
            // if no processes are running, run this process
            if (active == NULL)
            {
                active = &p[i];
            }
            if (active == &p[i])
            {
                // process is running
                p[i].bt--;
            }
            else
            {
                // process is waiting
                p[i].wt++;
                total_wt++;
            }
            p[i].tat++;
            total_tat++;
        }
        // if all processes completed, stop
        if (completed >= size)
        {
            break;
        }
        t++;
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
    // loop over every processes at all instances of time
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
                // process already completed
                completed++;
                continue;
            }
            if (t < p[i].at)
            {

                // process yet to arrive
                continue;
            }
            // if no process is running, run the shortest process in the queue
            if (active == NULL)
            {
                // find the process with shortest burst time
                if (shortest == NULL || p[i].bt < shortest->bt)
                {
                    shortest = &p[i];
                }
                else if (shortest == NULL || p[i].bt == shortest->bt)
                {
                    // if burst time is equal, tie breaker for SJF is arrival time
                    if (p[i].at < shortest->at)
                    {
                        shortest = &p[i];
                    }
                }
            }
            if (active == &p[i])
            {
                // process is running
                p[i].bt--;
            }
            else
            {
                // process is waiting
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
    // loop over every processes at all instances of time
    while (true)
    {
        int n = 0;
        // if the active process is completed or if its time slice is over, remove it
        if (active != NULL && active->bt <= 0 || ts <= 0)
        {
            n = (active->id + 1) % size;
            active = NULL;
            ts = time_slice;
        }
        completed = 0;
        bool flag = true;
        for (int i = n; i != n || flag; i = ++i % size)
        {
            flag = false;
            if (p[i].bt <= 0)
            {
                // process already completed
                completed++;
                continue;
            }
            if (t < p[i].at)
            {
                // process yet to arrive
                continue;
            }
            // if no process is running, run this process
            if (active == NULL)
            {
                active = &p[i];
            }
            if (active == &p[i])
            {
                // running process
                ts--;
                p[i].bt--;
            }
            else
            {
                // waiting process
                p[i].wt++;
                total_wt++;
            }
            p[i].tat++;
            total_tat++;
        }
        // if all processes are completed, stop
        if (completed >= size)
        {
            break;
        }
        t++;
    }
    avg_wt = total_wt / size;
    avg_tat = total_tat / size;
}

void priority()
{
    int t = 0;
    double total_wt = 0;
    double total_tat = 0;
    int completed = 0;
    Process *active = NULL;
    // loop over every processes at all instances of time
    while (true)
    {
        if (active != NULL && active->bt <= 0)
        {
            printf("p%d exiting at %d\n", active->id + 1, t);
            active = NULL;
        }
        completed = 0;
        Process *highest_priority = NULL;
        for (int i = 0; i < size; i++)
        {
            if (p[i].bt <= 0)
            {
                // process already completed
                completed++;
                continue;
            }
            if (t < p[i].at)
            {

                // process yet to arrive
                continue;
            }
            // if no process is running, run the shortest process in the queue
            if (active == NULL)
            {
                // find the process with highest priority (low value = high priority)
                if (highest_priority == NULL || p[i].priority < highest_priority->priority)
                {
                    highest_priority = &p[i];
                }
                else if (highest_priority == NULL || p[i].bt == highest_priority->bt)
                {
                    // if burst time is equal, tie breaker for SJF is arrival time
                    if (p[i].at < highest_priority->at)
                    {
                        highest_priority = &p[i];
                    }
                }
            }
            if (active == &p[i])
            {
                // process is running
                p[i].bt--;
            }
            else
            {
                // process is waiting
                p[i].wt++;
                total_wt++;
            }
            p[i].tat++;
            total_tat++;
        }
        // if no process is running, run the highest priority process
        if (active == NULL && highest_priority != NULL)
        {
            active = highest_priority;
            active->bt--;
            active->wt--;
            total_wt--;
        }
        // if all processes are completed, stop
        if (completed >= size)
        {
            break;
        }
        t++;
    }
    avg_wt = total_wt / size;
    avg_tat = total_tat / size;
}

void output()
{
    printf("\nAverage waiting time: %.2f\n", avg_wt);
    printf("Average turn around time: %.2f\n", avg_tat);
}