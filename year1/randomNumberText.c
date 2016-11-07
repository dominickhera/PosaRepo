#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

int main(void) {
srand (time(NULL));
int randomNumber = 0;

randomNumber = ((rand() % 6) + 1);
printf("%d", randomNumber);


}
