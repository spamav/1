/* BANKER'S ALGORITHM IN C (Turbo C++ Compatible) */

#include <stdio.h>
#include <conio.h>

#define MAX_P 10    /* Maximum number of processes */
#define MAX_R 10    /* Maximum number of resource types */

int main()
{
    int n, m;                       /* n = processes, m = resources   */
    int alloc[MAX_P][MAX_R];        /* Allocation matrix              */
    int max[MAX_P][MAX_R];          /* Maximum demand matrix          */
    int need[MAX_P][MAX_R];         /* Need matrix                    */
    int avail[MAX_R];               /* Available resources            */
    int finish[MAX_P];              /* Finish array                   */
    int safeSeq[MAX_P];             /* Safe sequence                  */

    int i, j, k;
    int count = 0;
    int found;

    clrscr();

    printf("BANKER'S ALGORITHM\n");
    printf("-------------------\n");

    /* INPUT NUMBER OF PROCESSES AND RESOURCES */
    printf("Enter number of processes (<= %d): ", MAX_P);
    scanf("%d", &n);

    printf("Enter number of resource types (<= %d): ", MAX_R);
    scanf("%d", &m);

    /* INPUT ALLOCATION MATRIX */
    printf("\nEnter Allocation matrix (%d x %d):\n", n, m);
    for (i = 0; i < n; i++)
    {
        printf("Process P%d:\n", i);
        for (j = 0; j < m; j++)
        {
            printf("  Allocation of resource R%d: ", j);
            scanf("%d", &alloc[i][j]);
        }
    }

    /* INPUT MAXIMUM MATRIX */
    printf("\nEnter Maximum matrix (%d x %d):\n", n, m);
    for (i = 0; i < n; i++)
    {
        printf("Process P%d:\n", i);
        for (j = 0; j < m; j++)
        {
            printf("  Maximum demand of resource R%d: ", j);
            scanf("%d", &max[i][j]);
        }
    }

    /* INPUT AVAILABLE RESOURCES */
    printf("\nEnter Available resources (for each of %d resource types):\n", m);
    for (j = 0; j < m; j++)
    {
        printf("Available units of resource R%d: ", j);
        scanf("%d", &avail[j]);
    }

    /* CALCULATE NEED MATRIX = MAX - ALLOC */
    printf("\nCalculating NEED matrix (NEED = MAX - ALLOCATION)...\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    /* INITIALIZE FINISH ARRAY */
    for (i = 0; i < n; i++)
    {
        finish[i] = 0;
    }

    /* BANKER'S SAFETY ALGORITHM */
    while (count < n)
    {
        found = 0;

        for (i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                /* Check if need[i][j] <= avail[j] for all j */
                int canAllocate = 1;

                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        canAllocate = 0;
                        break;
                    }
                }

                /* If this process can be allocated safely */
                if (canAllocate == 1)
                {
                    /* Add this process to safe sequence */
                    safeSeq[count] = i;
                    count++;

                    /* Release its resources to avail (simulating completion) */
                    for (k = 0; k < m; k++)
                    {
                        avail[k] = avail[k] + alloc[i][k];
                    }

                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        /* If no process was found in this loop, system is not in safe state */
        if (found == 0)
        {
            break;
        }
    }

    /* CHECK IF ALL PROCESSES COULD FINISH */
    if (count == n)
    {
        int x;
        printf("\nSystem is in a SAFE STATE.\n");
        printf("Safe Sequence: ");
        for (x = 0; x < n; x++)
        {
            printf("P%d", safeSeq[x]);
            if (x != n - 1)
                printf(" -> ");
        }
        printf("\n");
    }
    else
    {
        printf("\nSystem is NOT in a safe state (no safe sequence exists).\n");
    }

    printf("\nPress any key to exit...");
    getch();
    return 0;
}


/* PRODUCER–CONSUMER USING POSIX SEMAPHORES (UNIX / LINUX)
   Compile on Linux:  gcc producer_consumer.c -o pc -pthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>   /* for sleep() */

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;    /* index for next produced item  */
int out = 0;   /* index for next consumed item  */

sem_t empty;   /* counts empty slots in buffer  */
sem_t full;    /* counts filled slots in buffer */
pthread_mutex_t mutex;  /* protects critical section */

void *producer(void *arg)
{
    int item = 0;

    while (1)
    {
        item++;   /* produce next item */

        /* wait for at least one empty slot */
        sem_wait(&empty);

        /* enter critical section */
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producer produced %d at index %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        /* leave critical section */
        pthread_mutex_unlock(&mutex);

        /* one more full slot */
        sem_post(&full);

        sleep(1); /* slow down a bit */
    }

    return NULL;
}

void *consumer(void *arg)
{
    int item;

    while (1)
    {
        /* wait for at least one full slot */
        sem_wait(&full);

        /* enter critical section */
        pthread_mutex_lock(&mutex);

        item = buffer[out];
        printf("Consumer consumed %d from index %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        /* leave critical section */
        pthread_mutex_unlock(&mutex);

        /* one more empty slot */
        sem_post(&empty);

        sleep(2); /* slow down a bit */
    }

    return NULL;
}

int main()
{
    pthread_t prod_thread, cons_thread;

    /* initialize semaphores */
    sem_init(&empty, 0, BUFFER_SIZE);   /* all slots empty at start    */
    sem_init(&full, 0, 0);              /* no full slots at the start  */

    /* initialize mutex */
    pthread_mutex_init(&mutex, NULL);

    /* create producer and consumer threads */
    if (pthread_create(&prod_thread, NULL, producer, NULL) != 0)
    {
        perror(oss"Failed to create producer thread");
        exit(1);
    }

    if (pthread_create(&cons_thread, NULL, consumer, NULL) != 0)
    {
        perror("Failed to create consumer thread");
        exit(1);
    }

    /* wait for threads (in this infinite example, they never end) */
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    /* cleanup (not actually reached here) */
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
