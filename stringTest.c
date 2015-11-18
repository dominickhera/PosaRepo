#include <stdio.h>

int main(void) {
   char firstName[50] = "";
   char lastName[50]  = "";

   printf("Enter first name:\n");
   scanf("%s", firstName);  // Gets up to first space or ENTER

   printf("Enter last name:\n");
   scanf("%s", lastName);  // Gets up to first space or ENTER

   printf("\n");
   printf("Welcome %s %s!\n", firstName, lastName);
   printf("May I call you %s?\n", firstName);

   return 0;
}
