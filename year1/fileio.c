#include<stdio.h>
#include<string.h>

int main(){
    FILE * openFile;
    FILE * outputFile;
    char line[256];

    openFile = fopen("file.txt", "r");
    if(openFile == NULL){
        printf("couldn't open file\n");
        return 1;
    }


    outputFile = fopen("newFile.txt", "w");

    while(fgets(line, 256, openFile ) != NULL){
        int length = 0;

        length = strlen(line);
        line[length-1] = '\0';

        for (int i = 0; i < length; i++){
            if(line[i] == 'o') {
                line[i] = 'z';
            }
        }

        fprintf(outputFile, "%s\n", line);
	printf("%s\n", line);
    }

    fclose(openFile);
    fclose(outputFile);

    return 0;
}
