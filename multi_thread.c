#include <cstddef>

static volatile int counter = 0;

void *mythread(void *arg) {
    int i;
    printf("%s: begin\n", (char *)arg);
    for (i = 0; i < 1e7; i++) {
        counter = counter + 1;
    }
    printf("%s: done\n", (char *)arg);
    return NULL;
}
int main() {
    pthread_t T1;
    printf("main: begin [counter = %d]\n", counter);
    Pthread_create(&T1, NULL, mythread, "A");
    mythread((void *)"main");
    Pthread_join(T1, NULL);
    printf("main: done\n [counter: %d]\n", counter);
    return 0;
}
