#include<stdio.h>
#include<string.h>

int main() {
    int c;
    FILE *file;
    file = fopen("text.txt", "r");
    if (file) {
        while ((c = getc(file)) != EOF)
            putchar(c);
        fclose(file);
    }
}
