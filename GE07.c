#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pet {
    int age;
    char name[50];
};

struct Pet *createDynamicArray(int initialSize) {
    return (struct Pet *)malloc(initialSize * sizeof(struct Pet));
}

int comparePets(const void *a, const void *b) {
    return strcmp(((struct Pet *)a)->name, ((struct Pet *)b)->name);
}

void addPet(struct Pet **dynamicArray, int *size, int *capacity, struct Pet newPet) {
    if (*size >= *capacity) {
        *capacity = (*capacity == 0) ? 1 : (*capacity * 2);
        *dynamicArray = (struct Pet *)realloc(*dynamicArray, *capacity * sizeof(struct Pet));
    }

    (*dynamicArray)[*size] = newPet;
    (*size)++;

    // Sort the pets in alphabetical order by name
    qsort(*dynamicArray, *size, sizeof(struct Pet), comparePets);
}

void removePet(struct Pet **dynamicArray, int *size, int index) {
    if (index < 0 || index >= *size) {
        printf("Index out of bounds.\n");
        return;
    }

    for (int i = index; i < *size - 1; i++) {
        (*dynamicArray)[i] = (*dynamicArray)[i + 1];
    }

    (*size)--;

    // Sort the pets in alphabetical order by name
    qsort(*dynamicArray, *size, sizeof(struct Pet), comparePets);
}

void printPets(struct Pet *pets, int size) {
    for (int i = 0; i < size; i++) {
        printf("Pet %d: ID=%d, Name=%s\n", i + 1, pets[i].age, pets[i].name);
    }
}

int main() {
    int capacity = 0;
    int size = 0;

    struct Pet *pets = createDynamicArray(1); // Start with an initial capacity of 1

    char addAnother;
    do {
        struct Pet newPet;
        printf("Enter name: ");
        scanf("%s", newPet.name);
        printf("Enter age: ");
        scanf("%d", &newPet.age);

        addPet(&pets, &size, &capacity, newPet);

        printf("Do you want to add another pet? Please enter (y)es or (n)o: ");
        scanf(" %c", &addAnother);
    } while (addAnother == 'y' || addAnother == 'Y');

    // Access and print the pets
    printf("The pets in alphabetical order:\n");
    printPets(pets, size);

    char deletePet;
    printf("Do you want to delete a pet from the list? Please enter (y)es or (n)o: ");
    scanf(" %c", &deletePet);

    while (deletePet == 'y' || deletePet == 'Y') {
        char deleteName[50];
        printf("Enter the pet's name to delete: ");
        scanf("%s", deleteName);

        int deleteIndex = -1;
        for (int i = 0; i < size; i++) {
            if (strcmp(pets[i].name, deleteName) == 0) {
                deleteIndex = i;
                break;
            }
        }

        if (deleteIndex != -1) {
            removePet(&pets, &size, deleteIndex);
            printf("%s has been removed from the list.\n", deleteName);
        } else {
            printf("%s is not found in the list of pets!\n", deleteName);
        }

        printf("The pets in alphabetical order:\n");
        printPets(pets, size);

        printf("Do you want to delete another pet from the list? Please enter (y)es or (n)o: ");
        scanf(" %c", &deletePet);
    }

    // Don't forget to free the dynamically allocated memory
    free(pets);

    return 0;
}

/* Im going to need to make sure to get my iteration two working completly because as of now it is still buggy
Next i will need to add all of the user storys and primarly focus on linked lists. 
Afterwords i want to make sure i have no warnings like in iteration two about my memory situation
i want to make sure this iteration is perfect because it is the last one i can turn in
function to comfrim property gets added or not
way to select properties from link list
function to return property
export property info into a file 
file name and path
write to the files
apending the file name to the folder path


*/
int main() {
    FILE *filePointer;

    // Opening a file in write mode ("w")
    filePointer = fopen("example.txt", "w");

    if (filePointer == NULL) {
        printf("Error opening the file.\n");
        return 1; // Return an error code
    }

    // Writing to the file
    fprintf(filePointer, "Hello, World!\n");

    // Closing the file
    fclose(filePointer);

    printf("File written and closed successfully.\n");

    return 0;
}