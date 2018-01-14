#ifndef __DHERA_SIMCPU__
#define __DHERA_SIMCPU__


//thread struct which is techinically the process struct
typedef struct Thread
{
    int processNum;
	int threadNum;
	int arrivalTime;
	int cpuCount;
	int cpuTime;
	int ioTime;

}Thread;


//process struct which holds flags and all other basic data
typedef struct Process
{
    int processCount;
    int threadSwitch;
    int processSwitch;
    int averageTurnAroundTime;
    int totalTime;
    int cpuUtilization;

    int detailFlag;
    int verboseFlag;
    int roundRobinFlag;
    int quantumInteger;

    Thread * cpuThread;

}Process;


#endif
