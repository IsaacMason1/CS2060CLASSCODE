#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct member {
    char name[50];
    int age;
    float zone;
    double heartRate;
} Member;

struct member *createDynamicArray(int initialSize) {
    return (struct member *)malloc(initialSize * sizeof(struct member));
}

void addMember(struct member **dynamicArray, int *size, int *capacity, struct member newMember) {
    if (*size >= *capacity) {
        *capacity = (*capacity == 0) ? 1 : (*capacity * 2);
        *dynamicArray = (struct member *)realloc(*dynamicArray, *capacity * sizeof(struct member));
    }

    (*dynamicArray)[*size] = newMember;
    (*size)++;
}

int compareByAge(const void *a, const void *b) {
    return ((struct member *)a)->age - ((struct member *)b)->age;
}

void printMembers(struct member *members, int size) {
    for (int i = 0; i < size; i++) {
        printf("member %d age= %d heartReate= %.2f\n", i + 1, members[i].age, members[i].heartRate);
    }
}

void findHeartRate(struct member *members, int size) {
    for (int i = 0; i < size; i++) {
        if (members[i].zone == 1) {
            members[i].heartRate = members[i].heartRate * 0.6;
        } else if (members[i].zone == 2) {
            members[i].heartRate = members[i].heartRate * 0.7;
        } else if (members[i].zone == 3) {
            members[i].heartRate = members[i].heartRate * 0.8;
        }
    }
}

char *formFilePath(const char *directory, const char *filename) {
    // Allocate memory for the file path
    char *filePath = (char *)malloc(strlen(directory) + strlen(filename) + 2); // +2 for the slash and null terminator

    // Check if memory allocation was successful
    if (filePath == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Create the file path by concatenating directory, slash, filename, and null terminator
    strcpy(filePath, directory);
    strcat(filePath, "/");
    strcat(filePath, filename);

    return filePath;
}

void writeToFile(const char *filePath, struct member *members, int size) {
    FILE *file = fopen(filePath, "w");

    // Check if the file was opened successfully
    if (file == NULL) {
        printf("Error opening the file for writing.\n");
        exit(EXIT_FAILURE);
    }

    // Write each member's information to the file
    for (int i = 0; i < size; i++) {
        fprintf(file, "%s %d %.2f %.2f\n", members[i].name, members[i].age, members[i].zone, members[i].heartRate);
    }

    // Close the file
    fclose(file);
}

void readAndDisplayFromFile(const char *filePath) {
    FILE *file = fopen(filePath, "r");

    // Check if the file was opened successfully
    if (file == NULL) {
        printf("Error opening the file for reading.\n");
        exit(EXIT_FAILURE);
    }

    // Read and display each member's information from the file
    struct member member;
    while (fscanf(file, "%s %d %f %lf", member.name, &member.age, &member.zone, &member.heartRate) == 4) {
        printf("Name: %s, Age: %d, Zone: %.2f, Heart Rate: %.2f\n", member.name, member.age, member.zone, member.heartRate);
    }

    // Close the file
    fclose(file);
}

int main() {
    Member m1;
    Member m2;
    Member m3;
    int capacity = 0;
    int size = 0;
    struct member *members = createDynamicArray(3);
    m1.age = 45;
    strcpy(m1.name, "Static");
    m1.zone = 3;
    m1.heartRate = 175;
    addMember(&members, &size, &capacity, m1);
    m2.age = 23;
    strcpy(m2.name, "Dynamic");
    m2.zone = 1;
    m2.heartRate = 197;
    addMember(&members, &size, &capacity, m2);
    m3.age = 19;
    strcpy(m3.name, "Queue");
    m3.zone = 2;
    m3.heartRate = 101;
    addMember(&members, &size, &capacity, m3);

    qsort(members, size, sizeof(struct member), compareByAge);

    printMembers(members, size);

    findHeartRate(members, size);

    char *filePath = formFilePath("c:/cs2060/files", "gym.txt");

    // Write information to the file
    writeToFile(filePath, members, size);

    // Read and display information from the file
    readAndDisplayFromFile(filePath);

    // Free the dynamically allocated memory
    free(filePath);
    free(members);

    return 0;
}