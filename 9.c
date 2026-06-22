#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int n, opcount = 0, top = -1;
static int stack[MAX];   // replaces malloc'd stack

int dfs(int mat[][MAX], int *vis, int *track, int source)
{
    vis[source] = 1;
    track[source] = 1;
    for (int i = 0; i < n; i++)
    {
        opcount++;
        if (mat[source][i] && track[i] && vis[i])
        {
            return 1;
        }
        if (mat[source][i] && !vis[i] && dfs(mat, vis, track, i))
        {
            return 1;
        }
    }
    stack[++top] = source;
    track[source] = 0;
    return 0;
}

int *checkConnectivity(int mat[][MAX])
{
    static int vis[MAX], track[MAX];   // static memory allocation

    for (int i = 0; i < n; i++)
    {
        vis[i] = 0;
        track[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            if (dfs(mat, vis, track, i))
            {
                return NULL;
            }
        }
    }
    return stack;
}

void tester()
{
    static int adjMat[MAX][MAX];   // static memory allocation

    printf("Enter number of vertices :\n");
    scanf("%d", &n);

    if (n > MAX)
    {
        printf("Number of vertices exceeds maximum limit of %d\n", MAX);
        return;
    }

    printf("Enter the adjacency matrix :\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &adjMat[i][j]);

    top = -1;
    int *result = checkConnectivity(adjMat);
    if (result == NULL)
    {
        printf("Cycle exists..Cannot perform topological sorting!!!");
        exit(0);
    }
    else
    {
        printf("Topological sorting order : \n");
        while (top != -1)
        {
            printf("%d ", result[top--]);
        }
    }
}

void plotter()
{
    static int adjMat[MAX][MAX];   // static memory allocation

    FILE *f1 = fopen("bfsMatTopSort.txt", "w");
    for (int k = 1; k <= 10; k++)
    {
        n = k;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adjMat[i][j] = 0;

        for (int i = 0; i < n - 1; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                adjMat[i][j] = 1;
            }
        }

        opcount = 0;
        top = -1;
        checkConnectivity(adjMat);
        fprintf(f1, "%d\t%d\n", n, opcount);
    }
    fclose(f1);
}

int main()
{
    int choice;
    printf("Enter\n1.Tester\n2.Plotter\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        tester();
        break;
    case 2:
        plotter();
        break;
    default:
        printf("Invalid choice");
    }
    return 0;
}
