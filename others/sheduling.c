#include <stdio.h>

struct process
{
    int id;
    int burstTime;
    int arrivalTime;
    int startTime;
    int remainingTime;
    int priority;
    int slices;
    int remainingSlices;
};

/*void delete(struct process p, int front, int rear, struct process queue[]);
void insert(struct process p, int n, int front, int rear, struct process queue[]);*/

void main()
{
    int n, opt = 0;

    while (opt != 5)
    {
        printf("\n\t\tMENU:\n");
        printf("1)FCFS\n");
        printf("2)SJFS\n");
        printf("3)Priority Scheduling\n");
        printf("4)Round Robin Scheduling\n");
        printf("5)Exit\n");

        scanf("%d", &opt);

        if (opt > 0 && opt < 5)
        {
            printf("Enter number of processes.");
            scanf("%d", &n);
            struct process p[n];

            switch (opt)
            {
            case 1:
                fcfs(p, n);
                break;
            case 2:
                sjf(p, n);
                break;
            case 3:
                priority(p, n);
                break;
            case 4:
                roundRob(p, n);
                break;
            case 5:
                break;
            default:
                printf("Enter Valid Option\n");
                break;
            }
        }
    }
}

void sortFCFS(struct process p[], int n)
{
    struct process temp;
    int i, key, j, smallest = 0;
    for (i = 0; i < n; i++)
    {
        smallest = i;
        for (j = i + 1; j < n; ++j)
        {
            if ((p[j].arrivalTime) < (p[smallest].arrivalTime))
            {
                smallest = j;
            }
        }
        temp = p[i];
        p[i] = p[smallest];
        p[smallest] = temp;
    }
}

void fcfs(struct process p[], int n)
{

    int covered = 0, i = 0, j = 0;
    float avgWT = 0, avgTAT = 0;

    userInput(p, n, 0);
    sortFCFS(p, n);

    for (i = 0; covered < n; ++i)
    {
        //printf("i:%d",i);
        for (j = 0; j < n; ++j)
        {
            if (p[j].arrivalTime == i || ((p[j].arrivalTime < i) && (p[j].remainingTime != 0)))
            {
                p[j].startTime = i;
                //printf("%dstart",i);
                i += ((p[j].burstTime) - 1);
                p[j].remainingTime = 0;
                covered++;
                break;
            }
        }
    }

    for (i = 0; i < n; ++i)
    {
        //printf("%d is %d and %d\n",p[i].arrivalTime, p[i].startTime, p[i].burstTime);
        avgWT += (p[i].startTime - p[i].arrivalTime);
        avgTAT += (p[i].burstTime + (p[i].startTime - p[i].arrivalTime));
    }
    avgWT = avgWT / n;
    avgTAT = avgTAT / n;
    printf("Average Waiting Time is %f and Average Turnaround Time is %f\n", avgWT, avgTAT);
}

void sjf(struct process p[], int n)
{

    int covered = 0, i = 0, j = 0, shortest;
    float avgWT = 0, avgTAT = 0;

    userInput(p, n, 0);

    sortFCFS(p, n);

    for (i = 0; covered < n; ++i)
    {
        //printf("i:checking %d " ,i);
        shortest = -1;
        for (j = 0; j < n; ++j) //assume shortest
        {
            if (p[j].arrivalTime == i || ((p[j].arrivalTime < i) && (p[j].remainingTime != 0)))
            {

                shortest = j;
                //printf("\nthis is checking %d for %d\n", i,shortest);
                break;
            }
        }

        for (j = 0; j < n; ++j) //find shortest
        {
            if (p[j].arrivalTime == i || ((p[j].arrivalTime < i) && (p[j].remainingTime != 0))) //check availability of process in ith second
            {
                if (p[j].burstTime < p[shortest].burstTime)
                {
                    shortest = j;
                    //printf("second loop with %d and %d\n",p[j].burstTime, p[shortest].burstTime);
                }
            }
        }
        if (shortest != -1) //process excecution
        {
            p[shortest].startTime = i;
            //printf("\nthis is %d for %d\n", i,highest);
            i += ((p[shortest].burstTime) - 1);
            p[shortest].remainingTime = 0;
            covered++;
        }
    }

    for (i = 0; i < n; ++i)
    {
        //printf("%d is %d and %d\n",p[i].arrivalTime, p[i].startTime, p[i].burstTime);
        avgWT += (p[i].startTime - p[i].arrivalTime);
        avgTAT += (p[i].burstTime + (p[i].startTime - p[i].arrivalTime));
    }
    avgWT = avgWT / n;
    avgTAT = avgTAT / n;
    printf("Average Waiting Time is %f and Average Turnaround Time is %f\n", avgWT, avgTAT);
}

void userInput(struct process p[], int n, int priority)
{
    int i;
    for (i = 0; i < n; ++i)
    {

        printf("Enter arrival time of process %d: \n", i + 1);
        scanf("%d", &p[i].arrivalTime);

        printf("Enter burst time of process %d: \n", i + 1);
        scanf("%d", &p[i].burstTime);

        if (priority == 1)
        {
            printf("Enter priority of process %d: \n", i + 1);
            scanf("%d", &p[i].priority);
        }

        p[i].id = i;

        p[i].remainingTime = p[i].burstTime;
        p[i].startTime = -1;
        p[i].slices = -1;
        printf("\n");
    }
}

void priority(struct process p[], int n)
{

    int i = 0, j = 0, highest = 0, covered = 0;
    float avgWT = 0, avgTAT = 0;

    userInput(p, n, 1);

    sortFCFS(p, n);

    for (i = 0; covered < n; ++i)
    {
        //printf("i:checking %d " ,i);
        highest = -1;
        for (j = 0; j < n; ++j)
        {
            if (p[j].arrivalTime == i || ((p[j].arrivalTime < i) && (p[j].remainingTime != 0)))
            {

                highest = j;
                //printf("\nthis is checking %d for %d\n", i,highest);
                break;
            }
        }
        for (j = 0; j < n; ++j)
        {
            if (p[j].arrivalTime == i || ((p[j].arrivalTime < i) && (p[j].remainingTime != 0)))
            {
                if (p[j].priority < p[highest].priority)
                {
                    highest = j;
                    //printf("second loop with %d and %d\n",p[j].priority, p[highest].priority);
                }
            }
        }
        if (highest != -1)
        {
            p[highest].startTime = i;
            //printf("\nthis is %d for %d\n", i,highest);
            i += ((p[highest].burstTime) - 1);
            p[highest].remainingTime = 0;
            covered++;
        }
    }

    for (i = 0; i < n; ++i)
    {
        //printf("%d is %d and %d\n",p[i].arrivalTime, p[i].startTime, p[i].burstTime);
        avgWT += (p[i].startTime - p[i].arrivalTime);
        avgTAT += (p[i].burstTime + (p[i].startTime - p[i].arrivalTime));
    }
    avgWT = avgWT / n;
    avgTAT = avgTAT / n;
    printf("Average Waiting Time is %f and Average Turnaround Time is %f\n", avgWT, avgTAT);
}

void roundRobin2(struct process p[], int n)
{

    int covered = 0, i = 0, j = 0, k = 0, timeSlice, sliceCounter = 0;
    float avgWT = 0, avgTAT = 0;
    userInput(p, n, 0);

    printf("Enter Time Slice: \n");
    scanf("%d", &timeSlice);

    sortFCFS(p, n);

    for (i = 0; covered < n; ++i)
    {
        //printf("i:%d\n",i);
        for (j = 0; j < n; ++j)
        {
            //printf("boing : %d %d : %d\n", p[j].burstTime, p[j].remainingTime, sliceCounter);
            if (p[j].arrivalTime == i || ((p[j].arrivalTime < i) && (p[j].remainingTime != 0) && ((p[j].burstTime - p[j].remainingTime) == sliceCounter)))
            {
                //printf("process %d starts %d\n",j,i);
                //if(p[j].remainingTime!=p[j].burstTime);
                if (p[j].startTime == -1)
                {
                    p[j].startTime = i;
                    avgWT += (p[j].startTime - p[j].arrivalTime);
                }
                else
                {
                    avgWT += i;
                }

                //printf("%dstart",i);
                if (p[j].remainingTime <= timeSlice)
                {
                    i += ((p[j].remainingTime) - 1);
                    p[j].remainingTime = 0;
                    covered++;
                    avgWT += (i + 1);
                }
                else
                {
                    i += ((timeSlice)-1);
                    p[j].remainingTime -= timeSlice;
                }

                //printf("process %d stops %d\n",j,i);
                avgWT -= (i + 1);
                //printf("avgWT:  %f",avgWT);
                break;
            }
        }
        for (k = 0; k < n; ++k)
        {
            if ((p[k].burstTime - p[k].remainingTime == sliceCounter) && p[k].remainingTime != 0)
            {
                //printf("this is %d with %d and %d\n",k,p[k].burstTime, p[k].remainingTime);
                break;
            }
        }
        if (k == n)
        {
            //printf("BAZINGA\n\n");
            sliceCounter += timeSlice;
        }
    }

    for (i = 0; i < n; ++i)
    {
        //printf("%d is %d and %d\n",p[i].arrivalTime, p[i].startTime, p[i].burstTime);
        //avgWT += (p[i].startTime - p[i].arrivalTime);
        avgTAT += (p[i].burstTime);
    }
    avgTAT += avgWT;
    avgWT = avgWT / n;
    avgTAT = avgTAT / n;
    printf("Average Waiting Time is %f and Average Turnaround Time is %f\n", avgWT, avgTAT);
}

void roundRobin(struct process p[], int n)
{

    int covered = 0, i = 0, j = 0, k = 0, timeSlice, sliceCounter = 0;
    float avgWT = 0, avgTAT = 0;
    userInput(p, n, 0);
    struct process *ready_queue[n];
    int front = -1, rear = -1;

    printf("Enter Time Slice: \n");
    scanf("%d", &timeSlice);

    //sliceCalc(ready_queue, n, timeSlice);
    sortFCFS(p, n);

    for (i = 0; covered < n; ++i)
    {
        printf("i:%d\n", i);
        for (j = 0; j < n; ++j)
        {
            if (i >= p[j].arrivalTime)
            {
                printf("boing : %d %d : %d\n", p[j].burstTime, p[j].remainingTime, sliceCounter);
                if (rear != -1)
                {
                    printf("BAZINGA\n\n");
                    if ((isPresent(p[j], front, rear, ready_queue) != 1) && (p[j].remainingTime != 0))
                        ;
                    {
                        printf("BAZINGA\n\n");
                        if (ready_queue[front]->id != p[j].id)
                        {
                            //p[j].remainingSlices+=timeSlice;
                            printf("test\n");
                            insert(p[j], n, &front, &rear, ready_queue);
                        }
                    }
                }
                else
                {
                    printf("BAZONGA\n\n");
                    //p[j].remainingSlices+=timeSlice;
                    insert(p[j], n, &front, &rear, ready_queue);
                }
            }
        }

        if (rear != -1)
        {
            ready_queue[front]->remainingTime--;
            ready_queue[front]->remainingSlices--;
            /*for(k=0;k<n;++k)
            {
                if(p[k].id==ready_queue[front]->id)
                {
                    p[k].remainingTime--;
                    p[k].remainingSlices--;
                }
            }*/
            if (ready_queue[front]->remainingTime == 0)
            {
                printf("reached");
                covered++;
            }
            if ((ready_queue[front]->remainingTime == 0) || (p[k].remainingSlices == 0))
            {
                delete (p[k], &front, &rear, ready_queue);
            }
        }

        for (k = 0; k < n; ++k)
        {
            if ((p[k].burstTime - p[k].remainingTime == sliceCounter) && p[k].remainingTime != 0)
            {
                break;
            }
        }
        if (k == n)
        {
            //printf("BAZINGA\n\n");
            sliceCounter += timeSlice;
        }
    }

    for (i = 0; i < n; ++i)
    {
        //printf("%d is %d and %d\n",p[i].arrivalTime, p[i].startTime, p[i].burstTime);
        //avgWT += (p[i].startTime - p[i].arrivalTime);
        avgTAT += (p[i].burstTime);
    }
    avgTAT += avgWT;
    avgWT = avgWT / n;
    avgTAT = avgTAT / n;
    printf("Average Waiting Time is %f and Average Turnaround Time is %f\n", avgWT, avgTAT);
}

int isPresent(struct process p, int front, int rear, struct process *queue[])
{
    int i;
    if (rear == -1)
        return 0;
    printf("front %d rear %d idtocheck %d quefront %d\n", front, rear, p.id, queue[0]->id);
    for (i = front; i <= rear; ++i)
    {
        printf("\nque: %d p:%d at index%d \n", queue[i]->id, p.id, i);
        if (queue[i]->id == p.id)
        {
            printf("isPsent Returned One\n");
            return 1;
        }
    }
    if (i == rear + 1)
    {
        return 0;
    }
}

void insert(struct process p, int n, int *front, int *rear, struct process *queue[])
{
    printf("what %d is p", p.id);
    printf("insert %d-%d", *rear, *front);
    if ((*rear) == n - 1)
    {
        printf("Overflow");
    }
    else
    {
        if ((*rear) == -1)
        {
            (*front) = 0;
            (*rear) = 0;
            printf("conf");
        }
        else
        {
            (*rear)++;
        }
        queue[(*rear)] = &p;
        // printf("%d is que and %d is p", 0, p.id)
    }
    printf("%d is what is %d \n", queue[(*rear)]->burstTime, queue[0]->burstTime);
    printf("insert2 %d-%d", *rear, *front);
    printf("inserted process at %d\n", (*rear));

    /*
    4
    3
    0
    3
    2
    5
    3
    1
    2



    */
}

void delete (struct process p, int *front, int *rear, struct process *queue[])
{
    printf("delete %d-%d", *rear, *front);
    if ((*rear) == -1)
    {
        printf("Underflow");
    }
    else
    {
        if ((*front) == (*rear))
        {
            (*front) = -1;
            (*rear) = -1;
        }
        else
        {
            (*front)++;
        }
    }
}

/*void sliceCalc(struct process* queue[], int n, int quantum)
{
     int slices=0;
     for(int i=0;i<n;++i)
     {
         slices = queue[i]->burstTime/quantum;
         if(queue[i]->burstTime%quantum!=0)
         {
             slices++;
         }
         queue[i]->totalSlices = slices;
         queue[i]->remainingSlices = slices;
     }
}*/

void roundRob(struct process p[], int n)
{

    int covered = 0, i = 0, j = 0, k = 0, timeSlice, sliceCounter = 0;
    float avgWT = 0, avgTAT = 0;
    userInput(p, n, 0);
    struct process *ready_queue[n];
    int front = -1, rear = -1;

    printf("Enter Time Slice: \n");
    scanf("%d", &timeSlice);

    //sliceCalc(ready_queue, n, timeSlice);
    sortFCFS(p, n);

    for (i = 0; covered < n; ++i)
    {
        printf("\n\ni:%d\n", i);

        for (j = 0; j < n; ++j)
        {
            printQueue(ready_queue, front, rear);
            if (i >= p[j].arrivalTime)
            {
                //check if present in queue
                if ((isPresent(p[j], front, rear, ready_queue) != 1) && (p[j].remainingTime != 0))
                {
                    printf("yes");
                    p[j].slices = timeSlice;
                    printf("inserting %d", p[j].id);
                    insert(p[j], n, &front, &rear, ready_queue);
                }
            }
        }
        if (rear != -1)
        {
            ready_queue[front]->remainingTime--;
            if (ready_queue[front]->remainingTime == 0)
            {
                covered++;
            }
            ready_queue[front]->slices--;
            printf("running %d remaining: %d\n", ready_queue[front]->id, ready_queue[front]->slices);
            if (ready_queue[front]->slices == 0)
            {
                printf("deleting %d", ready_queue[front]->id);
                delete (*(ready_queue[front]), &front, &rear, ready_queue);
            }
        }
    }
    /*
    4
    3
    0
    3
    2
    5
    3
    1
    2



    */
}

void printQueue(struct process *queue[], int front, int rear)
{
    printf("Printing %d %d\n", front, rear);
    int i = 0;
    for (i = front; i <= rear; ++i)
    {
        printf("index%d - %d\n", i, queue[i]->id);
    }
    printf("End Printing\n");
}