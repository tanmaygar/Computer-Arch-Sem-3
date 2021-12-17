#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

void sorting (int array[15], int n)
{
    int c = 0;
    int d = 0;
    int t = 0;
    int comparisons = 0;
    for (c = 1 ; c <= n - 1; c++)
    {
        d = c;
        while (d > 0 && array[d] < array[d - 1]) 
        {
            comparisons++;
            t = array[d];
            array[d] = array[d - 1];
            array[d - 1] = t;
            d--;
        }
        if(d > 0)
        {
            comparisons++;
        }
    }
    //printing array
    printf("Sorted order: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    printf("No of comparisons taken is/are: %d\n", comparisons);
    return;
}

int main()
{
    srand(time(0)); 
    int n;
    int a, r;
    int array[15];
    printf("Input number of values to be sorted (0 < N < 10): ");
    scanf("%d", &n);
    printf("Input a value: ");
    scanf("%d", &a);
    printf("Input r value: ");
    scanf("%d", &r);

    
    //inserting elements in the array
        int temp = a;
        for (int i = 0; i < n; i++)
        {
            array[i] = temp;
            temp = temp*r;
        }

    //printing array
        printf("Ascending order: ");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", array[i]);
        }
        printf("\n");
    
    //sorting function
    sorting(array, n);

    //reversing the array
        int j = n;
        for (int i = 0; i < j; i++)
        {
            j--;
            temp = array[j];
            array[j] = array[i];
            array[i] = temp;
        }
        //printing array
        printf("Descending order: ");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", array[i]);
        }
        printf("\n");

    //sorting function
    sorting(array, n);

    //randomizing the array
        for (int i = 0; i < n; i++)
        {
            int j = rand() % n;
            temp = array[j];
            array[j] = array[i];
            array[i] = temp;
        }
        //printing array
        printf("Randomized order: ");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", array[i]);
        }
        printf("\n");

    //sorting function
    sorting(array, n);

    return 0;
}