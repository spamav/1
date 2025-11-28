#include <stdio.h>
#include <conio.h>

struct process {
    int pid;
    int bt;
    int at;
    int wt;
    int tat;
    int ct;
};

void fcfs() {
    struct process p[10];
    int n, i, j;
    float avg_wt = 0, avg_tat = 0;
    struct process temp;
    
    clrscr();
    printf("\n*** FCFS (First Come First Serve) Scheduling ***\n\n");
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    printf("\nEnter Arrival Time and Burst Time for each process:\n");
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess %d:", p[i].pid);
        printf("\n  Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("  Burst Time: ");
        scanf("%d", &p[i].bt);
    }
    
    /* Sort by arrival time */
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    
    /* Calculate completion, turnaround and waiting time */
    p[0].ct = p[0].at + p[0].bt;
    p[0].tat = p[0].ct - p[0].at;
    p[0].wt = p[0].tat - p[0].bt;
    
    for (i = 1; i < n; i++) {
        if (p[i].at > p[i - 1].ct) {
            p[i].ct = p[i].at + p[i].bt;
        } else {
            p[i].ct = p[i - 1].ct + p[i].bt;
        }
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
    
    printf("\n\n-----------------------------------------------------------");
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT");
    printf("\n-----------------------------------------------------------");
    
    for (i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d", 
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }
    
    printf("\n-----------------------------------------------------------");
    printf("\n\nAverage Waiting Time: %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time: %.2f", avg_tat / n);
    
    printf("\n\nPress any key to continue...");
    getch();
}

void sjf() {
    struct process p[10];
    int n, i, j, completed = 0, current_time = 0;
    int is_completed[10] = {0};
    float avg_wt = 0, avg_tat = 0;
    int min_bt, min_index;
    
    clrscr();
    printf("\n*** SJF (Shortest Job First) Scheduling ***\n\n");
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    printf("\nEnter Arrival Time and Burst Time for each process:\n");
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess %d:", p[i].pid);
        printf("\n  Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("  Burst Time: ");
        scanf("%d", &p[i].bt);
    }
    
    /* Non-preemptive SJF */
    while (completed != n) {
        min_bt = 9999;
        min_index = -1;
        
        /* Find process with minimum burst time among arrived processes */
        for (i = 0; i < n; i++) {
            if (p[i].at <= current_time && is_completed[i] == 0) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    min_index = i;
                } else if (p[i].bt == min_bt) {
                    if (p[i].at < p[min_index].at) {
                        min_index = i;
                    }
                }
            }
        }
        
        if (min_index == -1) {
            current_time++;
        } else {
            p[min_index].ct = current_time + p[min_index].bt;
            p[min_index].tat = p[min_index].ct - p[min_index].at;
            p[min_index].wt = p[min_index].tat - p[min_index].bt;
            
            current_time = p[min_index].ct;
            is_completed[min_index] = 1;
            completed++;
        }
    }
    
    printf("\n\n-----------------------------------------------------------");
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT");
    printf("\n-----------------------------------------------------------");
    
    for (i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d", 
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }
    
    printf("\n-----------------------------------------------------------");
    printf("\n\nAverage Waiting Time: %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time: %.2f", avg_tat / n);
    
    printf("\n\nPress any key to continue...");
    getch();
}

int main() {
    int choice;
    
    while (1) {
        clrscr();
        printf("\n*** CPU Scheduling Algorithms ***\n");
        printf("\n1. FCFS (First Come First Serve)");
        printf("\n2. SJF (Shortest Job First)");
        printf("\n3. Exit");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                fcfs();
                break;
            case 2:
                sjf();
                break;
            case 3:
                printf("\nExiting...");
                getch();
                return 0;
            default:
                printf("\nInvalid choice!");
                getch();
        }
    }
    
    return 0;
}



#include <stdio.h>
#include <conio.h>

struct segment {
    int seg_no;
    int base;
    int limit;
};

void segmentation() {
    struct segment s[10];
    int n, i;
    int logical_addr, seg_no, offset;
    int physical_addr;
    char choice;
    
    clrscr();
    printf("\n*** Memory Segmentation ***\n\n");
    
    printf("Enter number of segments: ");
    scanf("%d", &n);
    
    printf("\nEnter Segment Table:\n");
    for (i = 0; i < n; i++) {
        s[i].seg_no = i;
        printf("\nSegment %d:", i);
        printf("\n  Base Address: ");
        scanf("%d", &s[i].base);
        printf("  Limit (Size): ");
        scanf("%d", &s[i].limit);
    }
    
    printf("\n\n--- Segment Table ---");
    printf("\nSeg No.\tBase\tLimit");
    printf("\n--------------------");
    for (i = 0; i < n; i++) {
        printf("\n%d\t%d\t%d", s[i].seg_no, s[i].base, s[i].limit);
    }
    printf("\n--------------------");
    
    do {
        printf("\n\nEnter Logical Address:");
        printf("\n  Segment Number: ");
        scanf("%d", &seg_no);
        printf("  Offset: ");
        scanf("%d", &offset);
        
        if (seg_no < 0 || seg_no >= n) {
            printf("\nERROR: Invalid Segment Number!");
            printf("\nSegmentation Fault - Segment doesn't exist");
        } else if (offset >= s[seg_no].limit) {
            printf("\nERROR: Offset (%d) exceeds segment limit (%d)", 
                   offset, s[seg_no].limit);
            printf("\nSegmentation Fault - Addressing beyond segment boundary");
        } else {
            physical_addr = s[seg_no].base + offset;
            
            printf("\n\n--- Address Translation ---");
            printf("\nLogical Address: (%d, %d)", seg_no, offset);
            printf("\nSegment %d Base: %d", seg_no, s[seg_no].base);
            printf("\nSegment %d Limit: %d", seg_no, s[seg_no].limit);
            printf("\nPhysical Address = Base + Offset");
            printf("\nPhysical Address = %d + %d = %d", 
                   s[seg_no].base, offset, physical_addr);
            printf("\n\nSUCCESS: Valid address mapping!");
        }
        
        printf("\n\nDo you want to translate another address? (y/n): ");
        scanf(" %c", &choice);
        
    } while (choice == 'y' || choice == 'Y');
}

void segmentation_with_protection() {
    struct segment {
        int seg_no;
        int base;
        int limit;
        char protection[10];
    } s[10];
    
    int n, i;
    int logical_addr, seg_no, offset;
    int physical_addr;
    char operation[10];
    char choice;
    
    clrscr();
    printf("\n*** Segmentation with Protection ***\n\n");
    
    printf("Enter number of segments: ");
    scanf("%d", &n);
    
    printf("\nEnter Segment Table:\n");
    printf("Protection bits: R(Read), W(Write), X(Execute)\n");
    for (i = 0; i < n; i++) {
        s[i].seg_no = i;
        printf("\nSegment %d:", i);
        printf("\n  Base Address: ");
        scanf("%d", &s[i].base);
        printf("  Limit (Size): ");
        scanf("%d", &s[i].limit);
        printf("  Protection (e.g., RWX, RX, RW): ");
        scanf("%s", s[i].protection);
    }
    
    printf("\n\n--- Segment Table with Protection ---");
    printf("\nSeg No.\tBase\tLimit\tProtection");
    printf("\n-------------------------------------");
    for (i = 0; i < n; i++) {
        printf("\n%d\t%d\t%d\t%s", 
               s[i].seg_no, s[i].base, s[i].limit, s[i].protection);
    }
    printf("\n-------------------------------------");
    
    do {
        printf("\n\nEnter Logical Address:");
        printf("\n  Segment Number: ");
        scanf("%d", &seg_no);
        printf("  Offset: ");
        scanf("%d", &offset);
        printf("  Operation (R/W/X): ");
        scanf("%s", operation);
        
        if (seg_no < 0 || seg_no >= n) {
            printf("\nERROR: Invalid Segment Number!");
        } else if (offset >= s[seg_no].limit) {
            printf("\nERROR: Segmentation Fault!");
            printf("\nOffset exceeds segment limit");
        } else {
            int allowed = 0;
            
            if (operation[0] == 'R' || operation[0] == 'r') {
                if (strchr(s[seg_no].protection, 'R') != NULL || 
                    strchr(s[seg_no].protection, 'r') != NULL) {
                    allowed = 1;
                }
            } else if (operation[0] == 'W' || operation[0] == 'w') {
                if (strchr(s[seg_no].protection, 'W') != NULL || 
                    strchr(s[seg_no].protection, 'w') != NULL) {
                    allowed = 1;
                }
            } else if (operation[0] == 'X' || operation[0] == 'x') {
                if (strchr(s[seg_no].protection, 'X') != NULL || 
                    strchr(s[seg_no].protection, 'x') != NULL) {
                    allowed = 1;
                }
            }
            
            if (allowed) {
                physical_addr = s[seg_no].base + offset;
                printf("\n\n--- Address Translation ---");
                printf("\nLogical Address: (%d, %d)", seg_no, offset);
                printf("\nOperation: %s", operation);
                printf("\nSegment Protection: %s", s[seg_no].protection);
                printf("\nPhysical Address = %d + %d = %d", 
                       s[seg_no].base, offset, physical_addr);
                printf("\n\nSUCCESS: Operation permitted!");
            } else {
                printf("\n\nERROR: Protection Violation!");
                printf("\nOperation '%s' not allowed on segment %d", 
                       operation, seg_no);
                printf("\nSegment Protection: %s", s[seg_no].protection);
            }
        }
        
        printf("\n\nTranslate another address? (y/n): ");
        scanf(" %c", &choice);
        
    } while (choice == 'y' || choice == 'Y');
}

int main() {
    int choice;
    
    while (1) {
        clrscr();
        printf("\n*** Memory Segmentation Program ***\n");
        printf("\n1. Simple Segmentation");
        printf("\n2. Segmentation with Protection");
        printf("\n3. Exit");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                segmentation();
                break;
            case 2:
                segmentation_with_protection();
                break;
            case 3:
                printf("\nExiting...");
                getch();
                return 0;
            default:
                printf("\nInvalid choice!");
                getch();
        }
    }
    
    return 0;
}
