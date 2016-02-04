#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void initPhone();
void printPhone();

struct phoneNumberStruct {
    int areaCode;
    int phoneNumber;
    char * descrip;
}typedef phone;

int main(){
phone * phoneThing;

    printf("Dominick Hera\n");
    initPhone(phoneThing);
    printPhone(phoneThing);
    free(phoneThing);
    free(phoneThing->descrip);
    return 0;

}
void initPhone(int argc, char * argv){
    phone * phoneThing;

    phoneThing = malloc(sizeof(phone));
    phoneThing->descrip = malloc(sizeof(char)*25);

    phoneThing->areaCode = argv[1];;
    printf("%d", phoneThing->areaCode);
    phoneThing->phoneNumber = argv[2];
    printf("%d", phoneThing->phoneNumber);
    strcpy(phoneThing->descrip, &argv[3]);
    printf("%s", phoneThing->descrip);

}
void printPhone(){
    printf("%s: (%d) %d\n", phoneThing->descrip, phoneThing->areaCode, phoneThing->phoneNumber);
}
