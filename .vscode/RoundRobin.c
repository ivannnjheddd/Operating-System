#include <stdio.h>

struct Process {
    int id;
    int arrival;
    int burst;
    int remaining;
    int start;
    int end;
    int turnaround;
    int waiting;
    int completed;
    int first_run;  // To track first execution time
};

int main() {
    int n, quantum, i, time = 0, completed = 0;
    float total_waiting = 0, total_turnaround = 0;
    float cpu_utilization;
    int total_busy_time = 0;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    struct Process p[n];
    
    // Initialize processes
    for(i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nProcess P%d:\n", i + 1);
        printf("Arrival time: ");
        scanf("%d", &p[i].arrival);
        printf("Burst time: ");
        scanf("%d", &p[i].burst);
        p[i].remaining = p[i].burst;
        p[i].completed = 0;
        p[i].waiting = 0;
        p[i].first_run = -1;  // Not executed yet
        total_busy_time += p[i].burst;
    }
    
    printf("\nEnter time quantum: ");
    scanf("%d", &quantum);
    
    printf("\n=== Round Robin Scheduling ===\n");
    printf("Time\tProcess\tExecution\n");
    printf("----\t-------\t---------\n");
    
    // Main Round Robin loop - FIXED
    while(completed < n) {
        int idle = 1;
        
        for(i = 0; i < n; i++) {
            if(p[i].arrival <= time && p[i].remaining > 0) {
                idle = 0;
                
                // Track first execution time
                if(p[i].first_run == -1) {
                    p[i].first_run = time;
                }
                
                int exec_time = (p[i].remaining < quantum) ? p[i].remaining : quantum;
                printf("%3d-%3d\tP%d\t%2d units\n", time, time + exec_time, p[i].id, exec_time);
                
                // Update waiting time for other ready processes
                for(int j = 0; j < n; j++) {
                    if(j != i && p[j].arrival <= time && p[j].remaining > 0 && !p[j].completed) {
                        p[j].waiting += exec_time;
                    }
                }
                
                p[i].remaining -= exec_time;
                time += exec_time;
                
                if(p[i].remaining == 0) {
                    p[i].end = time;
                    p[i].completed = 1;
                    completed++;
                    
                    // Calculate turnaround and waiting time - CORRECTED
                    p[i].turnaround = p[i].end - p[i].arrival;
                    p[i].waiting = p[i].turnaround - p[i].burst;
                    
                    // If waiting time is negative (arrival > 0), set to 0
                    if(p[i].waiting < 0) p[i].waiting = 0;
                }
                
                break;  // Important: Break after executing one process in this iteration
            }
        }
        
        // If CPU was idle and there are still processes to come
        if(idle) {
            // Find the next arriving process
            int next_arrival = 1000000;
            for(i = 0; i < n; i++) {
                if(!p[i].completed && p[i].arrival < next_arrival) {
                    next_arrival = p[i].arrival;
                }
            }
            
            if(next_arrival > time) {
                printf("%3d-%3d\tIDLE\n", time, next_arrival);
                time = next_arrival;
            } else {
                time++;  // Small increment if all processes have arrived
            }
        }
    }
    
    // Recalculate totals based on corrected waiting times
    total_waiting = 0;
    total_turnaround = 0;
    
    for(i = 0; i < n; i++) {
        total_waiting += p[i].waiting;
        total_turnaround += p[i].turnaround;
    }
    
    // Calculate CPU utilization
    cpu_utilization = (float)total_busy_time / time * 100;
    
    // Display results
    printf("\n\n=== Results ===\n");
    printf("Process\tArrival\tBurst\tStart\tEnd\tWaiting\tTurnaround\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].id, p[i].arrival, p[i].burst, 
               p[i].first_run, p[i].end, 
               p[i].waiting, p[i].turnaround);
    }
    
    printf("\n=== Summary ===\n");
    printf("Average Waiting Time: %.2f\n", total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround / n);
    printf("Total Execution Time: %d\n", time);
    printf("Total CPU Busy Time: %d\n", total_busy_time);
    printf("CPU Utilization: %.2f%%\n", cpu_utilization);
    
    // Simplified Gantt Chart
    printf("\n=== Simplified Gantt Chart ===\n");
    printf("Time:  ");
    
    // Reset for Gantt chart
    for(i = 0; i < n; i++) {
        p[i].remaining = p[i].burst;
        p[i].completed = 0;
    }
    
    time = 0;
    completed = 0;
    int last_pid = -1;
    int count = 0;
    
    while(completed < n) {
        int executed = 0;
        
        for(i = 0; i < n; i++) {
            if(p[i].arrival <= time && p[i].remaining > 0) {
                int exec_time = (p[i].remaining < quantum) ? p[i].remaining : quantum;
                
                // Print process block
                if(p[i].id != last_pid) {
                    if(last_pid != -1) printf(" ");
                    printf("|P%d", p[i].id);
                    last_pid = p[i].id;
                }
                
                p[i].remaining -= exec_time;
                time += exec_time;
                
                if(p[i].remaining == 0) {
                    completed++;
                }
                
                executed = 1;
                break;
            }
        }
        
        if(!executed) {
            if(last_pid != -2) {
                printf("|IDLE");
                last_pid = -2;
            }
            time++;
        }
        
        count++;
        if(count > 100) break;  // Safety break
    }
    printf("|\n");
    
    return 0;
}