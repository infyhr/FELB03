#define _CRT_SECURE_NO_WARNINGS // VStudio stuff
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person *Position;
struct Person {
    char name[32];
    char lastName[32];
    int dob; // Date of birth
    Position Next; // Pointer to the next struct
};

int Insert(Position, int);
int Print(Position);
int Delete(Position);
int Exit(Position);
Position Find(Position, char *);
Position FindPrevious(Position, char *);

int main(int argc, char **argv) {
    struct Person head, *current;
    int choice;
    char temp[32];

    // Set the first element of the head structure to be NULL.
    head.Next = NULL;

    while(1) {
        printf("1. Add an element to the beginning of the list\n2. Add an element to the end of the list\n3. Print out the list.\n4. Find an element within the list\n5. Delete an element from the list\n0. Exit\n\n>");
        scanf("%d", &choice);

        switch(choice) {
            default:
                printf("Unknown command specified.\n");
            break;
            case 1: // Add an element to the beginning of the list.
                Insert(&head, 0);
            break;
            case 2: // Add an element to the end of the list.
                Insert(&head, 1);
            break;
            case 3: // Print out the list.
                Print(head.Next);
            break;
            case 4: // Find an element within the list.
                printf("Last name: ");
                scanf("%32s", temp);
                current = Find(head.Next, temp);
                if(!current) { printf("Did not find anything.\n");break; }
                printf("%s %s %d\n", current->name, current->lastName, current->dob);
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

    return 0;
}

int Exit(Position P) {
    Position temp;

    while(P != NULL) {
        temp = P;
        P    = P->Next;
        free(temp); // If we were to free P at last here, we wouldn't even be able to switch to the next element.
    }

    printf("Peace out homie.\n");

    return 0;
}

int Print(Position P) {
    int i = 0;

    while(P != NULL) { // Loop through every element...
        printf("%d. %s %s %d\n\n", i+1, P->name, P->lastName, P->dob);

        P = P->Next;
        i++;
    }

    return 0;
}

int Delete(Position P) {
    Position previous;
    char query[32];

    printf("Last name: ");
    scanf("%32s", query);
    previous = FindPrevious(P, query); // Find out the previous element of the user's query.

    if(!previous) {
        printf("Did not find anything to delete?\n");
        return -1;
    }

    P = previous->Next; // Now, the current element is previous' next element.
    previous->Next = P->Next; // Previous has to point to the current element's next element
    free(P); // We can now free of the current element since we needn't it.

    return 0;
}

Position FindPrevious(Position P, char *query) {
    // If there is no next element to work with, the previous one can't point to nothing.
    if(P->Next == NULL) P = NULL; // this works lol.
    while(P != NULL) {
        if(_strcmpi(query, P->Next->lastName) == 0) break; // Compare the next element's lastName with user's (yes, not the current, the next).
        P = P->Next;
    }

    return P;
}

Position Find(Position P, char *query) {
    while(P != NULL) {
        if(_strcmpi(query, P->lastName) == 0) break; // Compare the current element's lastName with the user's.
        P = P->Next;
    }
    return P;
}

int Insert(Position P, int mode) {
    Position temp;

    // Create a new element
    temp = (Position) malloc(sizeof(struct Person));
    if(!temp) {
        printf("Failed to allocate the needed memory.");
        return -1;
    }

    // Ask for the data
    printf("Insert: [name] [last name] [dob]\n");
    scanf("%32s %32s %d", temp->name, temp->lastName, &temp->dob);

    // Insert at the beginning
    if(mode == 0) {
        temp->Next = P->Next; // The new element has to point to _something_, let it point at what the element before pointed.
        P->Next = temp; // And now the element before points to this new element we've just created.
        return 0;
    }
    
    // We loop until we're at the end
    while(P->Next != NULL) P = P->Next;

    // Now we're at the end -- insert.
    temp->Next = NULL;
    P->Next = temp;

    return 0;
}