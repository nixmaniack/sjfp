/*
 ============================================================================
 Name        : sjfp.c
 Author      : Muneeb Shaikh
 Version     : 0.1
 Copyright   : None
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
int selectProcess(proc *);
void execProcess(proc *);


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

	execProcess(process);

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

	while( (pproc[i].arrvialTime <= currentTime) || (pproc[i].arrvialTime <= currentTime && pproc[i+1].arrvialTime <= currentTime)) {
		if( ((pproc[i].burstTime) < (pproc[i+1].burstTime)) && (pproc[i].burstTime!=0) ) {
			indexOfleastProcessTime = i;
			i++;
		}
	}
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

void execProcess(proc pproc[]) {
	int indexOfleastProcessTime;
	printf("Fetching next Shortest Process...\n");

	indexOfleastProcessTime = selectProcess(pproc);
	if(indexOfleastProcessTime == -1)
		return;

	printf("Executing Process %s \n", pproc[indexOfleastProcessTime].name);
	pproc[indexOfleastProcessTime].burstTime -= 1;
	system("sleep 1");
	currentTime += 1;
}
































/* These line is purposefully left at end */
