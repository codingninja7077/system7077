#include<stdio.h>
#include<stdlib.h>

// Structure to represent a process in FCFS
typedef struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
} Process;

// Function to sort processes based on arrival time
void sortProcesses(Process *processes, int num_processes) {
    int i, j;
    Process temp;
    for(i = 0; i < num_processes - 1; i++) {
        for(j = 0; j < num_processes - i - 1; j++) {
            if(processes[j].arrival_time > processes[j+1].arrival_time) {
                temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = temp;
            }
        }
    }
}

// Function to implement FCFS scheduling algorithm
void fcfs(Process *processes, int num_processes) {
    int total_waiting_time = 0, total_turnaround_time = 0;
    printf("Process\tWaiting Time\tTurnaround Time\n");

    // Calculate waiting time for each process
    for(int i = 0; i < num_processes; i++) {
        if(i == 0) {
            processes[i].waiting_time = 0;
        } else {
            processes[i].waiting_time = processes[i-1].waiting_time + processes[i-1].burst_time;
        }
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        printf("%d\t%d\t\t%d\n", processes[i].process_id, processes[i].waiting_time, processes[i].turnaround_time);
    }

    // Calculate average waiting and turnaround time
    float avg_waiting_time = (float)total_waiting_time / num_processes;
    float avg_turnaround_time = (float)total_turnaround_time / num_processes;
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

// Function to find if page is present in frames
int findPage(int page, int *frames, int num_frames) {
    for(int i = 0; i < num_frames; i++) {
        if(frames[i] == page)
            return 1;
    }
    return 0;
}

// Function to implement Optimal page replacement algorithm
void optimalPageReplacement(int *page_reference_string, int num_pages, int num_frames) {
    int frames[num_frames], page_faults = 0, i, j;
    for(i = 0; i < num_frames; i++) {
        frames[i] = -1; // Initialize frames with -1 indicating empty frame
    }

    printf("Page\t  Frames\n");
    for(i = 0; i < num_pages; i++) {
        printf("%d\t", page_reference_string[i]);
        if(!findPage(page_reference_string[i], frames, num_frames)) {
            int replace_index = -1, farthest = i;
            for(j = 0; j < num_frames; j++) {
                int k;
                for(k = i+1; k < num_pages; k++) {
                    if(page_reference_string[k] == frames[j]) {
                        if(k > farthest) {
                            farthest = k;
                            replace_index = j;
                        }
                        break;
                    }
                }
                if(k == num_pages) {
                    replace_index = j;
                    break;
                }
            }
            frames[replace_index] = page_reference_string[i];
            page_faults++;
            for(j = 0; j < num_frames; j++) {
                printf("%d\t", frames[j]);
            }
            printf("PF\n");
        } else {
            for(j = 0; j < num_frames; j++) {
                printf("%d\t", frames[j]);
            }
            printf("\n");
        }
    }
    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    // FCFS Scheduling
    int num_processes;
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    Process processes[num_processes];
    printf("Enter arrival time and burst time for each process:\n");
    for(int i = 0; i < num_processes; i++) {
        printf("Process %d: ", i+1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].process_id = i + 1;
    }
    sortProcesses(processes, num_processes);
    fcfs(processes, num_processes);

    // Optimal Page Replacement
    int num_pages = 20; // number of pages in reference string
    int page_reference_string[] = {7, 1, 0, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int num_frames = 3; // number of frames
    optimalPageReplacement(page_reference_string, num_pages, num_frames);

    return 0;
}
