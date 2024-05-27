sem_t s;

void *child(void *arg) {
    printf("child\n");
    sem_post(&s); // signal 전달 == 자식 동작 끝
    return NULL;
}

int main(int argc, char *argv[]){
    sem_init(&s, 0, 0);
    printf("parent : begin\n");
    pthread_t c;
    pthread_create(c, NULL, child, NULL);
    sem_wait(&s); // 자식을 여기서 대기
    printf("parent : end\n");
    return 0;
}

