#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

extern char **getln();

int main() 
{
    int i;
    int j;
    int addInt;
    int count;
    char **args; 

    while(1) 
    {
        args = getln();
        count = 0;
        for(i = 0; args[i] != NULL; i++)
        {
            count++;
        }

        for(i = 0; args[i] != NULL; i++)
        {
            if(count == 1)
            {
                if(strcmp(args[i], "exit") == 0)
                {
                    exit(1);
                }
                else
                { 
                    fork();
                    execvp(args[i], args);
                }
            }
            else if(count == 2)
            {
                if(strpbrk(args[i], "-") == 0)
                {
                    execvp(args[0], &args[i]);
                }
                else
                {
                    execvp(args[0], &args[i]);
                }
                break;
            }
            else
            {
                // if(strpbrk(args[i], ">") == 0)
                // {
                //  freopen   
                // }
                if(strcmp(args[i], "add") == 0)
                {
                    addInt = 0;
                    for(j = 1; j < count;j++)
                    {
                        addInt += atoi(args[j]);
                        if(j == count - 1)
                        {
                            printf("%s = ", args[j]);
                        }
                        else
                        {
                            printf("%s + ", args[j]);
                        }
                    }
                    printf("%d\n", addInt);
                    break;

                }
                else if(strcmp(args[i], "args") == 0)
                {
                    printf("argc = %d, args = ", count - 1);
                    for(j = 1; j < count; j++)
                    {
                        if(j == count - 1)
                        {
                            printf("%s\n", args[j]);
                        }
                        else
                        {
                            printf("%s, ", args[j]);
                        }
                    }
                }
                else if(strcmp(args[i], "&") == 0)
                {
                    printf("this should use the background computation but it is not implemented\n");
                }
                else
                {
                    execvp(args[0], &args[i]);
                }
            }
        }
    }
}
