#include<stdio.h>
#include<stdlib.h>

int main(void) {
int cardNum[15];
int num = 5105105105105100;
int i;
int length;

length = strlen(num);

for (i = 0; i < length; i++) {
cardNum[i] = num % 10;
}

for (i = 0; i < length; i++) {
printf("%d", cardNum[i]);
}

return 0;
}
