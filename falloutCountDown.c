#include<stdio.h>
#include<time.h>

int main(void) {

time_t rawtime;
struct tm * timeInfo;

time (&rawtime);
timeInfo = localtime (&rawtime);
//printf(" the time is %s", asctime(timeInfo));

char charAnswer;

printf("do you want to find out if fallout 4 is out yet?\n > ");
scanf("%c", &charAnswer);

while (charAnswer != 'y') {
scanf("%c", &charAnswer);
printf("how about now?\n");
}

printf("the date right now is %s\n",asctime(timeInfo));

return 0;

}
