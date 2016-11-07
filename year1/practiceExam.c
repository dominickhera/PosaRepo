#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct phoneNumberStruct {
    int areaCode;
    int phoneNumber;
    char * descrip;
}phone;

phone* initPhone();
void printPhone(phone* p);

int main(int argc, char* argv[]){

    phone* phoneThing;

    printf("Dominick Hera\n");
    phoneThing = initPhone(argc, argv);
    printPhone(phoneThing);
    free(phoneThing->descrip);
    free(phoneThing);
    return 0;

}
phone * initPhone(int argc, char * argv[]){
    phone * phoneThing;

    phoneThing = malloc(sizeof(phone));
    phoneThing->descrip = malloc(sizeof(char)*25);

    phoneThing->areaCode = atoi(argv[1]);
    phoneThing->phoneNumber = atoi(argv[2]);
    strcpy(phoneThing->descrip, argv[3]);

    return phoneThing;

}
void printPhone(phone* phoneThing){
    printf("%s: (%d) %d\n", phoneThing->descrip, phoneThing->areaCode, phoneThing->phoneNumber);
}
