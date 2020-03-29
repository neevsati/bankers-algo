/*
This is a tutorial from gfg to understand how multithreading works. Anyone who comes to this project can read this to understand the bankers_algo.c program. 
to compile : gcc multithread.c -lpthread
*/


#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>    
#include <pthread.h>  //posix thread header file for C
  
// creates a global variable to change it in threads 
int g = 0; 
  
// the function to be executed by all threads 
void *myThreadFun(void *vargp) 
{ 
    // stores the value argument passed to this thread 
    int *myid = (int *)vargp; 
  
    // create a static variable to observe its changes 
    static int s = 0; 
  
    // change static and global variables 
    ++s; ++g; 
  
    // prints the argument, static and global variables 
    printf("Thread ID: %d, Static: %d, Global: %d\n", *myid, ++s, ++g); 
} 
  
int main() 
{ 
    int i; 
    pthread_t tid; 
  
    // creates three threads 
    for (i = 0; i < 3; i++) 
        pthread_create(&tid, NULL, myThreadFun, (void *)&tid); 
  
    pthread_exit(NULL); 
    return 0; 
} 

