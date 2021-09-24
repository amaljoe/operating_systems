#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10
// set DEV to true for predefined inputs
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

Process *queue[MAX];
int rear = -1;
int front = -1;

void fcfs();
void sjf();
void round_robin(int);
void round_robin2(int);
void priority();
void input(bool);
void output();
bool insert(Process *);
Process *delete ();

int main()
{
    int ch;
    printf("\nEnter your scheduling algorithm choice:\n1. FCFS 2. SJF 3. Round Robin 4. Priority\n");
    scanf("%d", &ch);
    // menu driven program
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
        round_robin2(ts);
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
    // predefined inputs for development
    if (DEV)
    {
        size = 6;
        Process p0 = {1, 0, 5, 0};
        Process p1 = {2, 1, 6, 0};
        Process p2 = {3, 2, 3, 0};
        Process p3 = {4, 3, 1, 0};
        Process p4 = {5, 4, 5, 0};
        Process p5 = {6, 6, 4, 0};
        p[0] = p0;
        p[1] = p1;
        p[2] = p2;
        p[3] = p3;
        p[4] = p4;
        p[5] = p5;
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
        // only input priority for priority scheduling algorithm
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
    // loop over every process at all instances of time
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

void sjf()
{
    int t = 0;
    double total_wt = 0;
    double total_tat = 0;
    int completed = 0;
    Process *active = NULL;
    // loop over every process at all instances of time
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
        // if no process is running, run the shortest process
        if (active == NULL && shortest != NULL)
        {
            active = shortest;
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

void round_robin(int time_slice)
{
    int t = 0;
    double total_wt = 0;
    double total_tat = 0;
    int completed = 0;
    Process *active = NULL;
    int ts = time_slice;
    // loop over every process at all instances of time
    while (true)
    {
        int n = 0;
        // if the running process is completed or if its time slice is over, remove it
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

bool insert(Process *pr)
{
    if (front == (rear + 1) % MAX)
    {
        return false;
    }
    if (front == -1)
    {
        front = 0;
    }
    rear = (rear + 1) % MAX;
    queue[rear] = pr;
    return true;
}

Process *delete ()
{
    if (front == -1)
    {
        return NULL;
    }
    Process *pr = queue[front];
    queue[front] = NULL;
    if (front == rear)
    {
        front = -1;
        rear = -1;
    }
    else
    {
        front = (front + 1) % MAX;
    }
    return pr;
}

void round_robin2(int time_slice)
{
    int t = 0;
    double total_wt = 0;
    double total_tat = 0;
    int completed = 0;
    Process *active = NULL;
    int ts = time_slice;
    // loop over every process at all instances of time
    while (true)
    {
        int n = 0;
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
            // if process just arrived, put it in ready queue
            if (p[i].at == t)
            {
                insert(&p[i]);
            }

            p[i].wt++;
            total_wt++;
            p[i].tat++;
            total_tat++;
        }
        // if the running process is completed or if its time slice is over, remove it
        if (active != NULL && active->bt <= 0 || ts <= 0)
        {
            // if process is pending put in ready queue
            if (active->bt > 0)
            {
                insert(active);
            }
            n = (active->id + 1) % size;
            active = NULL;
            ts = time_slice;
        }
        // if no process is running, run the first process in ready queue
        if (active == NULL)
        {
            active = delete();
        }
        if (active != NULL)
        {
            // running process
            ts--;
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

void priority()
{
    int t = 0;
    double total_wt = 0;
    double total_tat = 0;
    int completed = 0;
    Process *active = NULL;
    // loop over every process at all instances of time
    while (true)
    {
        // if running process is complete, remove it
        if (active != NULL && active->bt <= 0)
        {
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
                else if (highest_priority == NULL || p[i].priority == highest_priority->priority)
                {
                    // if priority is equal, tie breaker is arrival time
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