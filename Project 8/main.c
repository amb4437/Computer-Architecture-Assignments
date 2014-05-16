#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>

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

#define T 5

void report(uint64_t count, double cycleNS) {
    double nsPerThing = (T * 1e9) / count;
    double cyclesPerThing = nsPerThing / cycleNS;

    printf("    latency: %fns %fcycles\n",nsPerThing,cyclesPerThing);
    printf("    rate: %f/ns %f/cycle\n",1/nsPerThing,1/cyclesPerThing);
}

volatile int done = 0;

void handler() {
    done = 1;
}

/* run one test */
void one(char* what, long (*func)(), double cycleNS) {
    uint64_t count = 0;

    done = 0;
    printf("%s ...\n",what);
    signal(SIGALRM,handler);
    alarm(T);
    
    while (!done) {
        count += func();
    }

    report(count,cycleNS);
}


extern long indepAdds();
extern long depAdds();

extern long indepMuls();
extern long depMuls();

extern long indepDivs();
extern long depDivs();

extern long indepLoads();
extern long depLoads();

extern long depUncond();
extern long depTaken();
extern long depUntaken();

extern long indepAdd32Ops();
extern long indepAdd8Ops();

int main(int argc, char* argv[]) {
    double freqGHz = getFrequencyGHz();
    double cycleNS = 1 / freqGHz;

    printf("freq = %fGHz, cycle_time = %fns\n",freqGHz,cycleNS);

    one("independent add instructions",indepAdds, cycleNS);
    one("dependent add instructions",depAdds, cycleNS);

    one("independent loads instructions",indepLoads, cycleNS);
    one("dependent load instructions",depLoads, cycleNS);

    one("independent multiply instrutions",indepMuls, cycleNS);
    one("dependent multiply instrutions",depMuls, cycleNS);

    one("independent divide instructions",indepDivs, cycleNS);
    one("dependent divide instructions",depDivs, cycleNS);

    one("32 bit integer add operations",indepAdd32Ops, cycleNS);
    one("8 bit integer add operations",indepAdd8Ops, cycleNS);

    one("unconditional jumps",depUncond, cycleNS);
    one("unconditional taken",depTaken, cycleNS);
    one("unconditional untaken",depUntaken, cycleNS);

    return 0;
}
