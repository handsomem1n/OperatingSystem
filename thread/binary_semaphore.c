sem_t m;
sem_init(&m, 0, 1); // semaphore의 초기값은 항상1이어야만 함.
sem_wait(&m);
// cs 영역 부분은 여기에 배치
sem_post(&m);

