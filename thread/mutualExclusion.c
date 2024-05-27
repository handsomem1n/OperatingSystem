sem_t empty;
sem_t full;
sem_t mutex;

void *producer(void *arg){
    int i;
    for (i = 0; i < loops; i++){
        sem_wait(&empty);   // p1
        sem_wait(&mutex);   // p1.5
        put(i);             // p2
        sem_post(&mutex);   // p2.5
        sem_post(&full);    // p3
    }
}

void *consumer(void *arg)
{
    int i;
    for (i = 0; i < loops; i++){
        sem_wait(&full);    // c1
        sem_wait(&mutex);   // c1.5
        int tmp = get();    // c2
        sem_post(&mutex);   // c2.5
        sem_post(&empty);   // c3
        printf("%d\n ", tmp);
    }
}

int main(int argc, char *argv[]){
    // ...
    sem_init(&empty, 0, MAX);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    // ...
}

