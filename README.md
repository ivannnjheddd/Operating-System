# Operating-System

Round Robin Scheduling in Operating System
Last Updated : 6 Jan, 2026

Round Robin Scheduling is a method used by operating systems to manage the execution time of multiple processes that are competing for CPU attention. It is called "round robin" because the system rotates through all the processes, allocating each of them a fixed time slice or "quantum", regardless of their priority.

The primary goal of this scheduling method is to ensure that all processes are given an equal opportunity to execute, promoting fairness among tasks.

Process Arrival: Processes enter the system and are placed in a queue.
Time Allocation: Each process is given a certain amount of CPU time, called a quantum.
Execution: The process uses the CPU for the allocated time.
Rotation: If the process completes within the time, it leaves the system. If not, it goes back to the end of the queue.
Repeat: The CPU continues to cycle through the queue until all processes are completed.
round_robinn
Round Robin Flow Chart
Example:
To understand the Round Robin Scheduling algorithm, let’s consider the following two scenarios:

Scenario 1: Processes with Same Arrival Time
Consider the following table of arrival time and burst time for three processes P1, P2 and P3 and given Time Quantum = 2 ms

Process	Burst Time	Arrival Time
 P1  	 4 ms	0 ms
 P2	 5 ms	0 ms
 P3	 3 ms	0 ms
Step-by-Step Execution:

Time 0-2 (P1): P1 runs for 2 ms (total time left: 2 ms).
Time 2-4 (P2): P2 runs for 2 ms (total time left: 3 ms).
Time 4-6 (P3): P3 runs for 2 ms (total time left: 1 ms).
Time 6-8 (P1): P1 finishes its last 2 ms.
Time 8-10 (P2): P2 runs for another 2 ms (total time left: 1 ms).
Time 10-11 (P3): P3 finishes its last 1 ms.
Time 11-12 (P2): P2 finishes its last 1 ms.
Gantt Chart:
23.webp23.webp
Now, lets calculate average waiting time and turn around time:

Turnaround Time = Completion Time - Arrival Time
Waiting Time = Turnaround Time - Burst Time
Processes	AT	BT	CT	TAT	WT
P1	0	4	8	8-0 = 8	8-4 = 4
P2	0	5	12	12-0 = 12	12-5 = 7
P3	0	3	11	11-0 = 11	11-3 = 8
Average Turn around time = (8 + 12 + 11)/3 = 31/3 = 10.33 ms
Average waiting time = (4 + 7 + 8)/3 = 19/3 = 6.33 ms
Scenario 2: Processes with Different Arrival Times
Consider the following table of arrival time and burst time for three processes P1, P2 and P3 and given Time Quantum = 2

Process	Burst Time (BT)	Arrival Time (AT)
P1	5 ms	0 ms
P2	2 ms	4 ms
P3	4 ms	5 ms
Step-by-Step Execution:
1. Time 0-2 (P1 Executes):

P1 starts execution as it arrives at 0 ms.
Runs for 2 ms; remaining burst time = 5 - 2 = 3 ms.
Ready Queue: [P1].
2. Time 2-4 (P1 Executes Again):

P1 continues execution since no other process has arrived yet.
Runs for 2 ms; remaining burst time = 3 - 2 = 1 ms.
P2 arrive at 4 ms.
Ready Queue: [P2, P1].
3. Time 4-6 (P2 Executes):

P2 starts execution as it arrives at 4 ms.
Runs for 2 ms; remaining burst time = 2 - 2 = 0 ms.
P3 arrive at 5ms
Ready Queue: [P1, P3].
4. Time 6-7 (P1 Executes):

P1 starts execution.
Runs for 1 ms; remaining burst time = 1 - 1 = 0 ms.
Ready Queue: [P3].
5. Time 7-9 (P3 Executes):

P3 starts execution.
Remaining burst time = 4 - 2 = 2 ms.
Ready Queue: [P3].
6. Time 9-11 (P3 Executes Again):

P3 resumes execution and runs for 2 ms and complete its execution
Remaining burst time = 2 - 2 = 0 ms.
Ready Queue: [].
Gantt Chart:
Round-Robin-Scheduling-Algorithm-with-different-Arrival-Time-2.webpRound-Robin-Scheduling-Algorithm-with-different-Arrival-Time-2.webp
Now, lets calculate average waiting time and turn around time:
Process	Completion Time (CT)	Turnaround Time (TAT = CT - AT)	Waiting Time (WT = TAT - BT)
P1	7 ms	7 ms	2 ms
P2	6 ms	2 ms	0 ms
P3	11 ms	6 ms	2 ms

Average Turn around time =7+2+6/3​=15/3=5ms
Average waiting time = 2+0+2/3=1.33ms

Code Implementation:
Program for Round Robin Scheduling for the Same Arrival Time
Program for Round Robin Scheduling with Different Arrival Times

Advantages of Round Robin Scheduling
Fairness: Each process gets an equal share of the CPU.
Simplicity: The algorithm is straightforward and easy to implement.
Responsiveness: Round Robin can handle multiple processes without significant delays, making it ideal for time-sharing systems.

Disadvantages of Round Robin Scheduling:
Overhead: Switching between processes can lead to high overhead, especially if the quantum is too small.
Underutilization: If the quantum is too large, it can cause the CPU to feel unresponsive as it waits for a process to finish its time.


































Preemptive and Non-Preemptive Scheduling
Last Updated : 3 Dec, 2025

CPU scheduling in operating systems is the method of selecting which process in the ready queue will execute on the CPU next. It aims to utilise the processor efficiently while minimising waiting and response times. By determining an optimal execution order, CPU scheduling enhances overall system performance, supports smooth multitasking, and improves the user experience.

Scheduling can be broadly classified into two types: Preemptive and Non-Preemptive.

Preemptive-Scheduling-vs--Non-Preemptive-Scheduling
Preemptive Scheduling vs Non-Preemptive Scheduling
Preemptive Scheduling

In preemptive scheduling, the operating system can interrupt a running process to allocate the CPU to another process usually due to priority rules or time-sharing policies. A process may be moved from Running → Ready state before it finishes.

In the following example P2 is preempted at time 1 due to arrival of a higher priority process.

Preemptive Scheduling
Preemptive Scheduling+
Examples:

Round Robin
Shortest Remaining Time First (SRTF)
Priority Scheduling (preemptive version)

Advantages
Prevents one process from monopolizing CPU
Better average response time in multi-user systems
Widely used in modern OS (Windows, Linux, macOS)

Disadvantages
More complex to implement
Higher overhead from context switching
Can cause starvation of low-priority processes
Risk of concurrency issues if preempted during shared resource access

Non-Preemptive Scheduling
In non-preemptive scheduling, once a process starts using the CPU, it runs until it finishes or moves to a waiting state. The OS cannot forcibly take away the CPU.

Below is the table and Gantt Chart according to the First Come First Serve (FCFS) Algorithm: We can notice that every process finishes execution once it gets CPU.

Non Preemptive Scheduling
Examples:

First Come First Serve (FCFS)
Shortest Job First (SJF)
Priority Scheduling (non-preemptive version)
Advantages
It is easy to implement in an operating system. It was used in Windows 3.11 and early macOS.
It has a minimal scheduling burden.
Less computational resources are used.
Disadvantages
It is open to denial of service attack. A malicious process can take CPU forever.
Since we cannot implement round robin, the average response time becomes less.
Preemptive vs. Non-Preemptive Scheduling
Preemptive Scheduling	Non-Preemptive Scheduling
In this resources(CPU Cycle) are allocated to a process for a limited time.	Once resources(CPU Cycle) are allocated to a process, the process holds it till it completes its burst time or switches to waiting state
Process can be interrupted in between.	Process can not be interrupted until it terminates itself or its time is up
If a process having high priority frequently arrives in the ready queue, a low priority process may starve	If a process with a long burst time is running CPU, then later coming process with less CPU burst time may starve
It has overheads of scheduling the processes	It does not have overheads
Average process response time is less	Average process response time is high
Decisions are made by the scheduler and are based on priority and time slice allocation	Decisions are made by the process itself and the OS just follows the process's instructions
More as a process might be preempted when it was accessing a shared resource.

Less as a process is never preempted.

Examples of preemptive scheduling are Round Robin and Shortest Remaining Time First	Examples of non-preemptive scheduling are First Come First Serve and Shortest Job GRADE: ​​​
 
AIM:​Deadlock Avoidance​
To Simulate bankers algorithm for Dead Lock Avoidance (Banker‘s Algorithm)
 
DESCRIPTION:
Deadlock is a situation where in two or more competing actions are waiting f or the other to finish, and thus neither ever does. When a new process enters a system, it must declare the maximum number of instances of each resource type it needed. This number may exceed the total number of resources in the system. When the user requests a set of resources, the system must determine whether the allocation of each resources will leave the system in safe state. If it will the resources are allocation; otherwise the process must wait until some other process release the resources.
 
ALGORITHM
​Step1: ​Start the program.
Step2: ​Get the values of resources and processes.
Step3: Get the avail value.
Step4: After allocation find the need value.
Step5: ​Check whether it’s possible to allocate.
Step6: ​If it is possible then the system is in safe state.
Step7:​Else system is not in safety state.
Step8: ​If the new request comes then check that the system is in safety.
Step9:​or not if we allow the request.
Step10: stop the program.
Step 11: end​
 

 

PROGRAM:
#include<stdio.h>
#include<conio.h>
#include<string.h>
void main()
{
int alloc[10][10],max[10][10];
int avail[10],work[10],total[10];
int i,j,k,n,need[10][10];
int m;
int count=0,c=0;
char finish[10];
clrscr();
printf("Enter the no. of processes and resources:");
scanf("%d%d",&n,&m);
for(i=0;i<=n;i++)
finish[i]='n';
printf("Enter the claim matrix:\n");
for(i=0;i<n;i++)
for(j=0;j<m;j++)
scanf("%d",&max[i][j]);
printf("Enter the allocation matrix:\n");
for(i=0;i<n;i++)
for(j=0;j<m;j++)
scanf("%d",&alloc[i][j]);
printf("Resource vector:");
for(i=0;i<m;i++)
scanf("%d",&total[i]);
for(i=0;i<m;i++)
avail[i]=0; for(i=0;i<n;i++)
for(j=0;j<m;j++)
avail[j]+=alloc[i][j];
for(i=0;i<m;i++)
work[i]=avail[i];
for(j=0;j<m;j++)
work[j]=total[j]-work[j];
for(i=0;i<n;i++)
for(j=0;j<m;j++)
need[i][j]=max[i][j]-alloc[i][j];
A:
for(i=0;i<n;i++)
{
c=0;
for(j=0;j<m;j++)
if((need[i][j]<=work[j])&&(finish[i]=='n'))
c++;
if(c==m)
{
printf("All the resources can be allocated to Process %d", i+1);
printf("\n\nAvailable resources are:");
for(k=0;k<m;k++)
{
work[k]+=alloc[i][k];
printf("%4d",work[k]);
}
printf("\n");
finish[i]='y';
printf("\nProcess %d executed?:%c \n",i+1,finish[i]);
count++;
}
}
if(count!=n)
goto A;
else
printf("\n System is in safe mode");
printf("\n The given state is safe state");
getch();
}
 
 
OUTPUT:
 
Enter the no. of processes and resources: 4 3
Enter the claim matrix:
3 2 2
6 1 3
3 1 4
4 2 2
Enter the allocation matrix:
1 0 0
6 1 2
2 1 1
0 0 2
Resource vector:9 3 6
All the resources can be allocated to Process 2
Available resources are: 6 2 3
Process 2 executed?: y
All the resources can be allocated to Process 3 Available resources are: 8 3 4
Process 3 executed?:y
All the resources can be allocated to Process 4 Available resources are: 8 3 6
Process 4 executed?:y
All the resources can be allocated to Process 1
Available resources are: 9 3 6
Process 1 executed?:y
System is in safe mode
The given state is safe state
 
OBSERVATION:
 
1. What is meant by deadlock?
2. What is safe state in banker’s algorithms?
3. What is banker’s algorithm?
4. What are the necessary conditions where deadlock occurs?
5. What are the principles and goals of protection




GRADE: ​​​
 
AIM:​Deadlock Avoidance​
To Simulate bankers algorithm for Dead Lock Avoidance (Banker‘s Algorithm)
 
DESCRIPTION:
Deadlock is a situation where in two or more competing actions are waiting f or the other to finish, and thus neither ever does. When a new process enters a system, it must declare the maximum number of instances of each resource type it needed. This number may exceed the total number of resources in the system. When the user requests a set of resources, the system must determine whether the allocation of each resources will leave the system in safe state. If it will the resources are allocation; otherwise the process must wait until some other process release the resources.
 
ALGORITHM
​Step1: ​Start the program.
Step2: ​Get the values of resources and processes.
Step3: Get the avail value.
Step4: After allocation find the need value.
Step5: ​Check whether it’s possible to allocate.
Step6: ​If it is possible then the system is in safe state.
Step7:​Else system is not in safety state.
Step8: ​If the new request comes then check that the system is in safety.
Step9:​or not if we allow the request.
Step10: stop the program.
Step 11: end​
 

 

PROGRAM:
#include<stdio.h>
#include<conio.h>
#include<string.h>
void main()
{
int alloc[10][10],max[10][10];
int avail[10],work[10],total[10];
int i,j,k,n,need[10][10];
int m;
int count=0,c=0;
char finish[10];
clrscr();
printf("Enter the no. of processes and resources:");
scanf("%d%d",&n,&m);
for(i=0;i<=n;i++)
finish[i]='n';
printf("Enter the claim matrix:\n");
for(i=0;i<n;i++)
for(j=0;j<m;j++)
scanf("%d",&max[i][j]);
printf("Enter the allocation matrix:\n");
for(i=0;i<n;i++)
for(j=0;j<m;j++)
scanf("%d",&alloc[i][j]);
printf("Resource vector:");
for(i=0;i<m;i++)
scanf("%d",&total[i]);
for(i=0;i<m;i++)
avail[i]=0; for(i=0;i<n;i++)
for(j=0;j<m;j++)
avail[j]+=alloc[i][j];
for(i=0;i<m;i++)
work[i]=avail[i];
for(j=0;j<m;j++)
work[j]=total[j]-work[j];
for(i=0;i<n;i++)
for(j=0;j<m;j++)
need[i][j]=max[i][j]-alloc[i][j];
A:
for(i=0;i<n;i++)
{
c=0;
for(j=0;j<m;j++)
if((need[i][j]<=work[j])&&(finish[i]=='n'))
c++;
if(c==m)
{
printf("All the resources can be allocated to Process %d", i+1);
printf("\n\nAvailable resources are:");
for(k=0;k<m;k++)
{
work[k]+=alloc[i][k];
printf("%4d",work[k]);
}
printf("\n");
finish[i]='y';
printf("\nProcess %d executed?:%c \n",i+1,finish[i]);
count++;
}
}
if(count!=n)
goto A;
else
printf("\n System is in safe mode");
printf("\n The given state is safe state");
getch();
}
 
 
OUTPUT:
 
Enter the no. of processes and resources: 4 3
Enter the claim matrix:
3 2 2
6 1 3
3 1 4
4 2 2
Enter the allocation matrix:
1 0 0
6 1 2
2 1 1
0 0 2
Resource vector:9 3 6
All the resources can be allocated to Process 2
Available resources are: 6 2 3
Process 2 executed?: y
All the resources can be allocated to Process 3 Available resources are: 8 3 4
Process 3 executed?:y
All the resources can be allocated to Process 4 Available resources are: 8 3 6
Process 4 executed?:y
All the resources can be allocated to Process 1
Available resources are: 9 3 6
Process 1 executed?:y
System is in safe mode
The given state is safe state
 
OBSERVATION:
 
1. What is meant by deadlock?
2. What is safe state in banker’s algorithms?
3. What is banker’s algorithm?
4. What are the necessary conditions where deadlock occurs?
5. What are the principles and goals of protection








