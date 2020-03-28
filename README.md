# Banker's Algorithm
Operating System Assignment - Neev Sati [11805116] [LPU]

## About

### Deadlock
It is a situation where set of processes are blocked from finishing because each process is holding a resource and waiting for another 
resource preoccupied by some other process.

### Banker's Algorithm
It is an algorithm used for avoiding deadlock and allocating resources. It tells whether the allocation should be done or not by simulating the allocation for predetermined maximum possible amounts of all resources.

*Sidenote* It is named Banker's Algorithm because of its application in Banking system. Whenever a person comes to a bank to request loan, the bank checks the available balance, then subtracts the amount requested and if the result is greater than the minimum balance it sanctions the loan.

There are two types of algorithm in it. 
1. Safety Algorithm - The algorithm for finding out whether or not a system is in a safe state.
2. Resource-Request Algorithm - The algorithm to check whether the resource requested will lead in safe state.

## Operating Systems
---

### Question:
Write a multithreaded program that implements the banker's algorithm.
Create n threads that request and release resources from the bank.
The banker will grant the request only if it leaves the system in a safe state.
It is important that shared data be safe from concurrent access.
To ensure safe access to shared data, you can use mutex locks.

### Compile manually:
```
$ compile
gcc -o bankeralgo bankers_algo.c

$ execute
./bankeralgo
```

### Input:
```
Number of processes? 3
Number of resources? 3

Currently Available resources (R1 R2 ...)? 3 2 2

Resource allocated to process A (R1 R2 ...)? 0 0 1
Resource allocated to process B (R1 R2 ...)? 3 2 0
Resource allocated to process C (R1 R2 ...)? 2 1 1

Maximum resource required by process A (R1 R2 ...)? 8 4 3
Maximum resource required by process B (R1 R2 ...)? 6 2 0
Maximum resource required by process C (R1 R2 ...)? 3 3 3

```
### Output:
```
Safe Sequence Found : B C A
Executing Processes...


--> Process B
	Allocated :   3  2  0
	Needed    :   3  0  0
	Available :   3  2  2
 	Resource Allocated!
	Process Code Running...
	Process Code Completed...
	Process Releasing Resource...
	Resource Released!
	Now Available :   6  4  2


--> Process C
	Allocated :   2  1  1
	Needed    :   1  2  2
	Available :   6  4  2
	Resource Allocated!
	Process Code Running...
	Process Code Completed...
	Process Releasing Resource...
	Resource Released!
	Now Available :   8  5  3


--> Process A
	Allocated :   0  0  1
	Needed    :   8  4  2
	Available :   8  5  3
	Resource Allocated!
	Process Code Running...
	Process Code Completed...
	Process Releasing Resource...
	Resource Released!
	Now Available :   8  5  4

All Processes Finished

```
