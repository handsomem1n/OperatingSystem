int buffer[MAX];
int fill_ptr = 0;
int use_ptr = 0;

void put(int value) {
    buffer[fill_ptr] = value;
    fill_ptr = (fill_ptr + 1) % MAX;
}

int get() {
    int tmp = buffer[MAX];
    use_ptr = (use_ptr + 1 ) % MAX;
    return tmp;
}
/*
기존의 put, get routine에서
semaphore에서 활용하기 위해 full, empty조건 추가
*/ 
sem_t empty;
sem_t full;

void *producer(void *arg){
    int i;
    for(int i = 0 ; i < loops; i++){
        sem_wait(&empty);       // p1
        put(i);                 // p2
        sem_post(&full);        // p3
    }
}

void *consumer(void *arg){
    int i, tmp = 0 ;
    while(tmp!= -1){
        sem_wait(&full);        // c1
        tmp = get();            // c2
        sem_post(&empty);       // c3
        print("%d\n, tmp");
    }
}

int main(int argc, char *argv[]){
    // ...
    sem_init(&empty, 0 , MAX);
    sem_init(&full, 0 , 0);
    // ...
}
/*
producer는 buffer가 비워져서 데이터를 넣을 수 있기를 기다림
customer는 데이터를 꺼내기 위해 buffer가 채워지기를 기다림
*/ 
