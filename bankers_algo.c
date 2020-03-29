// A Multithreaded Program that implements the banker's algorithm.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

int nResources, nProcesses;
int *resources;
int **allocated;
int **maxRequired;
int **need;
int *safeSequence;

int main(int argc, char** argv) {
        printf("\nNumber of processes? ");
        scanf("%d", &nProcesses);

        printf("\nNumber of resources? ");
        scanf("%d", &nResources);

        resources = (int *)malloc(nResources * sizeof(*resources));
        printf("\nCurrently Available resources (R1 R2 ...)? ");

        for(int i=0; i<nResources; i++)
                scanf("%d", &resources[i]);

        allocated = (int **)malloc(nProcesses * sizeof(*allocated));
        
        for(int i=0; i<nProcesses; i++)
                allocated[i] = (int *)malloc(nResources * sizeof(**allocated));

        maxRequired = (int **)malloc(nProcesses * sizeof(*maxRequired));
        
        for(int i=0; i<nProcesses; i++)
                maxRequired[i] = (int *)malloc(nResources * sizeof(**maxRequired));

        printf("\n");
        
        for(int i=0; i<nProcesses; i++) {
                
                printf("\nResource allocated to process %d (R1 R2 ...)? ", i+1);
                
                for(int j=0; j<nResources; j++)
                        scanf("%d", &allocated[i][j]);
        }
        printf("\n");

        for(int i=0; i<nProcesses; i++) {
                printf("\nMaximum resource required by process %d (R1 R2 ...)? ", i+1);
                
                for(int j=0; j<nResources; j++)
                        scanf("%d", &maxRequired[i][j]);
        }
        printf("\n");


        need = (int **)malloc(nProcesses * sizeof(*need));
        
        for(int i=0; i<nProcesses; i++)
                need[i] = (int *)malloc(nResources * sizeof(**need));

        for(int i=0; i<nProcesses; i++)
                for(int j=0; j<nResources; j++)
                        need[i][j] = maxRequired[i][j] - allocated[i][j];

	    safeSequence = (int *)malloc(nProcesses * sizeof(*safeSequence));
        for(int i=0; i<nProcesses; i++) safeSequence[i] = -1;

        if(!getSafeSeq()) {
                printf("\nWARNING! The processes lead the system to an unsafe state.\n\n");
                exit(-1);
        }

        printf("\n\nSafe Sequence Found : ");
        for(int i=0; i<nProcesses; i++) {
                printf("%-3d", safeSequence[i]+1);
        }
        
        printf("\nExecuting Processes...\n\n");
        sleep(1);
}

bool getSafeSeq() {
        int tempResources[nResources];

        for(int i=0; i<nResources; i++) tempResources[i] = resources[i];

        bool finished[nProcesses];

        for(int i=0; i<nProcesses; i++) finished[i] = false;
        int nfinished=0;

        while(nfinished < nProcesses) {

                bool safe = false;

                for(int i=0; i<nProcesses; i++) {

                        if(!finished[i]) {

                                bool possible = true;

                                for(int j=0; j<nResources; j++)

                                        if(need[i][j] > tempResources[j]) {
                                                possible = false;
                                                break;
                                        }

                                if(possible) {

                                        for(int j=0; j<nResources; j++)
                                                tempResources[j] += allocated[i][j];

                                        safeSequence[nfinished] = i;
                                        finished[i] = true;
                                        ++nfinished;
                                        safe = true;
                                }
                        }
                }

                if(!safe) {
                        for(int k=0; k<nProcesses; k++) safeSequence[k] = -1;

                        return false; 
                }
        }
        return true;
}