#include <stdio.h>

int main(void) {
   int dogAgeYears = 0;

   printf("Enter your dog's age (in years): ");
   scanf("%d", &dogAgeYears);

   switch (dogAgeYears) {
      case 0:
         printf("That's 0..14 human years.\n");
         break;

      case 1:
         printf("That's 15 human years.\n");
         break;

      case 2:
         printf("That's 24 human years.\n");
         break;

      case 3:
         printf("That's 28 human years.\n");
         break;

      case 4:
         printf("That's 32 human years.\n");
         break;

      case 5:
         printf("That's 37 human years.\n");
         break;

      default:
         printf("Human years unknown.\n");
         break;
   }

   return 0;
}
