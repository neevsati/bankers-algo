// A Multithreaded Program that implements the banker's algorithm.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

int nResources, nProcesses;
int *resources;
int **allocated;
int **need;
int *safeSequence;

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