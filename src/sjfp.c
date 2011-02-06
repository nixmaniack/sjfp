/*
 ============================================================================
 Name        : sjfp.c
 Author      : Muneeb Shaikh
 Version     : 0.1.1
 Copyright   : GPL v3
 Description : Shortest Job First Pre-emptive Algorithm
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

static int currentTime=1;
int numOfProcesses;

typedef struct {
	char name[3];
	int arrvialTime;
	int burstTime;
}proc;

void psort(proc *, int);			/* Sorts Processes according to Burst Time */
int selectProcess(proc *);			/* Selects process having shortest burst time */
void execProcess(proc *, int);		/* Executes process got from selectProcess */
int getTotalBurstTime(proc *, int); /* Calculates total burst Time */

int main(void) {
	proc process[10];
	int i;

	puts("Shortest Job First Pre-emptive Algorithm\n");
	puts("Enter Number of Process: ");
	scanf("%d", &numOfProcesses);

	for(i=0; i<numOfProcesses; i++) {
		printf("Enter Process Name(Max 2 chars): ");
		scanf("%s", process[i].name);
		printf("Enter Arrival Time for Process P%d: ", i+1);
		scanf("%d", &process[i].arrvialTime);
		printf("Enter Burst Time for Process P%d: ", i+1);
		scanf("%d", &process[i].burstTime);
	}

	printf("PName\tArrTime\tBTime\n");

	for(i=0; i<numOfProcesses; i++) {
		printf("\n%s\t%d\t%d", process[i].name, process[i].arrvialTime, process[i].burstTime);
	}

	psort(process, numOfProcesses);
	puts("After Sorting \n");

	for(i=0; i<numOfProcesses; i++) {
		printf("\n%s\t%d\t%d", process[i].name, process[i].arrvialTime, process[i].burstTime);
	}

	printf("\nTotal Burst Time: %d \n", getTotalBurstTime(process, numOfProcesses) );

	execProcess(process, getTotalBurstTime(process, numOfProcesses ));

	printf("All Processes executed...");

	return EXIT_SUCCESS;
}


void psort(proc pproc[], int numOfProcesses) {
	int i, j, test;
	proc temp;

	for(i = numOfProcesses - 1; i > 0; i--) {
		test = 0;
		for(j=0; j < i; j++) {
			if((pproc[j].arrvialTime) > (pproc[j+1].arrvialTime) ) {
				temp = pproc[j];
				pproc[j] = pproc[j+1];
				pproc[j+1] = temp;
				test=1;
			}
		}
		if(test==0) break;
	}
}

int selectProcess(proc pproc[]) {
	int i=0, j, indexOfleastProcessTime, minBurstTime;
	indexOfleastProcessTime = -1;

	while ( pproc[i].arrvialTime <= currentTime && i < numOfProcesses ) {
		i++; 		/* Find array of arrived processes */
	}

	for(j=0; j <= i && pproc[j].burstTime == 0; j++); /* Find first non-zero value in array*/

	minBurstTime = pproc[j].burstTime;

	while(j<i) {
		if(pproc[j].burstTime != 0 && pproc[j].burstTime <= minBurstTime) {
			minBurstTime = pproc[j].burstTime;
			indexOfleastProcessTime = j;
		}
		j++;
	}
	return indexOfleastProcessTime;
}



void execProcess(proc pproc[], int totalBurstTime) {
	int indexOfleastProcessTime;

	while (currentTime != totalBurstTime+1) { /*Terminating Condition*/
		printf("\n\nFetching next Shortest Process...\n");

		indexOfleastProcessTime = selectProcess(pproc); /* Call to process selection function */

		printf("\nExecuting Process %s \n", pproc[indexOfleastProcessTime].name);
		pproc[indexOfleastProcessTime].burstTime -= 1;
		system("sleep 1");
		currentTime += 1;
	}

}



int getTotalBurstTime(proc pproc[], int numOfProcesses) {
	int i, sum = 0;
	for(i=0; i< numOfProcesses; i++) {
		sum += pproc[i].burstTime;
	}
	return sum;
}






























/* These line is purposefully written at end */
