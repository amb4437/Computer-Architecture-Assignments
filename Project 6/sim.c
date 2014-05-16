#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "sim.h"

#define STACK_SIZE 1024
#define MEM_SIZE 1024

/* The processor state */
struct StateStruct {
    
    /* TODO -- define the machine state, stack, memory, program, PC, ... */
    
    
    int SP; /*Stack pointer*/
    int PC; /*Program counter*/
    
    char* program_mem; /*The program, in the form of characters*/
    int* data_mem; /*General purpose memory*/
    int32_t* stack; /*The stack*/
    
};

State* init() {
    /* allocate memory */
    State* s = malloc(sizeof(State));
    
    /* zero the memory */
    bzero(s, sizeof(State));
    
    /* TODO -- initialize the state as needed */
    s->stack = malloc(STACK_SIZE*4);
    s->data_mem = malloc(MEM_SIZE*4);
    s->SP = 0;
    s->PC = 0;
    
    
    return s;
}

void prog(State* s, char* p) {
    
    s-> program_mem = p;
    s-> PC = 0;
}

void push(State* s, int v) {
    s->SP++;
    s->stack[s->SP] = v;
    /* TODO -- push a value on the stack */
}

int pop(State*s){
    
    int top;
    top = s->stack[s->SP];
    s->SP--;
    return top;
}

void stacksimulator(State* s) {
    
    int a;
    int t;
    int v;
    
    
    /*Our decoder*/
    for (s->PC = 0; s->PC < 25; s->PC++){
        
        /* . instruction*/
        if (s->program_mem[s->PC] == 46){
            int end = pop(s);
            if (end == -1){
                break;
            }
            else{
                s->PC = end-1;
            }
            
        }
        
        /* - instruction*/
        else if (s->program_mem[s->PC] == 45){
            
            a = pop(s);
            v = pop(s);
            push(s, a-v);
        }
        
        /* + instruction*/
        else if (s->program_mem[s->PC] == 43){
            
            
            a = pop(s);
            v = pop(s);
            push(s, a+v);
        }
        
        /* * instruction*/
        else if (s->program_mem[s->PC] == 42){
            a = pop(s);
            v = pop(s);
            push(s, a*v);
        }
        
        /* / instruction*/
        else if (s->program_mem[s->PC] == 47){
            a = pop(s);
            v = pop(s);
            push(s, a/v);
        }
        
        /* % instruction*/
        else if (s->program_mem[s->PC] == 37){
            a = pop(s);
            v = pop(s);
            push(s, a%v);
        }
        
        /* < instruction*/
        else if (s->program_mem[s->PC] == 60){
            t = pop(s);
            v = pop(s);
            if (v < 0){
                s->PC = t-1;
            }
        }
        
        /* > instruction*/
        else if (s->program_mem[s->PC] == 62){
            t = pop(s);
            v = pop(s);
            if (v > 0){
                s->PC = t-1;
            }
        }
        
        /* = instruction*/
        else if (s->program_mem[s->PC] == 61){
            t = pop(s);
            v = pop(s);
            if (v == 0){
                s->PC = t-1;
            }
        }
        
        /* e instruction*/
        else if (s->program_mem[s->PC] == 101){
            t= pop(s);
            if (s->SP == 0){
                s->PC = t-1;
            }
        }
        
        /* c instruction*/
        else if (s->program_mem[s->PC] == 99){
            t = pop(s);
            v = s->PC+1;
            push(s, v);
            s->PC=t-1;
        }
        
        /* d instruction*/
        else if (s->program_mem[s->PC] == 100){
            t= pop(s);
            push (s,t);
            push (s,t);
        }
        
        /* l instruction*/
        else if (s->program_mem[s->PC] == 108){
            a = pop(s);
            t = s->data_mem[a];
            push(s, t);
        }
        
        /* p instruction*/
        else if (s->program_mem[s->PC] == 112){
            pop(s);
        }
        
        /* s instruction*/
        else if (s->program_mem[s->PC] == 115){
            a= pop(s);
            v= pop(s);
            s->data_mem[a] = v;
        }
        
        /* x instruction*/
        else if (s->program_mem[s->PC] == 120){
            a= pop(s);
            v= pop(s);
            push(s, a);
            push(s, v);
        }
        
        /* 0-9 instruction*/
        else if (s->program_mem[s->PC] > 47 && s->program_mem[s->PC] < 58){
            
            int current = s->program_mem[s->PC];
            int intstring = current-48;
            
            if (47 < s->program_mem[s->PC+1] && s->program_mem[s->PC+1] < 58)
            {
                
                int addnum = intstring * 10;
                int newnum = s->program_mem[s->PC+1] - 48;
                intstring = addnum + newnum;
                s->PC++;
            }
            push(s, intstring);
        }
        else
            break;
        
    }
    
    
    
    
}


void run(State* s) {
    /* TODO -- get the program from the state */
    char* prog = s->program_mem;
    printf("running: %s\n",prog);
    printf("initial stack:\n");
    stack(s);
    fflush(stdout);
    
    /* TODO -- simulate the execution */
    stacksimulator(s);
    
    printf("final stack:\n");
    stack(s);
    fflush(stdout);
    
}

void stack(State* s) {
    
    for (int i = s->SP; i > 0; i--){
        printf("%d \n",s->stack[i]);
    }
    /* TODO -- show the stack as decimal ints (one per lines) */
}
