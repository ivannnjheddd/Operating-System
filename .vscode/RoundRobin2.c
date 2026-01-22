#include <stdio.h>
#include <stdbool.h>

struct Process {
    int id;
    int arrival;
    int burst;
    int remaining;
    int start;
    int end;
    int turnaround;
    int waiting;
    bool completed;
    bool in_queue;
    int last_active_time; // Last time process was active or started waiting
};

int main() {
    int n, quantum;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    struct Process p[n];
    int queue[n * 10]; // Queue for ready processes
    int front = 0, rear = -1;
    
    // Initialize processes
    for(int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nProcess P%d:\n", i + 1);
        printf("Arrival time: ");
        scanf("%d", &p[i].arrival);
        printf("Burst time: ");
        scanf("%d", &p[i].burst);
        p[i].remaining = p[i].burst;
        p[i].completed = false;
        p[i].in_queue = false;
        p[i].waiting = 0;
        p[i].start = -1;
        p[i].last_active_time = p[i].arrival;
    }
    
    printf("\nEnter time quantum: ");
    scanf("%d", &quantum);
    
    printf("\n=== Round Robin Scheduling ===\n");
    printf("Time\tProcess\tExecution\tQueue State\n");
    printf("----\t-------\t---------\t-----------\n");
    
    int time = 0;
    int completed = 0;
    bool cpu_idle = true;
    int current_process = -1;
    int exec_start_time = 0;
    int exec_remaining = 0;
    
    // Main simulation loop
    while(completed < n) {
        // Add newly arrived processes to queue
        for(int i = 0; i < n; i++) {
            if(p[i].arrival == time && !p[i].completed && !p[i].in_queue) {
                rear++;
                queue[rear] = i;
                p[i].in_queue = true;
                printf("%3d\t\t\t\tP%d arrived and added to queue\n", time, p[i].id);
            }
        }
        
        // If a process is currently executing and its quantum expired or it finished
        if(current_process != -1) {
            if(time == exec_start_time + exec_remaining) {
                // Process finished its quantum or completed
                if(p[current_process].remaining == 0) {
                    // Process completed
                    p[current_process].end = time;
                    p[current_process].completed = true;
                    p[current_process].in_queue = false;
                    p[current_process].turnaround = time - p[current_process].arrival;
                    completed++;
                    printf("%3d\tP%d\tCompleted\t", time, p[current_process].id);
                } else {
                    // Quantum expired, add back to queue
                    rear++;
                    queue[rear] = current_process;
                    p[current_process].in_queue = true;
                    printf("%3d\tP%d\tQuantum expired\t", time, p[current_process].id);
                }
                current_process = -1;
                cpu_idle = true;
            }
        }
        
        // If CPU is idle and queue has processes, start next one
        if(cpu_idle && front <= rear) {
            // Get next process from queue
            current_process = queue[front];
            front++; // Remove from front of queue
            
            // Track first start time
            if(p[current_process].start == -1) {
                p[current_process].start = time;
                // Add waiting time from arrival to first start
                p[current_process].waiting += (time - p[current_process].arrival);
            } else {
                // Add waiting time since last completion/quantum expiry
                p[current_process].waiting += (time - p[current_process].last_active_time);
            }
            
            p[current_process].in_queue = false;
            cpu_idle = false;
            
            // Determine execution time (min of quantum or remaining time)
            exec_remaining = (p[current_process].remaining < quantum) ? 
                            p[current_process].remaining : quantum;
            exec_start_time = time;
            
            printf("%3d\tP%d\tStart %d units\t", time, p[current_process].id, exec_remaining);
            
            // Update last active time
            p[current_process].last_active_time = time + exec_remaining;
        }
        
        // If CPU is idle and no processes ready, just advance time
        if(cpu_idle && front > rear) {
            printf("%3d\tIDLE\n", time);
        }
        
        // Display queue contents
        if(!cpu_idle || (cpu_idle && front <= rear)) {
            if(front > rear) {
                printf("Queue: Empty\n");
            } else {
                printf("Queue: ");
                for(int q = front; q <= rear; q++) {
                    printf("P%d ", p[queue[q]].id);
                }
                printf("\n");
            }
        }
        
        // If process is executing, reduce its remaining time
        if(current_process != -1) {
            p[current_process].remaining--;
        }
        
        time++;
        
        // Add waiting time for processes in queue
        for(int i = 0; i < n; i++) {
            if(!p[i].completed && p[i].in_queue) {
                p[i].waiting++;
            }
        }
    }
    
    // Calculate statistics
    float total_waiting = 0, total_turnaround = 0;
    int total_busy_time = 0;
    
    for(int i = 0; i < n; i++) {
        // Recalculate to ensure accuracy
        p[i].turnaround = p[i].end - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
        if(p[i].waiting < 0) p[i].waiting = 0;
        
        total_waiting += p[i].waiting;
        total_turnaround += p[i].turnaround;
        total_busy_time += p[i].burst;
    }
    
    // Calculate CPU utilization
    float cpu_utilization = (float)total_busy_time / (time - 1) * 100;
    
    // Display results
    printf("\n\n=== Results ===\n");
    printf("Process\tArrival\tBurst\tStart\tEnd\tWaiting\tTurnaround\n");
    printf("-------\t-------\t-----\t-----\t---\t-------\t----------\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].id, p[i].arrival, p[i].burst, 
               p[i].start, p[i].end, 
               p[i].waiting, p[i].turnaround);
    }
    
    printf("\n=== Summary ===\n");
    printf("Average Waiting Time: %.2f\n", total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround / n);
    printf("Total Execution Time: %d units\n", time - 1);
    printf("Total CPU Busy Time: %d units\n", total_busy_time);
    printf("CPU Utilization: %.2f%%\n", cpu_utilization);
    
    // Generate Gantt Chart
    printf("\n=== Gantt Chart ===\n");
    
    // Reset for Gantt chart
    for(int i = 0; i < n; i++) {
        p[i].remaining = p[i].burst;
        p[i].completed = false;
        p[i].in_queue = false;
    }
    
    front = 0;
    rear = -1;
    time = 0;
    completed = 0;
    current_process = -1;
    exec_start_time = 0;
    exec_remaining = 0;
    cpu_idle = true;
    
    printf("\nTime:  |");
    int prev_time = 0;
    
    while(completed < n) {
        // Add arriving processes
        for(int i = 0; i < n; i++) {
            if(p[i].arrival == time && !p[i].completed && !p[i].in_queue) {
                rear++;
                queue[rear] = i;
                p[i].in_queue = true;
            }
        }
        
        // Check if current process finished
        if(current_process != -1) {
            if(time == exec_start_time + exec_remaining) {
                if(p[current_process].remaining == 0) {
                    p[current_process].completed = true;
                    completed++;
                } else {
                    rear++;
                    queue[rear] = current_process;
                    p[current_process].in_queue = true;
                }
                current_process = -1;
                cpu_idle = true;
            }
        }
        
        // Start new process if CPU idle
        if(cpu_idle && front <= rear) {
            current_process = queue[front];
            front++;
            p[current_process].in_queue = false;
            cpu_idle = false;
            
            exec_remaining = (p[current_process].remaining < quantum) ? 
                            p[current_process].remaining : quantum;
            exec_start_time = time;
            
            // Print the bar
            if(time > prev_time) {
                printf("|");
            }
            printf(" P%d ", p[current_process].id);
            for(int t = 0; t < exec_remaining - 1; t++) {
                printf(" ");
            }
            prev_time = time + exec_remaining;
        }
        
        // Execute current process
        if(current_process != -1) {
            p[current_process].remaining--;
        }
        
        time++;
    }
    printf("|\n");
    
    // Print timeline
    printf("      0");
    for(int t = 1; t <= time; t++) {
        if(t % 5 == 0 || t == time - 1) {
            printf("%*d", 5, t);
        }
    }
    printf("\n");
    
    return 0;
}