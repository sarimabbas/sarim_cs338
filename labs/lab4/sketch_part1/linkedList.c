#include linkedList.h

node* lCreate() {
    // request space
    node* head = malloc(sizeof(node);)
    if (head == NULL) {
        return NULL;
    }
    // initialize node
    head->next = NULL;
    head->val = 0;
    return head;
}

void lDestroy(node* head) {
    node* curr = head;
    node* tmp = head;
    while (curr != NULL) {
        tmp = curr;
        curr = curr->next;
        free(tmp);
    }
}

void lAddToFront(node* head, node* addMe) {
    node* tmp = head->next;
    head->next = addMe;
    addMe->next = tmp;
}

node* lFind(node* head, int val) {
    node* curr = head;
    while (curr != NULL) {
        if (curr->val == val) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

void lPrint(node* head) {
    curr = head;
    while (curr != NULL) {
        printf("%i, ", curr->val);
    }
}

void lPopFromFront(node* head) {
    node* front = head;
    head = head->next;
    front->next = NULL;
    return front;
}

bool lRemove(node* head, node* removeMe) {
    node* curr = head;
    node* prev = curr;
    while (curr != NULL) {
        if (curr->val == val) {
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    prev->next = curr->next;
    free(curr);
    return true;
}