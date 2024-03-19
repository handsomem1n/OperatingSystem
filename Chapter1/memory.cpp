#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <sys/time.h>
#include <assert.h>
// #include "common.h" // 
#include <unistd.h>

using namespace std;

int main (int argc, char *argv []){
    int *p = new int;
    assert(p!= NULL); // assert() 함수는 조건을 검사하고, 만일 조건이 false로 평가되면 프로그램을 중단시키고 오류 메시지를 출력.
    cout << "(" << "PID : " << getpid() << ", address pointed to by p : " << p << endl;

    *p = 0;
    cout << "*p : " << *p << endl;
    cout << "p : " << p << endl;
    
    while(1){
        // spin(1); // spin() 함수는 선언되어 있지만 정의되어 있지 않음. 교과서에서는 이 함수가 외부 파일에 정의되어 있다고 가정하였는데, 나는 그 가정된 함수와 비슷한 기능을 하는 sleep()를 사용함
        sleep(1);
        *p = *p + 1;
        cout << "(" << getpid() << ") p : " << *p << endl;
    }
    return 0;
}
/*
stack에 p라는 변수가 있을 것이고,*p에는 heap에 할당된 integer의 시작 주소가 있을텐데, 그것이 지금 200000번지가 되겠고, 거기에 integer가 하나 있다.
*/
