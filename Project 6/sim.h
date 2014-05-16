#ifndef _SIM_H_
#define _SIM_H_

/* Simulator API */

/* An opaque struct that represents the simulator state */
struct StateStruct;

/* Convenient typedef */
typedef struct StateStruct State;

/* create a new state */
State* init();

/* set the program */
void prog(State* s, char* prog);

/* push a value on the stack */
void push(State* state, int value);

/* run */
void run(State* state);

/* dump the stack */
void stack(State* state);

#endif
