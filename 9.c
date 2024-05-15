#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

typedef struct {
    int at; // Arrival Time
    int bt; // Burst Time
    int bt_remaining; // Remaining Burst Time
    int priority;
    int ct; // Completion Time
    int tat; // Turn Around Time
    int wt; // Waiting Time
    int is_completed;
} Process;

void priority_preemptive(Process processes[], int n) {
    int time = 0, completed = 0, shortest = -1;
    while (completed != n) {
        int min_priority = __INT_MAX__;
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= time && processes[i].is_completed == 0 && processes[i].priority < min_priority) {
                min_priority = processes[i].priority;
                shortest = i;
            }
        }
        if (shortest == -1) {
            time++;
        } else {
            processes[shortest].bt_remaining--;
            if (processes[shortest].bt_remaining == 0) {
                processes[shortest].ct = time + 1;
                processes[shortest].tat = processes[shortest].ct - processes[shortest].at;
                processes[shortest].wt = processes[shortest].tat - processes[shortest].bt;
                processes[shortest].is_completed = 1;
                completed++;
            }
            time++;
        }
    }
}

void fcfs(Process processes[], int n) {
    int time = 0, completed = 0;
    while (completed != n) {
        int earliest = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= time && processes[i].is_completed == 0) {
                if (earliest == -1 || processes[i].at < processes[earliest].at) {
                    earliest = i;
                }
            }
        }
        if (earliest == -1) {
            time++;
        } else {
            time += processes[earliest].bt;
            processes[earliest].ct = time;
            processes[earliest].tat = processes[earliest].ct - processes[earliest].at;
            processes[earliest].wt = processes[earliest].tat - processes[earliest].bt;
            processes[earliest].is_completed = 1;
            completed++;
        }
    }
}

void print_table(Process processes[], int n) {
    printf("P\tAT\tBT\tPri\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, processes[i].at, processes[i].bt, processes[i].priority,
               processes[i].ct, processes[i].tat, processes[i].wt);
    }
}

void reset_processes(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].bt_remaining = processes[i].bt;
        processes[i].ct = 0;
        processes[i].tat = 0;
        processes[i].wt = 0;
        processes[i].is_completed = 0;
    }
}

int main() {
    int n;
    Process processes[MAX_PROCESSES];
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].at, &processes[i].bt, &processes[i].priority);
        processes[i].bt_remaining = processes[i].bt;
        processes[i].is_completed = 0;
    }

    printf("\nPriority Preemptive Scheduling\n");
    priority_preemptive(processes, n);
    print_table(processes, n);

    reset_processes(processes, n);

    printf("\nFirst-Come-First-Serve Scheduling\n");
    fcfs(processes, n);
    print_table(processes, n);

    return 0;
}

/*
Input Example

Number of processes: 4

Process 1: AT=0, BT=5, Priority=2
Process 2: AT=1, BT=3, Priority=1
Process 3: AT=2, BT=8, Priority=4
Process 4: AT=3, BT=6, Priority=3
*/