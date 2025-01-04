#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Set { //structure for a set
    int* elements;
    size_t size;
    size_t capacity;
};

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void iSet(struct Set* set) {
    set->elements = malloc(4 * sizeof(int));  // initial capacity set to 4
    set->size = 0;
    set->capacity = 4;
}

void freeSet(struct Set* set) { //free memory allocated for a set
    free(set->elements);
    set->size = 0;
    set->capacity = 0;
}

void push(struct Set* set, int val) {
    if (set->size == set->capacity) {
        set->elements = realloc(set->elements, set->capacity * 2 * sizeof(int));
        set->capacity *= 2;
    }
    set->elements[set->size++] = val;
}

int findIndex(struct Set* set, int val) {
    for (size_t i = 0; i < set->size; i++) {
        if (set->elements[i] == val) {
            return i;
        }
    }
    return -1; // Not found
}

//add an element to the set
void add(struct Set* set, int val) {
    if (findIndex(set, val) == -1) {
        push(set, val);
    }
}

//remove an element from the set
void removed(struct Set* set, int val) {
    int index = findIndex(set, val);
    if (index != -1) {
        set->elements[index] = set->elements[--set->size];
    }
}

void print(struct Set* set) {
    if (set->size == 0) {
        return;
    }

    //for ascending order
    int* sort_items = malloc(set->size * sizeof(int));
    for (size_t i = 0; i < set->size; i++) {
        sort_items[i] = set->elements[i];
    }

    for (size_t i = 0; i < set->size; i++) {
        for (size_t j = i + 1; j < set->size; j++) {
            if (sort_items[i] > sort_items[j]) {
                int temp = sort_items[i];
                sort_items[i] = sort_items[j];
                sort_items[j] = temp;
            }
        }
    }

    for (size_t i = 0; i < set->size; i++) {
        printf("%d", sort_items[i]);
        if (i != set->size - 1) {
            printf(" ");
        }
    }

    printf("\n");

    free(sort_items);
}

//all elements w/o duplicates
void unionSets(struct Set* set1, struct Set* set2) {
    struct Set result;
    iSet(&result);
    for (size_t i = 0; i < set1->size; i++) {
        add(&result, set1->elements[i]);
    }
    for (size_t i = 0; i < set2->size; i++) {
        add(&result, set2->elements[i]);
    }
    print(&result);
    freeSet(&result);
}

//common elements
void intersect(struct Set* set1, struct Set* set2) {
    struct Set result;
    iSet(&result);
    for (size_t i = 0; i < set1->size; i++) {
        if (findIndex(set2, set1->elements[i]) != -1) {
            add(&result, set1->elements[i]);
        }
    }
    print(&result);
    freeSet(&result);
}

int main() {
    struct Set setX, setY;
    iSet(&setX);
    iSet(&setY);

    char* cmd = NULL;
    size_t cmdSize = 0;

    while (getline(&cmd, &cmdSize, stdin) != -1) {
        char ops = cmd[0];
        char target = cmd[2];
        int value = atoi(&cmd[4]);

        //read commands and perform corresponding operations
        if (ops == 'a') {
            if (target == 'x') {
                add(&setX, value);
            } else if (target == 'y') {
                add(&setY, value);
            }
        } else if (ops == 'r') {
            if (target == 'x') {
                removed(&setX, value);
            } else if (target == 'y') {
                removed(&setY, value);
            }
        } else if (ops == 'p') {
            if (target == 'x') {
                print(&setX);
            } else if (target == 'y') {
                print(&setY);
            }
        } else if (ops == 'u') {
            unionSets(&setX, &setY);
        } else if (ops == 'i') {
            intersect(&setX, &setY);
        } else if (ops == 'q') {
            free(cmd);
            cmd = NULL;
            break;
        }
    }

    //free memory allocated for sets and command string
    freeSet(&setX);
    freeSet(&setY);
    free(cmd);

    return 0;
}
