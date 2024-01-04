#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **alloc_tab_v1(size_t m, size_t n)
{
    int **t = (int **)malloc(m * sizeof(int *));

    // TODO
    for (size_t i = 0; i < m; ++i)
    {
        t[i] = (int *)malloc(n * sizeof(int));
    }

    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
            t[i][j] = i + j;
    }

    return t;
}

void alloc_tab_v2(size_t m, size_t n, int ***t)
{
    *t = (int **)malloc(m * sizeof(int *));

    // TODO
    for (size_t i = 0; i < m; ++i)
    {
        (*t)[i] = (int *)malloc(n * sizeof(int));
    }

    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
            (*t)[i][j] = i + j;
    }

    // TODO
}

void print_tab(int **tab, size_t m, size_t n)
{
    printf("++++++++++++++++++++++++++++++++\n");
    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
            printf("%d ", tab[i][j]);
        printf("\n");
    }
    printf("++++++++++++++++++++++++++++++++\n");
}

void free_tab(int **tab, size_t m, size_t n)
{
    for (size_t i = 0; i < m; ++i)
        free(tab[i]);
    free(tab);
}

int main(int c, char **v)
{
    const size_t m = 2;
    const size_t n = 3;

    int **tab1;
    int **tab2;

    // TODO
    tab1 = alloc_tab_v1(m, n);
    alloc_tab_v2(m, n, &tab2);

    print_tab(tab1, m, n);
    print_tab(tab2, m, n);

    free_tab(tab1, m, n);
    free_tab(tab2, m, n);

    return 0;
}
