#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


#define SIZE 100000000
#define N 10

/* The array */
int arr[SIZE];

extern int count1(int *p, int size, int val);
extern int count2(int *p, int size, int val);

int main() {
    alarm(30);

    for (int i=0; i<SIZE; i++) {
        arr[i] = rand() % N;
    }

    printf("\nwithout cmov\n");
    printf("%5s %5s %12s\n","value","ratio","ns/iteration");
    for (int val = 0; val <= N; val ++) {
        clock_t us = clock();
        int c = count1(arr,SIZE,val);
        us = clock() - us;
        printf("%5u  %1.2f         %1.1f\n",val,((double)c) / SIZE,((double)us*1000)/SIZE);
    }

    printf("\nwith cmov\n");
    printf("%5s %5s %12s\n","value","ratio","ns/iteration");
    for (int val = 0; val <= N; val ++) {
        clock_t us = clock();
        int c = count2(arr,SIZE,val);
        us = clock() - us;
        printf("%5u  %1.2f         %1.1f\n",val,((double)c) / SIZE,((double)us*1000)/SIZE);
    }

    printf("\nwithout cmov\n");
    printf("%5s %5s %12s\n","value","ratio","ns/iteration");
    for (int val = 0; val <= N; val ++) {
        clock_t us = clock();
        int c = count1(arr,SIZE,val);
        us = clock() - us;
        printf("%5u  %1.2f         %1.1f\n",val,((double)c) / SIZE,((double)us*1000)/SIZE);
    }

    printf("\nwith cmov\n");
    printf("%5s %5s %12s\n","value","ratio","ns/iteration");
    for (int val = 0; val <= N; val ++) {
        clock_t us = clock();
        int c = count2(arr,SIZE,val);
        us = clock() - us;
        printf("%5u  %1.2f         %1.1f\n",val,((double)c) / SIZE,((double)us*1000)/SIZE);
    }

    return 0;
}

