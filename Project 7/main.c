/*
 * Matrix transpose test
 *
 * Prints an estimate of the working-set size and nano-seconds / iteration for
 * two different implementations:
 *
 *     - a slow implementation
 *     - a fast implementation
 *
 * Matrix transpose is easy. You start with:
 *
 *      1  2  3  4
 *      5  6  7  8
 *      9 10 11 12
 *     13 14 15 16
 *
 * and end up with
 *
 *      1  5  9 13
 *      2  6 10 14
 *      3  7 11 15
 *      4  8 12 16
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "common.h"

// run for 10 seconds
#define T 10

/*
 * initialize the arrays
 */
void init() {
    long t = 0;
    int i;
    for (i=0; i<N; i++) {
        int j;
        for (j=0; j<N; j++) {
            in[i][j] = t++;
            out[i][j] = -1L;
        }
    }
}

/*
 * check the output and report an error if it's not correct
 */
void check() {
    int i,j;
    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            long x = in[i][j];
            long y = out[j][i];
            if (x != y) {
                printf("in[%d][%d] = %ld but out[%d][%d] = %ld\n",i,j,x,j,i,y);
                exit(-1);
            }
        }
    }
}

/* slow implementation */
void slow() {
    int i,j;
    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            out[j][i] = in[i][j];
        }
    }
}

double report(char* what, long long count) {
    /* make sure we managed to do at least 10 iterations */
    if (count < 5) {
        /* less then 10 iterations, results are not valid */
        printf(
            "%10ld %d low iteration count(%lld)\n",
            (long)2*sizeof(in),
            N,
            (long long) count);
        return 0;
    } else {
        /* print results */
        double ns = ((double) T) * 1E9;
        double iter = (double) count * N * N;
        double nsPerIter = ns/iter;
        printf(
            "%s count=%lld bytes=%ld N=%d ns/iter=%f\n",
            what,
            count,
            (long)2*sizeof(in),
            N,
            nsPerIter);
        return nsPerIter;
    }
}

volatile int done = 0;

void handler() {
    done = 1;
}

/*
 * This is the main program
 */
int main(int argc, char* argv[]) {
    /* initialize the arrays */
    init();

    /* register the handler for the alarm signal */
    signal(SIGALRM,handler);

    /* schedule an alarm in T second */
    alarm(T);

    /* do the work in a tight loop until our time expires */
    long long count = 0;

    while (!done) {
        slow();
        count ++;
    }

    check();

    double slowNS = report("slow",count);

    count = 0;
    done = 0;

    init();
    signal(SIGALRM,handler);
    alarm(T);

    while (!done) {
        fast();
        count ++;
    }

    check();

    double fastNS = report("fast",count);

    printf("speedup=%f\n",slowNS/fastNS);
    return 0;
}
