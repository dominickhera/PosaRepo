#include<stdio.h>
#include<string.h>
#include<time.h>

int getFileName(char docName[50]) {
FILE *ifp;

printf("enter name of document to scramble: \n");
scanf("%s", docName);

ifp = fopen(docName, "r");

if (ifp == NULL) {
printf("Sorry, that file does not exist.\n");
return 0;
}
}

int main(void) {

FILE *ifp;
char docOpen[50];

getFileName(docOpen);

return 0;
}
