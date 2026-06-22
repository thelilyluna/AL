/* program to implement quick sort*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1024

int count;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *arr, int beg, int end)
{
    int pivot = arr[beg];
    int i = beg, j = end + 1;
    do
    {
        do
        {
            count++;
            i++;
        } while (arr[i] < pivot);
        do
        {
            count++;
            j--;
        } while (arr[j] > pivot);
        swap(&arr[i], &arr[j]);
    } while (i < j);
    swap(&arr[i], &arr[j]);
    swap(&arr[beg], &arr[j]);
    return j;
}

void quicksort(int *arr, int beg, int end)
{
    if (beg < end)
    {
        int split = partition(arr, beg, end);
        quicksort(arr, beg, split - 1);
        quicksort(arr, split + 1, end);
    }
}

void tester()
{
    static int arr[MAX];   // static memory allocation
    int n;

    printf("ENTER THE NUMBER OF ELEMENTS\n");
    scanf("%d", &n);

    if (n > MAX)
    {
        printf("Array size exceeds maximum limit of %d\n", MAX);
        return;
    }

    printf("ENTER THE ELEMENTS OF THE ARRAY\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("THE ELEMENTS OF THE ARRAY BEFORE SORTING\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    quicksort(arr, 0, n - 1);

    printf("THE ELEMENTS OF THE ARRAY AFTER SORTING\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n\n");
}

void plotter()
{
    static int arr[MAX];   // static memory allocation
    int n;
    srand(time(NULL));
    FILE *f1, *f2, *f3;
    f1 = fopen("Quickbest.txt", "w");
    f2 = fopen("Quickavg.txt", "w");
    f3 = fopen("Quickworst.txt", "w");

    n = 4;
    while (n <= MAX)
    {
        // best case: all elements equal
        for (int i = 0; i < n; i++)
            arr[i] = 5;
        count = 0;
        quicksort(arr, 0, n - 1);
        fprintf(f1, "%d\t%d\n", n, count);

        // average case: random elements
        for (int i = 0; i < n; i++)
            arr[i] = rand() % n;
        count = 0;
        quicksort(arr, 0, n - 1);
        fprintf(f2, "%d\t%d\n", n, count);

        // worst case: already sorted
        for (int i = 0; i < n; i++)
            arr[i] = i + 1;
        count = 0;
        quicksort(arr, 0, n - 1);
        fprintf(f3, "%d\t%d\n", n, count);

        n = n * 2;
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);
}

int main()
{
    int ch;
    printf("Enter your choice: \n\n1.Tester\n2.Plotter\n\n");
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
        printf("Invalid choice!!!\n\n");
    }
    return 0;
}
