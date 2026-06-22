#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1000

int count = 0;

bool stringmatching(char *text, char *pattern, int n, int m)
{
    count = 0;
    for (int i = 0; i <= (n - m); i++)
    {
        int j = 0;
        while (j < m)
        {
            count++;
            if (pattern[j] != text[i + j])
                break;
            j++;
        }
        if (j == m)
            return true;
    }
    return false;
}

void plotter()
{
    static char text[MAX];
    static char pattern[MAX];

    FILE *f1 = fopen("strbest.txt", "w");
    FILE *f2 = fopen("stravg.txt", "w");
    FILE *f3 = fopen("strworst.txt", "w");

    srand(time(NULL));

    int n = MAX;
    for (int i = 0; i < n; i++)
        text[i] = 'a';

    int m = 10;
    while (m <= MAX)
    {
        // best case: pattern is all 'a's -> matches immediately at i = 0
        for (int i = 0; i < m; i++)
            pattern[i] = 'a';
        stringmatching(text, pattern, n, m);
        fprintf(f1, "%d\t%d\n", m, count);

        // average case: random mix of 'a'/'b'/'c' -> mismatches found early on average
        for (int i = 0; i < m; i++)
            pattern[i] = 97 + rand() % 3;
        stringmatching(text, pattern, n, m);
        fprintf(f2, "%d\t%d\n", m, count);

        // worst case: pattern matches everywhere except the last char -> max comparisons per shift
        for (int i = 0; i < m; i++)
            pattern[i] = 'a';
        pattern[m - 1] = 'b';
        stringmatching(text, pattern, n, m);
        fprintf(f3, "%d\t%d\n", m, count);

        m = (m < 100) ? m + 10 : m + 100; //can also just be m+=10. the current version makes plotting faster
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);
}

void tester()
{
    static char text[MAX], pattern[MAX];

    printf("Enter the pattern: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0';

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    int m = strlen(pattern);
    int n = strlen(text);

    bool found = stringmatching(text, pattern, n, m);
    if (found)
        printf("\nPattern '%s' matched with Text '%s'\n", pattern, text);
    else
        printf("\nPattern '%s' doesn't match with the Text '%s'\n", pattern, text);
}

int main()
{
    int ch;
    printf("Enter \n1.Tester\n2.Plotter\n");
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
        printf("Invalid choice.\n");
    }
    return 0;
}
