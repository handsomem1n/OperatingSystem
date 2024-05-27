// List의 경우, insert와 lookup의 작업 中 insert 연산이 없다는 보장이 된다면, 다수의 lookup작업을 동시에 수행할 수 있다.
typedef struct _rwlock_t{
    sem_t lock;
    sem_t writelock;
    int readers; // 읽기 중인 thread 수
} rwlock_t;

void rwlock_init(rwlock_t *rw){
    rw -> readers = 0;
    sem_init(&rw->lock, 0, 1);
    sem_init(&rw->writelock, 0, 1);
}

// for readlock 획득
void rwlock_acquire_readlock(rwlock_t *rw){
    sem_wait(&rw->lock);
    rw->readers++;
    if (rw->readers == 1) // 첫 번째 읽기 작업이 시작되면
        sem_wait(&rw->writelock); // writelock 세마포어 대기 -> 쓰기 작업이 진행되지 않도록
    sem_post(&rw->lock);
}

// for readlock 해제
void rwlock_release_readlock(rwlock_t *rw){
    sem_wait(&rw->lock);
    rw->readers--;
    if (rw->readers == 0) // 마지막 읽기 작업이 끝나면
        sem_post(&rw->writelock); // 이제 쓰기 작업이 가능하다
    sem_post(&rw->lock);
}

// for writelock 획득
void rwlock_acquire_writelock(rwlock_t *rw){
    sem_wait(&rw->writelock); // 쓰기 작업은 단독으로 수행되어야 하므로, writelock 세마포어를 대기
}

// for writelock 해제
void rwlock_release_writelock(rwlock_t *rw){
    sem_post(&rw->writelock); // 쓰기 작업이 끝나면 writelock 세마포어를 해제
}

