#include <semaphore.h>
sem_t s; // 세마포어 생성
sem_init(&s, 0, 1); /*
인자 :
1. 생성할 semaphore
2. process 내의 thread 간 semaphore 공유 여부
3. semaphore init값)*/ 

