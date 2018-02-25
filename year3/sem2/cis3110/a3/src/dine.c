#include "dine.h"

//inits mutex to handle forks
pthread_mutex_t forks[1000];

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        printf("not enough arguments, exiting...\n");
        exit(1);
    }

    char* p;
    int philosopherCount;
    int processCount;


    //pulls command line arguments into variables
    philosopherCount = strtol(argv[1], &p, 10);
    processCount = strtol(argv[2], &p, 10);

    //declares's pthread to handle the philosophers
    pthread_t philosopherThread[philosopherCount];

    //outer forloop to track amount of times they eat
    for(int j = 1; j <= processCount; j++)
    {
        printf("Process %d\n", j);

        //inits a fork in the mutex for each of the philosophers
        for(int i = 1; i <= philosopherCount; i++)
        {
            pthread_mutex_init(&forks[i], NULL);
        }

        //creates the pthread for the philosophers, calling the main eating function
        for(int i = 1; i <= philosopherCount; i++)
        {
            pthread_create(&philosopherThread[i], NULL, philosopherFunction, (void *)i);
        }

        //joins all the pthreads together
        for(int i = 1; i <= philosopherCount; i++)
        {
            pthread_join(philosopherThread[i], NULL);
        }

        //destroys all the mutexes created for the forks.
        for(int i = 1; i < philosopherCount; i++)
        {
            pthread_mutex_destroy(&forks[i]);
        }
    }
    return 0;
}


//main dining solution: locks fork position, changes fork position while locked, calls think function, pauses for a moment, unlocks fork position, changes fork postiion while unlocked, calls eat function 
void *philosopherFunction(void* position)
{
    int eatPosition = (int) position;
    for(int i = 0; i < 1; i++)
    {
        pthread_mutex_lock(&forks[eatPosition]);
        pthread_mutex_lock(&forks[(eatPosition + 1) % 1000]);
        think(eatPosition);
        sleep(1);
        pthread_mutex_unlock(&forks[eatPosition]);
        pthread_mutex_unlock(&forks[(eatPosition + 1) % 1000]);
        eat(eatPosition);
        sleep(1);

    }
    pthread_exit(NULL);
}

//prints which philosopher is eating
void eat(int eatPosition)
{
    printf("philosopher %d is eating...\n", eatPosition);
}

//prints which philosopher is thinking
void think(int thinkPosition)
{
    printf("philosopher %d is thinking...\n", thinkPosition);
}
