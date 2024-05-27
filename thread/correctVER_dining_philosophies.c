void getforks(){
    if (p == 4){
        sem_wait(forks[right(p)]);
        sem_wait(forks[left(p)]);
    }
    else{
        sem_wait(forks[left(p)]);
        sem_wait(forks[right(p)]);
    }
}

