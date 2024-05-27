#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
// #include "common.h" // 
#include <unistd.h>

using namespace std;

int main (int argc, char *argv []){
    if (argc !=2) {
        cerr << " usage : cpu <string>" << endl;
        return 1;
    }
    char *str = argv[1];
    while(1){
        // spin(1); // spin() 함수는 선언되어 있지만 정의되어 있지 않습니다. 이 함수가 외부 파일에 정의되어 있다고 가정합니다.
        sleep(1);
        cout << str << endl;
    }
    return 0;
}

/*
g++ -o cpu cpu.cpp       
(base) newuser@happyguy-2 1단원 % ./cpu hello
hello
hello
hello
hello
hello
hello

*/ 