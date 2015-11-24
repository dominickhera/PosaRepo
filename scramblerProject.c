#include<stdio.h>
#include<string.h>
#include<time.h>

/*
int getFileName(char docName[]) {
FILE *ifp;

printf("enter name of document to scramble: \n");
scanf("%s", docName);

ifp = fopen(docName, "r");

if (ifp == NULL) {
printf("Sorry, that file does not exist.\n");
return 0;
}
}*/

int main(void) {

FILE *ifp;
char docName[50];

printf("enter name of document to scramble: \n");
scanf("%s", docName);

ifp = fopen(docName, "r");

if (ifp == NULL) {
printf("Sorry, that file does not exist.\n");
return 0;
}
//getFileName(docOpen);

return 0;
}
