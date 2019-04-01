#include "concurrency.h"
#include "helper.hpp"

void psmTestImplementation();

int ledOne = 6;
int ledTwo = 7;
unsigned long startMillis;  
long interval = 10000;     // interval at which to blink (milliseconds)

void p1(void) {
    pPrint(current_process);
    digitalWrite(ledOne, HIGH);

    // option 1
    startMillis = millis();
    while(true) {
        if (millis() - startMillis > interval) {
            digitalWrite(ledOne, LOW);
            break;
        }
    }

    // option 2
    // delay(interval);
    // digitalWrite(ledOne, LOW);


    pPrint(current_process);
    return;
}

void p2(void) {
    pPrint(current_process);
    digitalWrite(ledTwo, HIGH);

    // option 1
    startMillis = millis();
    while (true) {
        if (millis() - startMillis > interval) {
            digitalWrite(ledTwo, LOW);
            break;
        }
    }

    // option 2
    // delay(interval);
    // digitalWrite(ledOne, LOW);

    pPrint(current_process);
    return;
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

    if (process_create(p1, 64) < 0) {
        return;
    }
    if (process_create(p2, 64) < 0) {
        return;
    }

    // yields are disabled because current_process == NULL until process_start() is called
}

void loop() {
    process_start();
    /* if you get here, then all processes are either finished or
       there is deadlock */
    while (1)
        ;
}


void psmTestImplementation() {
    // create two processes
    psmPrint(global_manager);
    Serial.println("create two processes");
    if (process_create(p1, 64) < 0) { return; }
    psmPrint(global_manager);
    if (process_create(p2, 64) < 0) { return; }
    psmPrint(global_manager);

    // simulate the first selection
    Serial.println("simulate the first selection");
    Serial.println(current_process->sp);
    current_process = psmRemoveFromFront(global_manager);
    Serial.println(current_process->sp);
    psmAddToBack(global_manager, current_process);
    Serial.println(current_process->sp);
    Serial.flush();

    // simulate a termination
    Serial.println("simulate a termination");
    current_process = psmRemoveByPtr(global_manager, current_process);
    Serial.println(current_process->sp);
    free(current_process);
    psmPrint(global_manager);

    // choose again
    Serial.println("choose again");
    process_t* select_process = psmRemoveFromFront(global_manager);
    psmAddToBack(global_manager, select_process);
    current_process = select_process;
    psmPrint(global_manager);
    Serial.println(current_process->sp);

    // remove this one too
    Serial.println("remove this one too");
    current_process = psmRemoveByPtr(global_manager, current_process);
    Serial.println(current_process->sp);
    free(current_process);
    psmPrint(global_manager);

    // destroy the list
    Serial.println("destroy the list");
    psmDestroy(&global_manager);
    psmPrint(global_manager);
}
