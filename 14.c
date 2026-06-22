#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX 100

int heapCount = 0, graphCount = 0;

typedef struct
{
    int node;
    int cost;
    int parent;
} Pair;

Pair heap[MAX * MAX];
int heapSize;

void swap(Pair *a, Pair *b)
{
    Pair temp = *a;
    *a = *b;
    *b = temp;
}

void insert(Pair p)
{
    heap[heapSize] = p;
    int i = heapSize++;

    while (i > 0)
    {
        int par = (i - 1) / 2;

        if (heap[par].cost <= heap[i].cost)
            break;

        swap(&heap[par], &heap[i]);
        i = par;
    }
}

void heapify(int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    heapCount++;

    if (left < heapSize &&
        heap[left].cost < heap[smallest].cost)
        smallest = left;

    if (right < heapSize &&
        heap[right].cost < heap[smallest].cost)
        smallest = right;

    if (smallest != i)
    {
        swap(&heap[i], &heap[smallest]);
        heapify(smallest);
    }
}

Pair deleteMin()
{
    Pair min = heap[0];

    heap[0] = heap[heapSize - 1];
    heapSize--;

    if (heapSize > 0)
        heapify(0);

    return min;
}

int prims(int n, int adj[n][n])
{
    int vis[n];
    int mst[n][2];
    int k = 0;
    int cost = 0;

    for (int i = 0; i < n; i++)
        vis[i] = 0;

    heapSize = 0;

    insert((Pair){0, 0, -1});

    while (heapSize)
    {
        Pair curr = deleteMin();

        if (vis[curr.node])
            continue;

        vis[curr.node] = 1;

        mst[k][0] = curr.parent;
        mst[k][1] = curr.node;
        k++;

        cost += curr.cost;

        for (int i = 0; i < n; i++)
        {
            graphCount++;

            if (!vis[i] &&
                adj[curr.node][i] != INT_MAX &&
                curr.node != i)
            {
                insert((Pair)
                           {i,
                            adj[curr.node][i],
                            curr.node});
            }
        }
    }

    printf("\nMST Edges:\n");
    for (int i = 1; i < k; i++)
        printf("%d -- %d\n", mst[i][0], mst[i][1]);

    return cost;
}

void tester()
{
    int n;

    printf("Enter number of vertices : ");
    scanf("%d", &n);

    int adj[n][n];

    printf("Enter adjacency matrix (-1 for no edge):\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &adj[i][j]);

            if (adj[i][j] == -1)
                adj[i][j] = INT_MAX;
        }
    }

    heapCount = graphCount = 0;

    int cost = prims(n, adj);

    printf("\nMinimum Cost = %d\n", cost);
    printf("Heap Count = %d\n", heapCount);
    printf("Graph Count = %d\n", graphCount);
}

void plotter()
{
    FILE *fp = fopen("prims.txt", "w");

    srand(time(NULL));

    for (int n = 10; n <= 100; n += 10)
    {
        int adj[n][n];

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    adj[i][j] = 0;
                else
                {
                    int wt = rand() % 100 + 1;
                    adj[i][j] = wt;
                    adj[j][i] = wt;
                }
            }
        }

        heapCount = graphCount = 0;

        prims(n, adj);

        fprintf(fp, "%d\t%d\n",
                n,
                heapCount + graphCount);
    }

    fclose(fp);

    printf("\nData stored in prims.txt\n");
}

int main()
{
    int ch;

    printf("\n1. Tester\n2. Plotter\nChoice : ");
    scanf("%d", &ch);

    switch (ch)
    {
    case 1:
        tester();
        break;

    case 2:
        plotter();
        break;

    default:
        printf("Invalid Choice\n");
    }

    return 0;
}
