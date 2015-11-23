#include<stdio.h>
#include<string.h>

int main(void) {
char firstArray[5];
char secondArray[5];
int i = 0;

for (i = 0; i < 5; i++) {
printf("enter name\n");
scanf("%s", &firstArray[i]);
}

for (i = 0; i < 5; i++) {
printf("%s, ", firstArray);
}

return 0;
}
