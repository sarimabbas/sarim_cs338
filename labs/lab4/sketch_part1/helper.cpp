#include "helper.hpp"
#include <Arduino.h>

psm* psmCreate(void) {
    psm* manager = (psm*) malloc(sizeof(psm));
    manager->head = NULL;
    manager->tail = NULL;
    manager->count = 0;
    return manager;
}

void psmAddToBack(psm* manager, process_t* process) {
    if (manager == NULL) {
        Serial.println("psmAddToBack: manager is NULL");
        return;
    }

    // if empty queue, make head point to new 
    if (manager->head == NULL) {
        manager->head = process;
    }

    // if non-empty queue, make pen-ultimate process point to new
    if (manager->tail != NULL) {
        manager->tail->next = process;
    }

    // set tail to new
    manager->tail = process;

    // increment count
    (manager->count)++;
}

void psmAddToFront(psm* manager, process_t* process) {
    if (manager == NULL) {
        Serial.println("psmAddToFront: manager is NULL");
        return;
    }

    // if empty queue, make tail point to new
    if (manager->tail == NULL) {
        manager->tail = process;
    }

    // manipulate head
    process->next = manager->head;
    manager->head = process;

    // increment count
    (manager->count)++;
}

// ! responsibility to free is with the caller
process_t* psmRemoveFromFront(psm* manager) {
    if (manager == NULL) {
        Serial.println("psmRemoveFromFront: manager is NULL");
        return NULL;
    }

    if (manager->head == NULL) {
        Serial.println("psmRemoveFromFront: nothing more to remove");
        return NULL;
    }

    // manipulate the head
    process_t* tmp = manager->head;
    manager->head = manager->head->next;

    // manipulate the tail
    if (manager->head == NULL) {
        manager->tail = NULL;
    }

    // decrement count
    (manager->count)--;

    // isolate removed process completely
    tmp->next = NULL;

    // return pointer to removed process
    return tmp;
}

void psmDestroy(psm** managerPtr) {
    psm* manager = *managerPtr;

    if (manager == NULL) {
        Serial.println("psmDestroy: manager is NULL");
        return;
    }

    Serial.println("psmDestroy: destroying manager");

    // free each process
    process_t* curr = manager->head;
    process_t* tmp = curr;
    while (curr != NULL) {
        tmp = curr;
        curr = curr->next;
        free(tmp);
    }

    // free the manager
    free(manager);
    *managerPtr = NULL;
}

process_t* psmFind(psm* manager, unsigned int sp) {
    if (manager == NULL) {
        Serial.println("psmFind: manager is NULL");
        return NULL;
    }

    process_t* curr = manager->head;
    while (curr != NULL) {
        if (curr->sp == sp) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

void psmDeleteByPtr(psm* manager, process_t* process) {
    if (manager == NULL) {
        Serial.println("psmDeletebyPtr: manager is NULL");
        return;
    }

    process_t* curr = manager->head;
    process_t* prev = curr;
    // curr moves through the list
    while (curr != NULL) {
        // if a match is found
        if (curr == process) {
            // special case if curr is the first element
            if (manager->head == curr) {
                manager->head = curr->next;
            }
            // special case if curr is the last element
            if (manager->tail == curr) {
                manager->tail = curr->next;
            }
            // regular case
            prev->next = curr->next;
            // make sure no loose ends
            curr->next = NULL;
            // free curr
            free(curr);
            // decrement count
            (manager->count)--;
        }
        // move prev ahead
        prev = curr;
        // if no match, continue for next iteration
        curr = curr->next;
    }
}

void SerialPrintWrapper(char* msg) {
    if (msg == NULL) {
        Serial.println("SerialPrintWrapper: msg was NULL");
        return;
    }
    Serial.print(msg);
    return;
}

void psmPrint(psm* manager) {
    if (manager == NULL) {
        Serial.println("psmPrint: manager is NULL");
        return;
    }

    Serial.print("Queue (");
    Serial.print(manager->count);
    Serial.print("): ");

    // iterate through queue
    process_t* curr = manager->head;
    while (curr != NULL) {
        // print formatted data
        Serial.print("[sp: ");
        Serial.print(curr->sp);
        Serial.print("], ");

        // advance curr
        curr = curr->next;
    }
    // new line
    Serial.println("");
}