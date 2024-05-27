int buffer[max]; // 데이터를 저장할 버퍼 배열
int fill_ptr = 0; // buffer에 데이터를 넣을 위치를 가리킴
int use_ptr = 0; // buffer에서 데이터를 꺼낼 위치를 가리킴
int count = 0; // buffer에 현재 저장된 데이터의 갯수를 나타냄

void put(int value){
    buffer[fill_ptr] = value; // buffer에 넣을 위치에 value 넣기
    fill_ptr = (fill_ptr + 1) % max; /*
    원형 버퍼이므로 % max를 사용하여 범위를 초과하지 않도록*/
    count++; // 추가되었으니 count값 증가
}

int get(){
    int tmp = buffer[use_ptr];
    use_ptr = (use_ptr + 1) % max;
    count--;
    return tmp;
}

cond_t empty; // 버퍼가 비었을 때를 기다리는 조건 변수
cont_t fill; // 버퍼가 찼을 때를 기다리는 조건 변수
mutex_t mutex; // 버퍼 접근을 동기화하기 위한 뮤텍스

void *producer(void *arg){
    int i;
    for (i = 0; i < loops; i++){
        Pthread_mutex_lock(&mutex);
        while (count == max) 
            Pthread_cond_wait(&empty, &mutex); // buffer가 꽉찼을 경우
        put(i); // buffer가 꽉차지 않았을 경우 put
        Pthread_cond_signal(&fill); /*
        데이터를 넣은 후 fill 조건 변수를 signal()-> customer에게 알림 */ 
        Pthread_mutex_unlock(&mutex);
    }
}

void *consumer(void *arg){
    int i;
    for (i = 0; i < loops; i++){
        Pthread_mutex_lock(&mutex);
        while (count == 0) 
            Pthread_cond_wait(&fill, &mutex);/*
            buffer가 비었으므로 fill 조건 변수를 기다림*/
        int tmp = get();
        Pthread_cond_signal(&empty); /*
        empty 조건 변수를 signal하여 producer에게 알림*/
        Pthread_mutex_unlock(&mutex);
        print("%d\n", tmp);
    }
}

