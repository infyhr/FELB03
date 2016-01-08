#define _CRT_SECURE_NO_WARNINGS // VStudio stuff
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct TreeNode {
    char name[32];
    struct TreeNode *Sibling; // Next
    struct TreeNode *Child;
}TreeNode;

typedef struct HistoryStack {
    struct TreeNode *Element;
    struct HistoryStack *Next;
}HistoryStack;

TreeNode *Insert(TreeNode *, char [32]);
TreeNode *SameSiblingExists(TreeNode *, char [32]);
TreeNode *ChangeDirectory(TreeNode *, char [32], HistoryStack *, char [32]);
void Push(HistoryStack *Stack, TreeNode *element);
TreeNode *GoUp(TreeNode *, HistoryStack *, char [32]);
TreeNode *Pop(HistoryStack *);
void Print(TreeNode *);
void PrintStack(HistoryStack *);
void Exit(TreeNode *, HistoryStack *);

int main(int argc, char **argv) {
    char buffer[32];
    char command[32], arguments[32] = {0};
    char absolutePath[32];

    TreeNode root;
    TreeNode *currentDirectory = &root;

    strncpy(root.name, "C", 2);
    strncpy(absolutePath, "C:\\", 4);

    root.Sibling = NULL;
    root.Child   = NULL;

    HistoryStack stack;
    stack.Next = NULL;

    //Push(&stack, &root);

    while(1) {
        /*PrintStack(stack.Next);
        printf("\n==%s==\n", currentDirectory->name);*/
        printf("Dozvoljene naredbe:\n1. md\n2. cd <dir>\n3. cd ..\n4. dir\n5. exit\n\nTrenutni direktorij: %s\n\n>", absolutePath);

        fgets(buffer, 32, stdin);
        //printf("buffer: %s", buffer);
        sscanf(buffer, "%s %s", command, arguments);

        if(strlen(buffer) == 1) continue; // Just \n recieved.

        // New directory
        if(_strcmpi(command, "md") == 0) {
            if(strlen(arguments) == 0) continue;

            if(Insert(currentDirectory, arguments)) {
                printf("Direktorij %s kreiran!\n", arguments);
            }else {
                printf("Greska u kreiranju direktorija %s\n", arguments);
            }
        // Change directory
        }else if(_strcmpi(command, "cd") == 0) {
            if(strlen(arguments) == 0) continue;

            if(_strcmpi(arguments, "..") == 0) { currentDirectory = GoUp(currentDirectory, &stack, absolutePath); continue; }

            currentDirectory = ChangeDirectory(currentDirectory, arguments, &stack, absolutePath);
            // Directory listings
        }else if(_strcmpi(command, "dir") == 0) {
            Print(currentDirectory);
        // Exit
        }else if(_strcmpi(command, "exit") == 0) {
            break;
        }
    }

    return 0;
}

void Print(TreeNode *P) {
    int count;
    P = P->Child; // Print out dem kidz

    if(P == NULL) {
        printf("(prazno)\n");
        return;
    }

    count = 0;
    while(P != NULL) {
        printf("\t- %s\n", P->name);

        P = P->Sibling;
        count++;
    }

    printf("Ukupno %d direktorija.\n", count);
}

void Push(HistoryStack *Stack, TreeNode *element) {
    HistoryStack *temp = (HistoryStack *)malloc(sizeof(HistoryStack));
    if(!temp) {
        printf("Alokacija memorije neuspjela.\n");
        return;
    }

    temp->Element = element;
    temp->Next    = Stack->Next;

    Stack->Next   = temp;
}

TreeNode *Pop(HistoryStack *Stack) {
    HistoryStack *target;
    TreeNode *previousDirectory;

    if(Stack->Next == NULL) return NULL; // Empty stack!

    previousDirectory = Stack->Next->Element; // We need to return this last dir we entered so we can cd back to it later.
    target            = Stack->Next;
    Stack->Next       = target->Next;

    // Just pop the first element
    free(target);

    return previousDirectory;
}

// debug
void PrintStack(HistoryStack *Stack) {
    printf("\nU stack su:\n");
    while(Stack != NULL) {
        printf("\t%s\n", Stack->Element->name);

        Stack = Stack->Next;
    }
}

TreeNode *GoUp(TreeNode *currentDirectory, HistoryStack *stack, char absolutePath[32]) {
    int i = 0, length;
    TreeNode *lastDirectory = Pop(stack);

    if(lastDirectory == NULL) { // This means the stack is empty which means there are no previous directories which means we are at root!
        printf("Izlazak iz root direktorija je nemoguc.\n");
        return currentDirectory;
    }

    // Remove the last directory and save it. This is the one we cd into.
    printf("od stack lastDirectory je %s\n", lastDirectory->name);

    // Update the absolute path now by deleting the last dir
    length = strlen(absolutePath)-1;
    absolutePath[length] = 0; // This'll get rid of the last '\'

    // Now try to get rid of all the rest
    for(i = length; i >= 0; --i) {
        if(absolutePath[i] == '\\'){ break; }else { absolutePath[i] = 0; }
    }

    return lastDirectory; // We update this from main.
}

TreeNode *ChangeDirectory(TreeNode *currentDirectory, char newDir[32], HistoryStack *stack, char absolutePath[32]) {
    TreeNode *result;

    // Check if the desired dir exists by examining the current's children
    result = SameSiblingExists(currentDirectory->Child, newDir);

    if(!result) { // Does not exist.
        printf("Takav direktorij ne postoji.\n");

        return currentDirectory;
    }

    // It exists after all
    Push(stack, currentDirectory); // Push the CURRENT directory, not the new one, so we can return to it later.

    // Update the absolute path now with the new dir name
    strncat(absolutePath, result->name, strlen(result->name));

    // And append "\"
    strncat(absolutePath, "\\", 2);

    return result;
}

TreeNode *SameSiblingExists(TreeNode *P, char name[32]) {
    // Loop through all siblings.
    while(P != NULL) {
        if(_strcmpi(P->name, name) == 0) break;

        P = P->Sibling;
    }

    return P;
}

TreeNode *Insert(TreeNode *Parent, char name[32]) {
    TreeNode *temp = (TreeNode *) malloc(sizeof(TreeNode));
    if(!temp) {
        printf("Alokacija memorije neuspjela.\n");
        return NULL;
    }

    temp->Child   = NULL;
    temp->Sibling = NULL;
    strncpy(temp->name, name, strlen(name)+1);

    if(Parent->Child != NULL) { // We already have a child
        // Check if there exists already a sibling with the same name
        if(SameSiblingExists(Parent->Child, name)) {
            return NULL;
        }

        temp->Sibling = Parent->Child;
        Parent->Child = temp;
    }else {
        // We don't have a child, so let the newly allocated memory become the child
        Parent->Child = temp;
    }

    return temp;
}