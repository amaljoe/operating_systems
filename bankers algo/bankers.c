#include <stdio.h>
#define MAX_PROCESS 10
#define MAX_REQUEST 5

int available[MAX_REQUEST];
int max[MAX_PROCESS][MAX_REQUEST];
int alloc[MAX_PROCESS][MAX_REQUEST];
// n - no of process, m - no of resources
int n, m;

void safety();
void resource_req(int[]);

int main()
{
    n = 1;
    printf("Hello world");
    n = n + 1;
    printf("%d\n", n);
}