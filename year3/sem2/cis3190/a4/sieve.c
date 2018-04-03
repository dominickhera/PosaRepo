#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{

    int upperlimitInt = 0;
    printf("Enter the upper limit of prime numbers to calculate: ");
    scanf("%d", &upperlimitInt);
    int sieveArray[upperlimitInt];
    int newSieveCount = 0;
    int secondCount = 0;
    FILE * fp;

    clock_t initTime = clock();

    for(int i = 2; i <= upperlimitInt; i++)
    {
        sieveArray[i] = i; 
    }

    for(int i = 2; i <= upperlimitInt; i++)
    {
        if(sieveArray[i] % 2*i == 0)
        {
            // printf("shit equals 0? %d\n", sieveArray[i]);

            for(int k = i * 2; k <= upperlimitInt; k += i)
            {
                sieveArray[k] = 0;
            }

            for(int k = i * 3; k <= upperlimitInt; k += i)
            {
                sieveArray[k] = 0;
            }
        }
    }

    for(int i = 2; i <= upperlimitInt; i++)
    {
        if(sieveArray[i] % 3*i == 0 )
        {

            for(int k = i * 3; k <= upperlimitInt; k += i)
            {
                sieveArray[k] = 0;
            }
        }
    }

    for(int i = 2; i <= upperlimitInt; i++)
    {
        if(sieveArray[i] % 5*i == 0)
        {
            for(int k = i * 5; k <= upperlimitInt; k += i)
            {
                sieveArray[k] = 0;
            }
        }
    }

    for (int i = 2; i <= upperlimitInt; i++)
    {
        if(sieveArray[i] != 0)
        {
            newSieveCount++;
        }
    }
    int resultsArray[newSieveCount];

    for(int i = 2; i <= upperlimitInt; i++)
    {
        if(sieveArray[i] != 0)
        {
            resultsArray[secondCount] = sieveArray[i];
            secondCount++;
        }
    }

    fp = fopen("primeNumberCOutput.txt", "w");
    fprintf(fp, "results\n");

    for(int i = 0; i < newSieveCount; i++)
    {
        fprintf(fp, "%d\n", resultsArray[i]);
    }
    
    fprintf(fp, "\n");
    fclose(fp);

    clock_t finishTime = clock();

    printf("Execution Time: %f seconds\n", (float)(finishTime - initTime)/CLOCKS_PER_SEC);

    return 0;
}
