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
    // int j;
    // int child_status;
    int addInt;
    int count;
    char **args; 
    pid_t child_pid;

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
                    // printf("lol\n");
                    exit(1);
                }
                else
                { 
                    
                    child_pid = fork();
                    if(child_pid == 0) 
                    {
                        execvp(args[i], args);
                        printf("error\n");
                        exit(0);
                    }
                    else
                    {
                        wait(NULL);
                        // do {
                           // tpid = wait(&child_status);
                           // printf("cpid is %d, tpid is %d\n", tpid, child_pid);
                           // if(tpid != child_pid) process_terminated(tpid);
                         // } while(tpid != child_pid);
                        // printf("hi");
                        // return child_status;
                    }

        //             // fork();
                    // execvp(args[i], args);
                    // break;
                }
            }
            else if(count == 2)
            {

                // printf("args[%s]\n", args[i]);
                if(strpbrk(args[i], "-") == 0)
                {
                    child_pid = fork();
                    if(child_pid == 0) 
                    {
                        execvp(args[i], &args[i]);
                        // printf("error\n");
                        exit(0);
                    }
                    else
                    {
                        wait(NULL);
                        // do {
                           // tpid = wait(&child_status);
                           // printf("cpid is %d, tpid is %d\n", tpid, child_pid);
                           // if(tpid != child_pid) process_terminated(tpid);
                         // } while(tpid != child_pid);
                        // printf("hi");
                        // return child_status;
                    }
                }
                else if(strpbrk(args[i], "&") == 0)
                {
                    char * executeString = malloc(sizeof(char) * 500);
                    for(int i = 0; i < count - 1; i++)
                    {
                        strcat(executeString, args[i]);  
                    }
                    printf("string is %s\n", executeString);
                    child_pid = fork();
                    if(child_pid == 0) 
                    {
                        execvp(args[i], &executeString);
                        // printf("error\n");
                        exit(0);
                    }
                    else
                    {
                        wait(NULL);
                        // do {
                           // tpid = wait(&child_status);
                           // printf("cpid is %d, tpid is %d\n", tpid, child_pid);
                           // if(tpid != child_pid) process_terminated(tpid);
                         // } while(tpid != child_pid);
                        // printf("hi");
                        // return child_status;
                    }
        //             execvp(args[0], &args[i]);
                }
        //         break;
            }
        //     else
        //     {
        //         // if(strpbrk(args[i], ">") == 0)
        //         // {
        //         //  freopen   
        //         // }
        //         if(strcmp(args[i], "add") == 0)
        //         {
        //             addInt = 0;
        //             for(j = 1; j < count;j++)
        //             {
        //                 addInt += atoi(args[j]);
        //                 if(j == count - 1)
        //                 {
        //                     printf("%s = ", args[j]);
        //                 }
        //                 else
        //                 {
        //                     printf("%s + ", args[j]);
        //                 }
        //             }
        //             printf("%d\n", addInt);
        //             break;

        //         }
        //         else if(strcmp(args[i], "args") == 0)
        //         {
        //             printf("argc = %d, args = ", count - 1);
        //             for(j = 1; j < count; j++)
        //             {
        //                 if(j == count - 1)
        //                 {
        //                     printf("%s\n", args[j]);
        //                 }
        //                 else
        //                 {
        //                     printf("%s, ", args[j]);
        //                 }
        //             }
        //         }
        //         else if(strcmp(args[i], "&") == 0)
        //         {
        //             printf("this should use the background computation but it is not implemented\n");
        //         }
        //         else
        //         {
                    // execvp(args[0], &args[i]);
        //         }
            // }
        }
    }
}
