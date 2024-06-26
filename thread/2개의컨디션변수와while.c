cond_t empty, fill;
mutex_t mutex;

void *producer(void *arg){
    int i;
    for (i = 0; i < loops; i++){
        Pthread_mutex_lock(&mutex);
        while (count == 1) // 버퍼가 꽉 차 있는 동안 
            Pthread_cond_wait(&empty, &mutex); // 대기, empty 조건 변수를 기다림
        put(i);
        Pthread_cond_signal(&fill); // signal -> 소비자가 아이템을 소비할 수 있음을 알림
        Pthread_mutex_unlock(&mutex); // // 뮤텍스 잠금 해제
    }
}

void *consumer(void *arg){
    int i;
    for (i = 0; i < loops; i++){
        Pthread_mutex_lock(&mutex);
        while (count == 0)
            Pthread_cond_wait(&fill, &mutex); // // fill 조건 변수를 기다림
        int tmp = get();
        Pthread_cond_signal(&empty); // signal-> 생산자가 아이템을 추가할 수 있음을 알림
        Pthread_mutex_unlock(&mutex);
        printf("%d\n", tmp);
    }
}




