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

void printMembers(struct member *members, int size){
    for (int i=0; i < size; i++) {
        printf("member %d age= %d heartReate= %d ", i+1, members[i].age, members[i].heartRate);
    }
}
void findHeartRate(struct member *members, int size){
    for(int i=0; i< size; i++){
        if(members[i].zone = 1){
            members[i].heartRate = members[i].heartRate*.6;
        }
        else if(members[i].zone = 2){
            members[i].heartRate = members[i].heartRate*.7;
        }
         else if(members[i].zone = 3){
            members[i].heartRate = members[i].heartRate*.8;
        }
    }
}


int main (){
    Member m1;
    Member m2;
    Member m3;
    int capacity = 0;
    int size = 0;
    struct Member *members = createDynamicArray(3);
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


}
 //Static 		Age: 		Zone: 3     	HearRate: 0
//Name: Dynamic 	Age: 23 		Zone: 1     	HearRate: 0
//Name: Queue 		Age: 19 		Zone: 2     	HearRate: 0
