#define _CRT_SECURE_NO_WARNINGS // VStudio stuff
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define FILENAME "students.txt"

typedef struct {
    char name[32];
    char lastName[32];
    short points;
}students;

int CountLines(char *);
short ReadData(students *, char *, int);
void PrintData(students *, int, short);

int main(int argc, char **argv) {
    int       lines = 0;
    short maxPoints = 0;
    students *student;

    // Count the lines
    lines = CountLines(FILENAME);
    if(lines <= 0) { // Could have switch()'d but oh well
        printf("File is either empty, or there was an error whilst reading it.\n");
        return -1;
    }

    // Allocate how much is needed
    student = (students *) malloc(sizeof(students) * (lines+1));
    if(!student) {
        printf("Failed to allocate the needed memory.\n");
        return -1;
    }

    // Read the students into the ptr
    maxPoints = ReadData(student, FILENAME, lines);
    if(maxPoints <= 0) {
        printf("Failed to read the data.\n");
    }
    
    // Print it all out.
    PrintData(student, lines, maxPoints);

    free(student); student = NULL;
    return 0;
}

void PrintData(students *student, int lines, short maxPoints) {
    int i;
    for(i = 0; i < lines; i++) {
        printf("Name: %s\nLast name: %s\nPoints: %d\nRelative points: %f\n\n", 
                student[i].name, student[i].lastName, student[i].points, (float)student[i].points/maxPoints * 100);
    }
}

short ReadData(students *student, char *fileName, int count) {
    int i;
    short maxPoints;
    FILE *fp = fopen(fileName, "r");
    if(fp == NULL) return -1;

    maxPoints = 0;
    for(i = 0; i < count; i++) {
        // Read line by line.
        fscanf(fp, "%32s %32s %3d", student[i].name, student[i].lastName, &student[i].points);

        // If there's anyone with more than what's currently the max, set it to that.
        if(student[i].points > maxPoints) maxPoints = student[i].points;
    }

    fclose(fp); fp = NULL;
    return maxPoints;
}

int CountLines(char *fileName) {
    char tempBuffer[70]; // temporary buffer
    int lines = 0;
    FILE *fp = fopen(fileName, "r"); // try to open
    if(fp == NULL) return -1;

    // Read line by line and count
    while(!feof(fp)) {
        // 69 -> 32 (name) + 32 (lastName) + 3 (points) + 2 \0x32 + 1
        if(fgets(tempBuffer, 70, fp) != NULL) lines++;
    }

    fclose(fp); fp = NULL;
    return lines;
}