#include <stdio.h>
#include <stdlib.h>
#define FIRST "prvi_polinom.txt"
#define SECOND "drugi_polinom.txt"

struct Polynomial;

typedef struct Polynomial *Position;

struct Polynomial {
    int coeff;
    int exp;
    Position Next;
};

void Read(Position P, char []);
void Print(Position P);
Position Add(Position P1, Position P2);
Position Multiply(Position P1, Position P2);

int main(int argc, char **argv) {
    struct Polynomial P1, P2;

    // Set up the things
    P1.Next = NULL;
    P2.Next = NULL;

    // Read the two polynomials from the file.
    Read(&P1, FIRST);
    Read(&P2, SECOND);

    // Print them out
    Print(P1.Next);
    Print(P2.Next);

    // Add up and print
//    Print(Add(P1.Next, P2.Next));
//    Print(Multiply(P1.Next, P2.Next));

    // Free and exit
    // Free here

    return 0;
}

void Print(Position P) {
    int i = 0;
    while(P != NULL) {
        if(i != 0) printf("+");
        printf("+%dx^%d", P->coeff, P->exp);

        P = P->Next;
        i++;
    }
}

void Read(Position P, char fileName[32]) {
    Position temp;
    FILE *fp = fopen(fileName, "r");

    if(!fp) {
        printf("Otvaranje datoteke neuspjelo.\n");
        return;
    }

    // We're good to go, read.
    //while(!feof(fp)) {
    while(1) {
        // Try to allocate the needed memory.
        temp = (Position) malloc(sizeof(struct Polynomial));
        if(!temp) {
            printf("Alokacija memorije neuspjela.\n");
            return;
        }

        // Read line by line -- (coeff) (exp) -- 2 3 == 2^3
        fscanf(fp, "%d %d", &temp->coeff, &temp->exp);

        // Temporary element is now the next element, say: P -> 4 -> NULL, temp = 4;
        //temp = P->Next;

        // Check whether the list is empty.
        if(P->Next == NULL) { // Just add to beginning of the list.
            temp->Next = P->Next;
            P->Next    = temp;
        }

        while(P->Next != NULL) { // If there is something beyond the element we're inspecting (not the last element).
            if(P->Next->exp > temp->exp) { // If the exponent of the next element is higher than the one we've just read from the file...
                // Then just insert it after that one.
                temp->Next = P->Next->Next;
                P->Next->Next = temp;
            }

            P = P->Next; // loop
        }

        // This means we're at the last element (P->Next points to NULL), so just add to the end.
        temp->Next = NULL;
        P->Next    = temp;
    }
    printf("reached.\n");
}
