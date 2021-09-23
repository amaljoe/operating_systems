#include <stdio.h>
#define MAX_PROCESS 10
#define MAX_REQUEST 5

int available[MAX_REQUEST];
int max[MAX_PROCESS][MAX_REQUEST];
int alloc[MAX_PROCESS][MAX_REQUEST];
int need[MAX_PROCESS][MAX_REQUEST];
// n - no of process, m - no of resources
int n, m;

void safety();
void resource_req(int[]);
void display();

int main()
{
    printf("Enter the no of processes:\n");
    scanf("%d", &n);
    printf("Enter the no of resources:\n");
    scanf("%d", &m);
    printf("Enter available resources (a1 a2 a3...):\n");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &available[i]);
    }
    for (int i = 0; i < n; i++)
    {
        printf("Enter current allocation for resource p%d (c1 c2 c3...):\n", i);
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
        printf("Enter maximum allocation for resource p%d (m1 m2 m3...):\n", i);
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
            if (need[i][j] < 0)
            {
                printf("Invalid inputs");
                return 1;
            }
        }
    }
    display();
    return 0;
}

void display()
{
    printf("Process\tAllocated\tMax\tNeed\n");
    for (int i = 0; i < n; i++)
    {
        printf("p%d\t", i);
        for (int j = 0; j < m; j++)
        {
            printf("%d ", alloc[i][j]);
        }
        printf("\t\t");
        for (int j = 0; j < m; j++)
        {
            printf("%d ", max[i][j]);
        }
        printf("\t");
        for (int j = 0; j < m; j++)
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

/*
4
3
1 2 3
1 2 3
2 3 4
1 2 3
2 3 4
1 2 3
2 3 4
1 2 3
2 3 4
*/