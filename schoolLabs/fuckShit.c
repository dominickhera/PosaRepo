#include<stdio.h>

int main(void) {
   const int NUM_VALS = 4;
   int courseGrades[NUM_VALS];
   int i = 0;

   courseGrades[0] = 7;
   courseGrades[1] = 9;
   courseGrades[2] = 11;
   courseGrades[3] = 10;
for (i = 0; i != NUM_VALS; i++){
   printf("%d ", courseGrades[i]);
}
printf("\n");
	for (i = 3, i != NUM_VALS;){
	i = NUM_VALS - 1;
	printf("%d ", courseGrades[i]);

}
return 0;
}
