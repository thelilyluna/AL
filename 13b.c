#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

int t[MAX][MAX], v[MAX], w[MAX], n, m, count = 0;

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void init()
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
            if (i == 0 || j == 0)
                t[i][j] = 0;
            else
                t[i][j] = -1;
    }
}

int Knap(int i, int j)
{
    if (t[i][j] != -1)
        return t[i][j];
    count++;
    if (w[i - 1] <= j)
        return t[i][j] = max(Knap(i - 1, j), v[i - 1] + Knap(i - 1, j - w[i - 1]));
    else
        return t[i][j] = Knap(i - 1, j);
}

void tester()
{
    printf("Enter number of items: ");
    scanf("%d", &n);
    printf("Sack capacity: ");
    scanf("%d", &m);
    for (int i = 0; i < n; i++)
    {
        printf("Enter weight and profit of item %d :", i + 1);
        scanf("%d%d", &w[i], &v[i]);
    }
    init();
    printf("Max profit is %d\n", Knap(n, m));
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
            printf("%d\t", t[i][j]);
        printf("\n");
    }
    printf("Picked items:\n");
    int k = m;
    for (int i = n; i > 0; i--)
    {
        if (t[i][k] != t[i - 1][k])
        {
            printf("%d\t", i);
            k -= w[i - 1];
        }
    }
    printf("\nOpcount: %d\n", count);
}

void plotter()
{
    FILE *f1 = fopen("KnapMemo.txt", "w");
    for (int iter = 5; iter <= 10; iter++)
    {
        n = iter;
        m = iter * 2;
        for (int i = 0; i < n; i++)
        {
            w[i] = rand() % 10 + 1;
            v[i] = rand() % 50 + 1;
        }
        init();
        count = 0;        // reset AFTER init, exactly as original
        Knap(n, m);
        fprintf(f1, "%d\t%d\n", n, count);
    }
    fclose(f1);
}

int main()
{
    int ch;
    printf("Enter your choice:\n1.Tester\n2.Plotter\n");
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
        printf("Invalid input\n");
    }
    return 0;
}
