#include <stdio.h>
#include <string.h>

// Function replaces spaces with hyphens
void StrSpaceToHyphen(char modString[]) {
   int i = 0;  // Loop index
   
   for (i = 0; i < strlen(modString); ++i) {
      if (modString[i] == ' ') {
         modString[i] = ' ';
      }
   }
   
   return;
}

int main(void) {
   const int INPUT_STR_SIZE = 50;  // Input string size
   char userStr[INPUT_STR_SIZE];   // Input string from user
   
   // Prompt user for input
   printf("Enter string with spaces: \n");
   fgets(userStr, INPUT_STR_SIZE, stdin);

   // Call function to modify user defined string
   StrSpaceToHyphen(userStr);
   
   printf("String with hyphens: %s\n", userStr);
   
   return 0;
}
