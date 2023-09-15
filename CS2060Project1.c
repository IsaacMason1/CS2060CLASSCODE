#include <stdio.h>

#include <string.h>

 

// Define a struct to represent a "class"

struct Person {

    char name[50];

    int age;

};

 

// Define functions to act as "methods" on the "class"

void initializePerson(struct Person *person, const char *name, int age) {

    strcpy(person->name, name);

    person->age = age;

}

 

void printPerson(struct Person *person) {

    printf("Name: %s\n", person->name);

    printf("Age: %d\n", person->age);

}

 

int main() {

    // Create an instance of the "class"

    struct Person person1;

 

    // Call methods on the instance

    initializePerson(&person1, "John", 30);

    printPerson(&person1);

 

    return 0;

}