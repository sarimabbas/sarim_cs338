#include "concurrency.h"
#include "helper.hpp"

void psmTestImplementation();
void psmTest2();

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
    // TODO: debugging. remove later
    Serial.begin(9600);
    pinMode(ledOne, OUTPUT);
    pinMode(ledTwo, OUTPUT);

    global_manager = NULL;
    current_process = NULL;

    // psmTest2();
    // return;

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

void psmTest2() {
    unsigned int sp1, sp2, sp3;
    
    // test 1: push to back
    global_manager = psmCreate();
    psmPrint(global_manager);
    psmPushToBack(global_manager, 123);
    psmPushToBack(global_manager, 456);
    psmPushToBack(global_manager, 789);
    psmPrint(global_manager);
    psmDestroy(&global_manager);
    psmPrint(global_manager);

    // test 2: push to front
    global_manager = psmCreate();
    psmPushToFront(global_manager, 123);
    psmPushToFront(global_manager, 456);
    psmPushToFront(global_manager, 789);
    psmPrint(global_manager);
    psmDestroy(&global_manager);
    psmPrint(global_manager);

    // test 3: pop all
    global_manager = psmCreate();
    psmPushToFront(global_manager, 123);
    psmPushToFront(global_manager, 456);
    psmPushToFront(global_manager, 789);
    psmPrint(global_manager);
    psmPop(global_manager);
    psmPop(global_manager);
    psmPop(global_manager);
    psmPop(global_manager);
    psmPrint(global_manager);
    psmDestroy(&global_manager);
    psmPrint(global_manager);

    // test 4: process create (uses push to front)
    process_create(p1, 64);
    process_create(p2, 64);
    process_create(p2, 64);
    psmPrint(global_manager);
    sp1 = psmPop(global_manager);
    psmPrint(global_manager);
    sp2 = psmPop(global_manager);
    sp3 = psmPop(global_manager);
    psmPrint(global_manager);
    psmPop(global_manager);
    psmPrint(global_manager);
    psmPushToBack(global_manager, sp1);
    psmPushToBack(global_manager, sp2);
    psmPushToBack(global_manager, sp3);
    psmPrint(global_manager);
    psmDestroy(&global_manager);
    psmPrint(global_manager);
}


void psmTestImplementation() {
    // unsigned int sp;

    // // create two processes
    // psmPrint(global_manager);
    // Serial.println("create two processes");
    // if (process_create(p1, 64) < 0) { return; }
    // psmPrint(global_manager);
    // if (process_create(p2, 64) < 0) { return; }
    // psmPrint(global_manager);

    // // simulate the first selection
    // Serial.println("simulate the first selection");
    // pPrint(current_process);
    // sp = psmPop(global_manager);
    // Serial.println(sp);
    // psmPushToBack(global_manager, current_process);
    // Serial.println(current_process->sp);
    // Serial.flush();

    // // simulate a termination
    // Serial.println("simulate a termination");
    // current_process = psmRemoveByPtr(global_manager, current_process);
    // Serial.println(current_process->sp);
    // free(current_process);
    // psmPrint(global_manager);

    // // choose again
    // Serial.println("choose again");
    // process_t* select_process = psmRemoveFromFront(global_manager);
    // psmAddToBack(global_manager, select_process);
    // current_process = select_process;
    // psmPrint(global_manager);
    // Serial.println(current_process->sp);

    // // remove this one too
    // Serial.println("remove this one too");
    // current_process = psmRemoveByPtr(global_manager, current_process);
    // Serial.println(current_process->sp);
    // free(current_process);
    // psmPrint(global_manager);

    // // destroy the list
    // Serial.println("destroy the list");
    // psmDestroy(&global_manager);
    // psmPrint(global_manager);
}
