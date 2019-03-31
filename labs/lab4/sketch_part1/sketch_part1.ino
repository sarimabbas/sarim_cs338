#include "concurrency.h"
#include "helper.hpp"

#define MINUTE 60000000

void psmTestImplementation();

int ledOne = 6;
int ledTwo = 7;

void p1(void) {
    digitalWrite(ledOne, LOW);

    // wait a bit
    for(int i =0; i < 100000; i++)
        ;

    digitalWrite(ledOne, HIGH);
    return;
}

void p2(void) {
    /* process 2 here */
    // this should go out after ten seconds
    digitalWrite(ledTwo, HIGH);
    // for (int i = 0; i < 100000; i++)
    //     ;
    // digitalWrite(ledTwo, LOW);
    // return;
}

void setup() {
    // make sure ready queue is NULL;
    global_manager = NULL;
    current_process = NULL;

    // TODO: debugging. remove later
    Serial.begin(9600);
    
    // simultaneous LED test
    pinMode(ledOne, OUTPUT);
    pinMode(ledTwo, OUTPUT);

    // psmTestImplementation();
    // return;

    // create the two processes
    if (process_create(p1, 64) < 0) {
        return;
    }

    if (process_create(p2, 64) < 0) {
        return;
    }
}

void loop() {
    process_start();
    /* if you get here, then all processes are either finished or
       there is deadlock */
    while (1)
        ;
}


void psmTestImplementation() {
    if (process_create(p1, 64) < 0) {
        return;
    }

    if (process_create(p2, 64) < 0) {
        return;
    }

    psmPrint(global_manager);

    process_t* one = psmRemoveFromFront(global_manager);
    psmAddToBack(global_manager, one);
    psmPrint(global_manager);

    psmDestroy(&global_manager);
    psmPrint(global_manager);
}
