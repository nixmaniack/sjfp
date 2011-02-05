/*
 ============================================================================
 Name        : sjfp.c
 Author      : Muneeb Shaikh, Parikshit Ghodake
 Version     : 0.1
 Copyright   : GPL v3
 Description : Shortest Job First Pre-emptive Algorithm
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

static int currentTime=0;

typedef struct {
	char name[3];
	int arrvialTime;
	int burstTime;
}proc;

void psort(proc *, int);
int selectProcess(proc *);			/* Selects process having shortest burst time */
int execProcess(proc *, int);		/* Executes process got from selectProcess */
int getTotalBurstTime(proc *, int); /* Calculates total burst Time */

int main(void) {
	proc process[10];
	int i, numOfProcesses;

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

	printf("%d", getTotalBurstTime(process, numOfProcesses) );

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
	int i=0, indexOfleastProcessTime;
	indexOfleastProcessTime = -1;

	if(currentTime == 0) {
		return 0;
	} else {
		for(i=0; i < currentTime; i++) {
			if(pproc[i].arrvialTime <= currentTime) {
				if(pproc[i+1].arrvialTime <= currentTime) {
					if(pproc[i].burstTime <= pproc[i+1].burstTime) {
						return i;
					} else {
						return i+1;
					}
				} else {
					return i;
				}
			}
		}
	}

/*
	while( (pproc[i].arrvialTime <= currentTime) || (pproc[i].arrvialTime <= currentTime && pproc[i+1].arrvialTime <= currentTime)) {
		if( ((pproc[i].burstTime) < (pproc[i+1].burstTime)) && (pproc[i].burstTime!=0) ) {
			indexOfleastProcessTime = i;
			i++;
		}
	}
		*/
/*	for(i=0; i<=currentTime; i++) {
		if( ((pproc[i].burstTime) < (pproc[i+1].burstTime)) && (pproc[i].burstTime!=0) ) {
			indexOfleastProcessTime = i;
		}
	}
*/

	if(indexOfleastProcessTime == -1)
		return -1;
	return i;

}

int execProcess(proc pproc[], int totalBurstTime) {
	int indexOfleastProcessTime;
	printf("\n\nFetching next Shortest Process...\n");

	if(currentTime == totalBurstTime) /*Terminating Condition*/
		return 0;
	else {

		indexOfleastProcessTime = selectProcess(pproc);
		/*if(indexOfleastProcessTime == -1)
		return;*/

		printf("\nExecuting Process %s \n", pproc[indexOfleastProcessTime].name);
		pproc[indexOfleastProcessTime].burstTime -= 1;
		system("sleep 1");
		currentTime += 1;
	}

	execProcess(pproc, totalBurstTime);
	return 0;
}

int getTotalBurstTime(proc pproc[], int numOfProcesses) {
	int i, sum = 0;
	for(i=0; i< numOfProcesses; i++) {
		sum += pproc[i].burstTime;
	}
	return sum;
}






























/* These line is purposefully left at end */
