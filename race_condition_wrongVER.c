#include <stdio.h>
#include <stddef.h>
#include <stdatomic.h> // Un-comment this to use atomic functions
#include <pthread.h>

static volatile int counter = 0; // Change to atomic_int
#define loop 4

void *workerA(void *arg)
{
    int i;
    for (i = 0; i < loop; i++)
    {
        counter = counter + 2; // This is still non-atomic, consider using atomic operations if needed
        // atomic_fetch_add(&counter, 2);
    }
    return NULL;
}

void *workerB(void *arg)
{
    int i;
    for (i = 0; i< loop; i++)
    {
        // atomic_fetch_add(&counter, 1); // Use atomic_fetch_add for atomic increment
        counter = counter + 1;
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t T1;

    pthread_create(&T1, NULL, workerB, NULL);
    workerA(NULL);
    pthread_join(T1, NULL);
    printf("counter = %d\n", counter);
    return 0;
}
