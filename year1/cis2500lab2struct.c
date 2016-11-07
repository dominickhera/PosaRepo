#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct uogPerson {
    int idNum;
    int grade;
    char * Name;
}typedef uogID;

int main(){
    uogID * person1;

    person1 = malloc(sizeof(uogID));

    person1->idNum = 123124;
    person1->grade = 67;

    person1->Name = malloc(sizeof(char)*30);
    strcpy(person1->Name, "Dominick");
    printf("%s's grade is %d. His ID number is %d\n", person1->Name, person1->grade, person1->idNum);

    free(person1->Name);
    free(person1);
    return 0;
}
