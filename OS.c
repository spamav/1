sites : https://sites.google.com/view/spamavanthi/home
github : https://github.com/spamav/1
gdrive :https://drive.google.com/drive/folders/1vYtQ3wXk_gZzgSoeKo8LIrJLta1bLxTn?usp=drive_link



#include <stdio.h>
#include <conio.h>
#include <string.h>

/* Structure to represent a segment */
struct Segment {
    char name[20];
    int base;
    int limit;
};

/* Function to display segment table */
void displaySegmentTable(struct Segment seg[], int n) {
    int i;
    printf("\n\t*** SEGMENT TABLE ***\n");
    printf("\nSegment\t\tBase\tLimit\n");
    printf("---------------------------------------\n");
    for(i = 0; i < n; i++) {
        printf("%-15s\t%d\t%d\n", seg[i].name, seg[i].base, seg[i].limit);
    }
}

/* Function to translate logical address to physical address */
void translateAddress(struct Segment seg[], int n) {
    int seg_num, offset, physical_addr;
    
    printf("\n\n*** ADDRESS TRANSLATION ***\n");
    printf("\nEnter Segment Number (0-%d): ", n-1);
    scanf("%d", &seg_num);
    
    if(seg_num < 0 || seg_num >= n) {
        printf("\nError: Invalid Segment Number!\n");
        return;
    }
    
    printf("Enter Offset: ");
    scanf("%d", &offset);
    
    /* Check if offset is within segment limit */
    if(offset < 0 || offset >= seg[seg_num].limit) {
        printf("\nError: SEGMENTATION FAULT!");
        printf("\nOffset %d exceeds segment limit %d\n", 
               offset, seg[seg_num].limit);
        return;
    }
    
    /* Calculate physical address */
    physical_addr = seg[seg_num].base + offset;
    
    printf("\n--- Translation Details ---");
    printf("\nSegment: %s", seg[seg_num].name);
    printf("\nBase Address: %d", seg[seg_num].base);
    printf("\nOffset: %d", offset);
    printf("\nPhysical Address: %d + %d = %d\n", 
           seg[seg_num].base, offset, physical_addr);
}

/* Function to add a new segment */
int addSegment(struct Segment seg[], int n) {
    if(n >= 10) {
        printf("\nError: Maximum segments reached!\n");
        return n;
    }
    
    printf("\n\n*** ADD NEW SEGMENT ***\n");
    printf("\nEnter Segment Name: ");
    fflush(stdin);
    gets(seg[n].name);
    
    printf("Enter Base Address: ");
    scanf("%d", &seg[n].base);
    
    printf("Enter Segment Limit (Size): ");
    scanf("%d", &seg[n].limit);
    
    printf("\nSegment added successfully!\n");
    return n + 1;
}

/* Function to demonstrate segmentation with example */
void demonstrateSegmentation() {
    struct Segment seg[10];
    int n = 5;
    
    /* Initialize example segments */
    strcpy(seg[0].name, "Code");
    seg[0].base = 1000;
    seg[0].limit = 500;
    
    strcpy(seg[1].name, "Data");
    seg[1].base = 1500;
    seg[1].limit = 300;
    
    strcpy(seg[2].name, "Stack");
    seg[2].base = 1800;
    seg[2].limit = 400;
    
    strcpy(seg[3].name, "Heap");
    seg[3].base = 2200;
    seg[3].limit = 600;
    
    strcpy(seg[4].name, "Symbol Table");
    seg[4].base = 2800;
    seg[4].limit = 200;
    
    printf("\n\t*** SEGMENTATION DEMONSTRATION ***\n");
    printf("\nExample: A program divided into 5 segments\n");
    
    displaySegmentTable(seg, n);
    
    printf("\n\nExample Translations:\n");
    printf("---------------------");
    
    printf("\n\n1. Accessing Code Segment:");
    printf("\n   Logical Address: (Segment 0, Offset 100)");
    printf("\n   Physical Address: %d + 100 = %d", seg[0].base, seg[0].base + 100);
    
    printf("\n\n2. Accessing Data Segment:");
    printf("\n   Logical Address: (Segment 1, Offset 50)");
    printf("\n   Physical Address: %d + 50 = %d", seg[1].base, seg[1].base + 50);
    
    printf("\n\n3. Invalid Access (Segmentation Fault):");
    printf("\n   Logical Address: (Segment 0, Offset 600)");
    printf("\n   Error: Offset 600 exceeds limit 500");
    
    printf("\n\nPress any key to continue...");
    getch();
}

/* Main function with menu */
void main() {
    struct Segment seg[10];
    int choice, n = 0, i;
    int initialized = 0;
    
    clrscr();
    
    do {
        clrscr();
        printf("\n\t*** SEGMENTATION MEMORY MANAGEMENT ***\n");
        printf("\n1. Initialize Segment Table");
        printf("\n2. Display Segment Table");
        printf("\n3. Translate Logical to Physical Address");
        printf("\n4. Add New Segment");
        printf("\n5. Demonstration with Example");
        printf("\n6. Exit");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                clrscr();
                printf("\n*** INITIALIZE SEGMENT TABLE ***\n");
                printf("\nEnter number of segments (max 10): ");
                scanf("%d", &n);
                
                if(n > 10 || n < 1) {
                    printf("\nInvalid number of segments!\n");
                    n = 0;
                    getch();
                    break;
                }
                
                for(i = 0; i < n; i++) {
                    printf("\n--- Segment %d ---\n", i);
                    printf("Segment Name: ");
                    fflush(stdin);
                    gets(seg[i].name);
                    
                    printf("Base Address: ");
                    scanf("%d", &seg[i].base);
                    
                    printf("Segment Limit (Size): ");
                    scanf("%d", &seg[i].limit);
                }
                
                initialized = 1;
                printf("\nSegment table initialized successfully!\n");
                getch();
                break;
                
            case 2:
                clrscr();
                if(!initialized || n == 0) {
                    printf("\nError: Segment table not initialized!\n");
                    printf("Please initialize segment table first.\n");
                } else {
                    displaySegmentTable(seg, n);
                }
                getch();
                break;
                
            case 3:
                clrscr();
                if(!initialized || n == 0) {
                    printf("\nError: Segment table not initialized!\n");
                    printf("Please initialize segment table first.\n");
                } else {
                    displaySegmentTable(seg, n);
                    translateAddress(seg, n);
                }
                getch();
                break;
                
            case 4:
                clrscr();
                if(!initialized) {
                    printf("\nError: Segment table not initialized!\n");
                    printf("Please initialize segment table first.\n");
                } else {
                    n = addSegment(seg, n);
                }
                getch();
                break;
                
            case 5:
                clrscr();
                demonstrateSegmentation();
                break;
                
            case 6:
                printf("\nExiting...\n");
                break;
                
            default:
                printf("\nInvalid choice! Try again.\n");
                getch();
        }
    } while(choice != 6);
    
    getch();
}



FCFS SJF

#include <stdio.h>
#include <conio.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
};

void fcfs(void) {
    struct Process p[10];
    int n, i, j;
    float avg_tat = 0.0f, avg_wt = 0.0f;
    struct Process temp;

    clrscr();
    printf("\n\t\t*** FCFS SCHEDULING ***\n\n");

    do {
        printf("Enter number of processes (1-10): ");
        scanf("%d", &n);
    } while(n < 1 || n > 10);

    for(i = 0; i < n; i++) {
        printf("\nProcess %d:\n", i + 1);
        p[i].pid = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);
        printf("Burst Time: ");
        scanf("%d", &p[i].burst);
    }

    /* sort by arrival time (bubble) */
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(p[j].arrival > p[j+1].arrival) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    p[0].completion = p[0].arrival + p[0].burst;
    p[0].turnaround = p[0].completion - p[0].arrival;
    p[0].waiting = p[0].turnaround - p[0].burst;

    for(i = 1; i < n; i++) {
        if(p[i].arrival > p[i-1].completion)
            p[i].completion = p[i].arrival + p[i].burst;
        else
            p[i].completion = p[i-1].completion + p[i].burst;

        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
    }

    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    printf("-----------------------------------------------\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival, p[i].burst,
               p[i].completion, p[i].turnaround, p[i].waiting);
        avg_tat += p[i].turnaround;
        avg_wt += p[i].waiting;
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("\nAverage Turnaround Time: %.2f", avg_tat);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);

    printf("\nPress any key to return to menu...");
    getch();
}

void sjf(void) {
    struct Process p[10];
    int n, i, completed = 0, current_time = 0;
    int min_idx, min_burst;
    int is_completed[10];
    float avg_tat = 0.0f, avg_wt = 0.0f;

    clrscr();
    printf("\n\t\t*** SJF SCHEDULING (Non-preemptive) ***\n\n");

    do {
        printf("Enter number of processes (1-10): ");
        scanf("%d", &n);
    } while(n < 1 || n > 10);

    for(i = 0; i < n; i++) {
        printf("\nProcess %d:\n", i + 1);
        p[i].pid = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);
        printf("Burst Time: ");
        scanf("%d", &p[i].burst);
        is_completed[i] = 0;
    }

    while(completed != n) {
        min_idx = -1;
        min_burst = 32767; /* large */

        for(i = 0; i < n; i++) {
            if(p[i].arrival <= current_time && is_completed[i] == 0) {
                if(p[i].burst < min_burst) {
                    min_burst = p[i].burst;
                    min_idx = i;
                } else if(p[i].burst == min_burst) {
                    /* tie-break by earlier arrival */
                    if(min_idx == -1 || p[i].arrival < p[min_idx].arrival)
                        min_idx = i;
                }
            }
        }

        if(min_idx == -1) {
            current_time++;
        } else {
            p[min_idx].completion = current_time + p[min_idx].burst;
            p[min_idx].turnaround = p[min_idx].completion - p[min_idx].arrival;
            p[min_idx].waiting = p[min_idx].turnaround - p[min_idx].burst;

            current_time = p[min_idx].completion;
            is_completed[min_idx] = 1;
            completed++;
        }
    }

    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    printf("-----------------------------------------------\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival, p[i].burst,
               p[i].completion, p[i].turnaround, p[i].waiting);
        avg_tat += p[i].turnaround;
        avg_wt += p[i].waiting;
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("\nAverage Turnaround Time: %.2f", avg_tat);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);

    printf("\nPress any key to return to menu...");
    getch();
}

void main(void) {
    int choice;
    clrscr();

    do {
        clrscr();
        printf("\n\t*** CPU SCHEDULING ALGORITHMS ***\n");
        printf("\n1. FCFS (First Come First Serve)");
        printf("\n2. SJF (Shortest Job First)");
        printf("\n3. Exit");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: fcfs(); break;
            case 2: sjf(); break;
            case 3: printf("\nExiting...\n"); break;
            default: printf("\nInvalid choice! Try again.\n"); getch();
        }
    } while(choice != 3);

    /* Turbo C doesn't require return in void main */
}
