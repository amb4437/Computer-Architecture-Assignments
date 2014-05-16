#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>

#include "common.h"

double getFrequencyGHz() {
    /* use lscpu to get the CPU frequency in MHz. Only works on Linux */
    /* writes the frequency in freq.txt */
    int rc = system("lscpu | grep MHz | sed -e s'/.*:  *//' > freq.txt");
    if (rc != 0) {
        perror("system");
        exit(-1);
    }

    /* open freq.txt */
    FILE *file = fopen("freq.txt","r");
    if (file == 0) {
        perror("open freq.txt");
        exit(-1);
    }

    /* read frequency from freq.txt */
    double freqMHz = 0;
    rc = fscanf(file,"%lf",&freqMHz);
    if (rc != 1) {
        perror("scanning file");
        exit(-1);
    }
    fclose(file);

    return freqMHz / 1000.0;
}

#define MAX 1*1024*1024*1024
#define T 2

volatile int done = 0;

void handler() {
    done = 1;
}

int main(int argc, char* argv[]) {
    double freqGHz = getFrequencyGHz();

    printf("freq = %fGHz\n",freqGHz);

    int ws = 100;
    while (ws < MAX) {
        double count = 0;
        prep(ws);
        doit();

        done = 0;
        signal(SIGALRM,handler);
        alarm(T);
    
        while (!done) {
            count += doit();
        }

        double nsPerLoad = (((double) T) * 1e9) / count;
        printf("ws = %d, Nanoseconds per load = %f\n",ws, nsPerLoad);
        ws = 2 * ws;
                
    }

    return 0;
}
