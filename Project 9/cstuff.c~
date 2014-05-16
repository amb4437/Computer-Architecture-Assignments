#include "common.h"
#include "stdlib.h"
#include <time.h>

int *arrayOfInts;
int i = 0;

void prep(int ws) {
    
    if (arrayOfInts != 0) free(arrayOfInts);
    arrayOfInts = malloc(ws);

    for (int i = 0; i < ws/4; i++){
        arrayOfInts[i] = i;
    }

    //Shuffle the array
    int randomElement = 0;
    srand(time(NULL));
    for (int j = 0; j < ws/4; j++){
	int r = rand() % ws/4;
	randomElement = arrayOfInts[r];
	arrayOfInts[r] = arrayOfInts[j];
	arrayOfInts[j] = randomElement;
    }
}

int doit() {

    for (int counter = 0; counter < 1000; counter++){
      	i = arrayOfInts[i];
    }
    return 1000;
}

