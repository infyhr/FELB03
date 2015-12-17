#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Stack;
typedef struct Stack *Position;
struct Stack {
    char element[5]; // <-32768, +32768>
    Position Next;
};

int Recalculate(Position, char);
int Print(Position);
int ReadFromFile(Position, char fileName[32]);
Position Push(Position, char[5]);
int Pop(Position);

int main(int argc, char **argv) {
    struct Stack Stack;
    Stack.Next = NULL;

    // Try to load stuff from the file
    ReadFromFile(&Stack, "7.txt");

    // Print the stack -- This should be the result
    Print(Stack.Next);

    // And empty it.
    Pop(&Stack);

    return 0;
}

int ReadFromFile(Position P, char fileName[32]) {
    FILE *fp = fopen(fileName, "r");
    char buffer[5]; // <-32768, +32768>

    if(!fp) {
        printf("Otvaranje datoteke neuspjelo.\n");
        return -1;
    }

    while(1) {
        if(feof(fp)) break; // hit EOF

        fscanf(fp, "%s", buffer);
        if(!buffer) break; // Something either failed or we've hit EOF

        // Determine whether we're dealing with an actual number or an operator. Push to stack, or recalculate otherwise.
        (isdigit(buffer[0])) ? Push(P, buffer) : Recalculate(P, buffer[0]);
    }

    return 0;
}

int Recalculate(Position _Queue, char operation) {
    // Get the last two elements (which are actually the 1st and the 2nd one since we use a stack and add on top. Since we want to be efficient, we add to the beginning)
    Position lastElement    = _Queue->Next; // 1st = last
    Position PreviousOfLast = lastElement->Next; // 2nd = before the last one

    if(!lastElement || !PreviousOfLast) {
        printf("Dohvatanje zadnjeg i predzadnjeg elementa (odnosno prvog i drugog) neuspjelo. Provjeri je li postfix dobro napisan?");
        return -1;
    }

    // Convert char * -> int
    int a = atoi(lastElement->element);
    int b = atoi(PreviousOfLast->element);
    int intResult;
    char strResult[5];

    // Check out what sort of operation we've got
    switch(operation) {
        case '+':
            intResult = a + b;
        break;
        case '-':
            intResult = abs(a - b);
        break;
        case '*':
            intResult = a * b;
        break;
        default:
            return -1; // Invalid Operation.
    }

    // Convert back to string
    sprintf(strResult, "%d", intResult);

    // Pop off last two elements
    Pop(_Queue);Pop(_Queue);

    // Add?
    Push(_Queue, strResult);

    return 0;
}

int Print(Position P) {
    if(P == NULL) return -1;

    while(P != NULL) {
        printf("%s\n", P->element);
        P = P->Next;
    }

    return 0;
}

Position Push(Position P, char data[5]) {
    Position temp = (Position)malloc(sizeof(struct Stack));
    if(!temp) {
        printf("Alokacija memorije neuspjela.\n");
        return NULL;
    }

    // Chain here
    strncpy(temp->element, data, strlen(data)+1);
    temp->Next    = P->Next;
    P->Next       = temp;

    return P;
}

int Pop(Position P) {
    Position target;

    target = P->Next; // Grab the element which needs to be removed
    if(!target) return -1;

    P->Next = target->Next;
    free(target);

    return 0;
}