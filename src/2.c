#define _CRT_SECURE_NO_WARNINGS // VStudio stuff
#ifdef __unix__
#define _strcmpi strcasecmp
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person; // Prototype of our structure.

typedef struct Person *Position;
struct Person {
    char name[32];
    char lastName[32];
    int dob;
    Position Next;
};

void Insert(Position);
void Delete(Position);
void Print(Position);
void Exit(Position);
Position FindPrevious(Position, char[]);
Position Find(Position, char []);
Position FindLast(Position);

int main(int argc, char **argv) {
    struct Person head, *current;
    int choice; // This could perhaps be a character, if so required.
    char query[32];

    head.Next = NULL;

    while(1) {
        printf("\n1. Dodaj element na pocetak liste\n2. Dodaj element na kraj liste\n3. Ispisi listu\n4. Pronadi element u listi\n5. Izbrisi element s liste\n0. Izlaz\n\n> ");
        scanf("%d", &choice);

        switch(choice) {
            default:
                printf("Nepoznata naredba.\n");
            break;
            case 1: // Add an element to the beginning of the list.
                Insert(&head);
            break;
            case 2: // Add an element to the end of the list.
                Insert(FindLast(&head));
            break;
            case 3: // Print out the list.
                Print(head.Next);
            break;
            case 4: // Find an element within the list.
                printf("Prezime trazene osobe: ");
                scanf("%32s", query); // Ask away

                current = Find(head.Next, query);
                if(!current) {
                    printf("Nista nije pronadeno.\n");
                    break;
                }
                printf("Pronadena osoba: %s %s %d\n", current->name, current->lastName, current->dob);
            break;
            case 5: // Delete an element
                Delete(&head);
            break;
            case 0: // Cleanup and exit.
                Exit(head.Next);
                return 0;
            break;
        }
    }
}

Position FindLast(Position P) {
    while(P->Next != NULL) P = P->Next;

    return P;
}

Position Find(Position P, char query[32]) {
    while(P != NULL) { // Loop through each element
        // Change _strcmpi to strcasecmp if running on *nix.
        if(_strcmpi(query, P->lastName) == 0) break; // If we've found what we're looking for stop then.

        P = P->Next;
    }

    return P;
}

Position FindPrevious(Position P, char query[32]) {
    if(P->Next == NULL) return NULL; // If the current element is pointing to nothing, then we can't work with it.
    while(P->Next != NULL) {
        if(_strcmpi(query, P->Next->lastName) == 0) break; // As soon as we've hit the next element's query, we stop asap.

        P = P->Next;
    }

    return P;
}

void Insert(Position P) {
    Position temp;

    // Allocate the needed memory for our new element.
    temp = (Position) malloc(sizeof(struct Person));
    if(!temp) {
        printf("Alokacija memorije neuspjela. Izlazim...\n");
        return;
    }

    // Ask and set away.
    printf("Upisite [ime] [prezime] [godinu rodenja]\n> ");
    scanf("%32s %32s %d", temp->name, temp->lastName, &temp->dob);

    // Set the pointers
    temp->Next = P->Next; // Our new element points to what P used to point at
    P->Next    = temp; // And now P points to our element
}

void Print(Position P) {
    unsigned int i;

    // Check whether the list is empty or not.
    if(P == NULL) { // This means we're only dealing with the head element which is always NULL.
        printf("Lista je prazna.\n");
        return;
    }

    // We've got something, loop and print out each element.
    i = 0;
    while(P != NULL) {
        printf("\n%d. %s %s %d\n", i+1, P->name, P->lastName, P->dob);

        P = P->Next;
        i++;
    }
}

void Delete(Position P) {
    Position previous;
    char query[32];

    printf("Prezime osobe koju zelite izbrisati:\n> ");
    scanf("%32s", query);

    // Find the previous element of the element we want to delete
    previous = FindPrevious(P, query);
    if(!previous) {
        printf("Osoba nije pronadena.\n");
        return;
    }

    // Good to go.
    P = previous->Next; // Current element is previous' next element.
    previous->Next = P->Next; // Now the previous element is pointing to current element's next element, skipping the current one.
    free(P); // We needn't this anymore.
}

void Exit(Position P) {
    Position temp;

    while(P != NULL) {
        temp = P;
        P    = P->Next;
        free(temp); // If we were to free P, we wouldn't even be able to loop through the next element, hence this.
    }

    printf("Pozdrav!\n");
}
