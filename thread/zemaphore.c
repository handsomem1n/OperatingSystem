typedef struct _ _zem_t{
    int value; // semaphore의 값
    pthread_cond_t cond; // 특정 조건이 만족될 때까지 thread를 대기 상태로 두기 위해
    pthread_mutex_t lock; // CS 구역을 보호하기 위해
} zem_t;

// 오직 하나의 thread만이 이 문장 호출 可
void zem_init(zem_t *zema, int value){
    zema->value = value; // semaphore의 초기값
    cond_init(&zema->cond);
    mutex_init(&zema->lock);
}

void zem_wait(zem_t *zema){
    mutex_lock(&zema->lock);
    while (s->value <= 0) // sema의 값이 0이하일 때 까지
        cond_wait(&zema->cond, &zema->lock); // 대기
    zema->value--;
    mutex_unlock(&zema->lock);
}

void zem_post(zem_t *zema){
    mutex_lock(&zema->lock); // 뮤텍스 잠금
    zema->value++;
    cond_signal(&zema->cond); // 조건 변수 신호
    mutex_unlock(&zema->lock); // // 뮤텍스 해제
}

