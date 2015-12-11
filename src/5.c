#include <stdio.h>
#include <stdlib.h>

struct LL;
typedef struct LL *Position;
struct LL {
    int x;
    Position Next;
};

Position FindPreviousGreater(Position, int);
Position Insert(Position, int);
struct LL Union(Position, Position);
struct LL Intersection(Position, Position);
int ReadList(char fileName[32], Position);
int Print(Position);

int main(int argc, char **argv) {
    struct LL list1, list2;

    list1.Next = NULL;
    list2.Next = NULL;

    ReadList("5_1.txt", &list1);
    ReadList("5_2.txt", &list2);

    Print(list1.Next);
    Print(list2.Next);

    Print(Intersection(list1.Next, list2.Next).Next);
    Print(Union(list1.Next, list2.Next).Next);
}

struct LL Intersection(Position P1, Position P2) {
    struct LL Result;
    Result.Next = NULL;

    while(P1 != NULL && P2 != NULL) {
        if(P1->x > P2->x) P2 = P2->Next;
        else if(P2->x > P1->x) P1 = P1->Next;
        else {
            Insert(&Result, P1->x);
            P1 = P1->Next; P2 = P2->Next;
        }
    }

    return Result;
}

struct LL Union(Position P1, Position P2) {
    Position temp;
    struct LL Result;
    Result.Next = NULL;

    while(P1 != NULL && P2 != NULL) {
        if(P1->x > P2->x) {
            Insert(&Result, P2->x);
            P2 = P2->Next;
        }else if(P2->x > P1->x) {
            Insert(&Result, P1->x);
            P1 = P1->Next;
        }else {
            Insert(&Result, P1->x);
            P1 = P1->Next; P2 = P2->Next;
        }
    }

    temp = P2;
    if(P1 != NULL) temp = P1; // There's something left off P1, we have to add it.

    while(temp != NULL) {
        Insert(&Result, temp->x);
        temp = temp->Next;
    }

    return Result;
}

int Print(Position P) {
    while(P != NULL) {
        printf("%d ", P->x);

        P = P->Next;
    }

    printf("\n");
    return 0;
}

Position Insert(Position P, int element) {
    Position temp = (Position)malloc(sizeof(struct LL));
    if(!temp) {
        printf("Alokacija memorije neuspjela.\n");
        return NULL;
    }

    temp->x     = element;
    temp->Next  = P->Next;
    P->Next     = temp;

    return temp;
}

Position FindPreviousGreater(Position P, int element) {
    while(P->Next != NULL) {
        if(element <= P->Next->x) break;
        P = P->Next;
    }

    return P;
}

int ReadList(char fileName[32], Position P) {
    FILE *fp = fopen(fileName, "r");
    int temp;

    if(!fp) {
        printf("Učitavanje datoteke neuspjelo.\n");
        return -1;
    }

    while(1) {
        fscanf(fp, "%d", &temp);
        if(!temp) break; // Something fucked up lol.
        if(feof(fp)) break; // We hit end of file.

        // Insert it before the first greater element.
        Insert(FindPreviousGreater(P, temp), temp);
    }

    fclose(fp); fp = NULL;
    return 0;
}
