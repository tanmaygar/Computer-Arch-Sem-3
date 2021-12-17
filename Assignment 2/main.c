/* Tanmay Garg CS20BTECh11063 Computer Architecture Assignment 2
*
*   To compile the program use the following commands in terminal or powershell:
*
*   $ gcc -o main main.c
*   $ ./main
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define DUMMY_N 10

//Insertion Sort Function
void insertion_sort(int *array_num, int N)
{
    //variable to store the number of ith index of array
    int num;

    //tmp variable for using in while loop for index
    int tmp;

    //comparison counter
    int compare_counter = 0;
    for (int i = 1; i < N; i++)
    {
        num = array_num[i];
        tmp = i - 1;
        while (tmp >= 0 && num < array_num[tmp])
        {
            array_num[tmp + 1] = array_num[tmp];
            compare_counter++;
            tmp--;
        }
        if (tmp >= 0)
        {
            compare_counter++;
        }

        array_num[tmp + 1] = num;
    }

    //Printing array
    for (int i = 0; i < N; i++)
    {
        printf("%d ", array_num[i]);
    }
    printf(": %d\n", compare_counter);
}

//Function to put array into descending order
void desc_sort(int *array_num, int N)
{
    int tmp_arr[DUMMY_N];
    for (int i = 0; i < N; i++)
    {
        tmp_arr[N - 1 - i] = array_num[i];
    }
    for (int i = 0; i < N; i++)
    {
        array_num[i] = tmp_arr[i];
    }

    //Printing array
    for (int i = 0; i < N; i++)
    {
        printf("%d ", array_num[i]);
    }
    printf("\n");
}

//Function to put array into random order
void random_sort(int *array_num, int N)
{
    //variable to store the number of ith index of array for swapping
    int tmp;

    //variable for using in while loop for index by random number generator
    int index;

    for (int i = 0; i < N; i++)
    {
        index = rand() % N;
        tmp = array_num[index];
        array_num[index] = array_num[i];
        array_num[i] = tmp;
    }

    //Printing array
    for (int i = 0; i < N; i++)
    {
        printf("%d ", array_num[i]);
    }
    printf("\n");
}

//Function to create a GP of Numbers and then perform all 3 arrangment and sorting of all
void gp_number_func(int *array_num, int N)
{
    int a, r;
    printf("Input value for 'a' between 1 to 5: \n");
    scanf("%d", &a);
    printf("Input value for 'r' between 1 to 5: \n");
    scanf("%d", &r);

    array_num[0] = a;
    for (int i = 1; i < N; i++)
    {
        array_num[i] = array_num[i - 1] * r;
    }

    printf("Ascending Order : Comparisons\n");
    insertion_sort(array_num, N);

    printf("Descending Order :Comparisons\n");
    desc_sort(array_num, N);
    insertion_sort(array_num, N);

    printf("Random Order : Comparisons\n");
    random_sort(array_num, N);
    insertion_sort(array_num, N);
}

int main()
{
    srand(time(NULL));

    int N;
    printf("Input value of N from 1 to 10: \n");
    scanf("%d", &N);

    int arr[DUMMY_N];

    gp_number_func(arr, N);
}