/*
 fork()는 반환값을 가지는데, 그 반환값으로는 부모 프로세스는 자식의 PID값을 반환받게 되고, 자식 프로세스는 0을 반환받게 된다. 그렇다면 자식과 부모의 rc의 값은 서로 다르게 되는 것이고 이걸 이용하여 설계한다.
*/
#include <stdio.h> // <stdio.h>: 표준 입출력 함수를 사용하기 위한 헤더 파일입니다. (c++에서 iostream과 같음)
#include <stdlib.h> // <stdlib.h>: 일반 유틸리티 함수들, 예를 들어 exit() 함수를 사용하기 위한 헤더 파일입니다. (c++에서 cstdlib과 같음)
#include <unistd.h> // 유닉스 스탠다드(symbolic constants, types, and functions)를 제공하는 헤더 파일입니다. 여기서는 getpid() 및 fork() 함수를 사용하기 위해 필요합니다.

int main (int argc, char *argv[]) {
    printf("hello world (pid:%d) \n", (int) getpid()); // 부모 프로세스의 프로세스 ID(pid)를 출력합니다. getpid() 함수는 현재 프로세스의 ID를 반환합니다.
    int rc = fork(); // 현재 프로세스의 복사본을 생성합니다. 이때 생성된 프로세스를 자식 프로세스라고 합니다. fork() 함수는 부모 프로세스에서는 자식 프로세스의 pid를 반환하고, 자식 프로세스에서는 0을 반환합니다. 실패할 경우에는 -1을 반환합니다.
    if (rc <0) { // 오류 처리: fork()의 반환 값이 -1이면, fork() 호출이 실패했음을 의미하고, 오류 메시지를 출력한 후 프로그램을 종료합니다.
        fprintf(stderr, "fork failed \n");
        exit(1);
    }
    else if (rc ==0) { // fork()의 반환 값이 0이면 현재 코드 실행부는 자식 프로세스 내에서 실행되고 있음을 의미합니다. 이 경우, 자식 프로세스의 pid를 출력합니다.
        printf("hello I am child (pid:%d)\n", (int) getpid());
    }
    else if (rc > 0){ // fork()에서 반환된 값이 0보다 크면 현재 코드 실행부는 부모 프로세스 내에서 실행되고 있음을 의미합니다. 이 경우, 자식 프로세스의 pid와 부모 프로세스 자신의 pid를 출력합니다.
        printf("hello, I am parent of %d (pid:%d)\n", rc, (int) getpid());
    }
    return 0;
}

// 이 프로그램은 fork()를 사용하여 부모 프로세스와 자식 프로세스를 생성하고, 각 프로세스가 자신의 프로세스 ID와 부모 프로세스의 경우 자식 프로세스의 ID를 출력하게 합니다. 프로세스 생성에 실패한 경우에는 오류 메시지를 출력하고 프로그램을 종료합니다.