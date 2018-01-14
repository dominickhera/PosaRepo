#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

extern char **getln();
void sigHandler(int sig);

int main() 
{
    int i;
    // int j;
    // int child_status;
    // int addInt;
    char fileName[256];
    int backgroundCheck = 0;
    int count;
    int fileNameCheck = 0;
    int fileRedirectCheck = 0;
    char **args; 
    pid_t child_pid;
    FILE *fp;
    // char backgroundArgs[256][500];
    // printf("lol\n");
    while(1) 
    {
        printf("/> ");
        args = getln();
        // printf("1\n");
        count = 0;
        for(i = 0; args[i] != NULL; i++)
        {
            count++;
        }
        // printf("2\n");

        if(strcmp(args[count - 1], "&") == 0)
        {
            backgroundCheck = 1;
            args[count - 1] = NULL;
        }
        // printf("3\n");

        for(int i = 0; i < count - 1; i++)
        {
            if(strcmp(args[i], ">") == 0)
            {
                fileNameCheck = 1;
                strcpy(fileName, args[i+1]);
                while(i != count - 1)
                {
                    args[i] = NULL;
                    i++;
                }
            }
            else if(strcmp(args[i], "<") == 0)
            {
                fileRedirectCheck = 1;
                strcpy(fileName, args[i+1]);
                while(i != count - 1)
                {
                    args[i] = NULL;
                    i++;
                }
            }

        }
        // printf("4\n");
        if(fileNameCheck == 1)
        {
            fp = freopen(fileName, "w+", stdout);
        }
    // printf("5\n");
        if(fileRedirectCheck == 1)
        {
            if(access(fileName, F_OK) != -1)
            {
                // printf("6\n");
                fp = freopen(fileName, "r+", stdin);
            }
            else
            {
                printf("There was an error opening your file, %s...\n", fileName);
                // break;
                exit(0);
            }
        }
// printf("7\n");
        // printf("count is %d\n", count);
        for(i = 0; args[i] != NULL; i++)
        {
            // printf("args[%s]\n", args[i]);
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
                    }

                    //             // fork();
                    // execvp(args[i], args);
                    // break;
                }
            }
            else if(count == 2)
            {

                // printf("args[%s] at count[%d] and i[%d]\n", args[i], count, i);
                // if(strpbrk(args[i], "-") == 0)
                // {
                //     child_pid = fork();
                //     if(child_pid == 0) 
                //     {
                //         execvp(args[i], &args[i]);
                //         // printf("error\n");
                //         exit(0);
                //     }
                //     else
                //     {
                //         wait(NULL);
                //         // do {
                //            // tpid = wait(&child_status);
                //            // printf("cpid is %d, tpid is %d\n", tpid, child_pid);
                //            // if(tpid != child_pid) process_terminated(tpid);
                //          // } while(tpid != child_pid);
                //         // printf("hi");
                //         // return child_status;
                //     }
                // }
                // else 
                if(backgroundCheck == 1)
                    // if(strcmp(args[count - 1], "&") == 0)
                {
                    // printf("hiya\n");
                    // char * executeString = malloc(sizeof(char) * 500);
                    // for(int i = 0; i < count - 1; i++)
                    // {
                    //     strcat(executeString, args[i]);
                    //     strcat(executeString, " ");    
                    // }
                    // // printf("string is %s\n", executeString);
                    child_pid = fork();
                    if(child_pid == 0) 
                    {
                        sigset(SIGINT, sigHandler);
                        execvp(args[i], &args[i]);
                        // printf("error\n");
                        exit(0);
                    }
                    else
                    {
                        wait(NULL);
                    }
                    backgroundCheck = 0;
                    //             execvp(args[0], &args[i]);
                }
                else
                {
                    child_pid = fork();
                    if(child_pid == 0) 
                    {
                        execvp(args[i], &args[i]);
                        //         // printf("error\n");
                        exit(0);
                    }
                    else
                    {
                        wait(NULL);
                        //         // do {
                        //            // tpid = wait(&child_status);
                        //            // printf("cpid is %d, tpid is %d\n", tpid, child_pid);
                        //            // if(tpid != child_pid) process_terminated(tpid);
                        //          // } while(tpid != child_pid);
                        //         // printf("hi");
                        //         // return child_status;
                    }
                }
                //         break;
            }
            else
            {
                // printf("args[%s]\n", args[i]);
                if(backgroundCheck == 1)
                    // if(strcmp(args[count - 1], "&") == 0)
                {
                    // printf("hiya\n");
                    // char * executeString = malloc(sizeof(char) * 500);
                    // for(int i = 0; i < count - 1; i++)
                    // {
                    // strcat(executeString, args[i]);
                    // strcat(executeString, " ");  
                    // }
                    // printf("string is %s\n", executeString);
                    child_pid = fork();
                    if(child_pid == 0) 
                    {


                        // printf("this arg is %s\n", args[i]);
                        sigset(SIGINT, sigHandler);
                        execvp(args[i], &args[i]);
                        // if(strcmp(args[i+1], "&") == 0)
                        // {
                        //     i++;
                        // }

                        // printf("error\n");
                        exit(0);
                        // }
                }
                else
                {
                    wait(NULL);
                }

                //             execvp(args[0], &args[i]);
            }
            else
            {
                // printf("args[%s]\n", args[i]);
                // printf("lol cats\n");
                if(fileNameCheck == 1)
                {
                    // printf("hiya\n");
                    child_pid = fork();
                    if(child_pid == 0) 
                    {
                        // printf("file name is %s\n", fileName);
                        // fp = freopen(fileName, "w+", stdout);
                        execvp(args[i], &args[i]);
                        // printf("%d 1lolcats\n", i);
                        //         //  freopen   

                        // fclose(fp);
                        // fileNameCheck = 0;
                        // execvp(args[i], &args[i]);
                        //         // printf("error\n");
                        exit(0);
                    }
                    else
                    {
                        wait(NULL);
                        //         // do {
                        //            // tpid = wait(&child_status);
                        //            // printf("cpid is %d, tpid is %d\n", tpid, child_pid);
                        //            // if(tpid != child_pid) process_terminated(tpid);
                        //          // } while(tpid != child_pid);
                        //         // printf("hi");
                        //         // return child_status;
                    }
                    //             printf("file name is %s\n", args[i+1]);
                    //             fp = freopen(args[i+1], "w+", stdin);
                    //             // printf("%d 1lolcats\n", i);
                    // //         //  freopen   

                    //         fclose(fp);
                    // exit(0);
                }
                else if(fileRedirectCheck == 1)
                {
                    // printf("uhhh\n");
                    child_pid = fork();
                    if(child_pid == 0) 
                    {
                        // printf("file name is %s\n", fileName);
                        // fp = freopen(fileName, "w+", stdout);
                        execvp(args[i], &args[i]);
                        // printf("%d 1lolcats\n", i);
                        //         //  freopen   

                        fclose(fp);
                        // fileNameCheck = 0;
                        // execvp(args[i], &args[i]);
                                // printf("error\n");
                        exit(0);
                        // printf("sort num\n");
                    }
                    else
                    {
                        // printf("why\n");
                        wait(NULL);
                        //         // do {
                        //            // tpid = wait(&child_status);
                        //            // printf("cpid is %d, tpid is %d\n", tpid, child_pid);
                        //            // if(tpid != child_pid) process_terminated(tpid);
                        //          // } while(tpid != child_pid);
                        //         // printf("hi");
                        //         // return child_status;
                    }
                    // printf("num\n");
                }
                // printf("num2\n");
            }
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

        }
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
        // printf("hiya\n");
        // backgroundCheck = 0;
    }
    if(fileNameCheck == 1)
    {
        // printf("lol\n");
        // fclose(fp);
        fileNameCheck = 0;
        // freopen(stdout, )
        freopen ("/dev/tty", "a", stdout);

        for(int k = 0; args[k] != NULL; i++)
        {
            // printf("1\n");
            child_pid = fork();
            // printf("2\n");
            if(child_pid == 0) 
            {
                // printf("3\n");
                // printf("file name is %s\n", fileName);
                // fp = freopen(fileName, "w+", stdout);
                execvp(args[k], &args[k]);
                // printf("%d 1lolcats\n", i);
                //         //  freopen   
                // printf("4\n");
                // fclose(fp);
                // fileNameCheck = 0;
                // execvp(args[i], &args[i]);
                //         // printf("error\n");
                exit(0);
                // break;
            }
            else
            {
                // printf("5\n");
                wait(NULL);
                // printf("6\n");
                break;
                //         // do {
                //            // tpid = wait(&child_status);
                //            // printf("cpid is %d, tpid is %d\n", tpid, child_pid);
                //            // if(tpid != child_pid) process_terminated(tpid);
                //          // } while(tpid != child_pid);
                //         // printf("hi");
                //         // return child_status;
            }
        }

        printf("\nAbove output successfully copied output to File: %s\n", fileName);
    }
    else if(fileRedirectCheck == 1)
    {
        // printf("hreali\n");
        // fclose(fo);
        fileRedirectCheck = 0;

        fp = freopen("/dev/tty", "r+", stdin);

        // printf("\nAbove output successfully copied output to File: %s\n", fileName);
        // fclose(fp);
         // fseek(stdin, 0, SEEK_END);
         // printf("wtf\n");
        // break;
        // freopen("/dev/tty", "a", stdout);
    }
    backgroundCheck = 0;
    // printf("done\n");
}
}


void sigHandler(int sig) {
    // printf("sig handler ay\n");
    exit(3);
}
