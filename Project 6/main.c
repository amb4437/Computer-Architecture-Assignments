#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sim.h"

int main(int argc, char* argv[]) {
    alarm(3);

    State* s = init();

    /* process the arguments */
    int i = 1;
    while (i < argc) {
        char* arg = argv[i++];

        if (strcmp(arg,"-p") == 0) {
            prog(s,argv[i++]);
        } else {
            int32_t x = atoi(arg);
            push(s,x);
        }
    }
            
    push(s,-1); /* the program exits when it returns */
    run(s);

    return 0;
}
