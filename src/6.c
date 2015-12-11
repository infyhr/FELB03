#define _CRT_SECURE_NO_WARNINGS // VStudio stuff
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct LL;
typedef struct LL *Position;
struct LL {
    int element;
    Position Next;
};

Position Push(Position);
void Pop(Position);
void Print(Position, char *);

int main(int argc, char **argv) {
    struct LL Stack, Queue;
    static Position lastElement;
    int choice;

    Stack.Next = NULL;
    Queue.Next = NULL;
    lastElement = &Queue;

    while(1) {
        Print(Stack.Next, "stog");
        Print(Queue.Next, "red");
        printf("1. Dodaj u stog\n2. Dodaj u red\n3. Makni iz stoga\n4. Makni iz reda\n^C izlaz\n>");
        scanf("%d", &choice);
        if(!choice) break; // Exit

        switch(choice) {
        default:
            printf("Nepoznata naredba.\n");
            break;
        case 1: // Add to stack
            Push(&Stack);
            break;
        case 2:
            lastElement = Push(lastElement);
            break;
        case 3:
            Pop(&Stack);
            break;
        case 4:
            Pop(&Queue);
            break;
        }
    }
}

void Print(Position P, char *what) {
    if(P == NULL) {
        printf("%s je prazan.\n", what);
        return;
    }

    printf("%s: ", what);
    while(P != NULL) {
        printf("%d ", P->element);

        P = P->Next;
    }
    printf("\n");
}

Position Push(Position P) {
    int random;
    Position temp;

    // Generate a random number
    srand((unsigned)time(NULL));
    random = (rand() % (100 + 1 - 10)) + 10;

    temp = (Position)malloc(sizeof(struct LL));
    if(!temp) {
        printf("Alokacija memorije neuspjela.\n");
        return NULL;
    }

    temp->element = random;
    temp->Next = P->Next;
    P->Next = temp;

    return temp;
}

void Pop(Position P) {
    Position target;

    target = P->Next; // Grab the element which needs to be removed
    if(!target) return;

    P->Next = target->Next;
    free(target); // pop!
}