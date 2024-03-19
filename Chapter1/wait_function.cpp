#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "hello world (pid:" << getpid() << ")" << endl;
    int rc = fork();
    if (rc < 0)
    {
        cerr << "fork failed" << endl;
        exit(1);
    }
    else if (rc == 0)
    { // rc == 0: 현재 코드가 자식 프로세스에서 실행 중임을 의미. 자식 프로세스의 PID를 출력.
        cout << "hello I am child (pid:" << getpid() << ")" << endl;
    }
    else if (rc > 0)
    { // rc > 0: 이 경우 부모 프로세스에서 실행 중임. 
        int wc = wait(NULL); // 부모 프로세스는 wait(NULL)을 호출하여 자식 프로세스가 종료될 때까지 대기한다. wait()은 종료된 자식 프로세스의 PID를 반환 -> 이로써 이 코드의 출력결과는 항상 동일한 결과를 나타낸다.
        cout << "hello, I am parent of " << rc << " (wc : " << wc << ") "
             << "(pid:" << getpid() << ")" << endl; // 부모는 자신의 PID와 자식 프로세스의 PID(rc), 그리고 wait()에서 반환된 값을 출력.
    }
    return 0;
}

/*
코드의 핵심은 프로세스 생성과 프로세스 간의 통신 방법을 이해하는 것
fork()는 프로세스를 분기시키고, 부모와 자식 프로세스는 fork() 호출 이후의 코드를 병렬로 실행함.
부모 프로세스는 wait()를 사용하여 자식 프로세스의 실행 완료를 기다리며, 이를 통해 자식 프로세스가 완전히 종료된 후에 프로그램이 계속 실행되도록 한다.
*/
