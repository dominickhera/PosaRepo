#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void) {

srand(time(NULL));
int personCount = 0;
int nameArray[personCount];
int count = 0;
char charAnswer;
int randomNumber = 0;

printf("how many people are in your group?\n");
scanf("%d", &personCount);

struct nameArray *arrayNameSize;
arrayNameSize =(struct nameArray *) malloc(sizeof(struct nameArray)*personCount);

//printf("%d is the person Count\n", nameArray[]);

while (count  != personCount) {

//randomNumber = ((rand() % personCount));
count += 1;
printf("%d\n", count);
}
printf("all done\n");

return 0;
}
