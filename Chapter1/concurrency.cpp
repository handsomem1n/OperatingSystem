#include <iostream>
#include <cstdlib>

using namespace std;

volatile int counter = 0;
int loops;

void *worker(void *arg){
    for ( int i = 0 ; i < loops ; i++){
        counter ++;
    }
    return NULL;
}

int main (int argc, char *argv[]){
    if (argc !=2) {
        cerr << "usage : threads <value>" << endl;
        exit(1);
    }
    loops = atoi(argv[1]);
    pthread_t p1, p2;
    cout << "Initial value :" << counter << endl;

    Pthread_create(&p1, NULL, worker, NULL);
    Pthread_create(&p2, NULL, worker, NULL);
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
    cout << "Final value : " << counter << endl;

}
