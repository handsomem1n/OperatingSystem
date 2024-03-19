#include <iostream>
#include <unistd.h>   // fork(), getpid(), execvp()
#include <cstdlib>    // exit()
#include <cstring>    // strdup()
#include <sys/wait.h> // wait()

using namespace std;

int main(int argc, char *argv[])
{
    cout << "hello world (pid:" << getpid() << ")" << endl;
    int rc = fork(); // fork()를 호출하여 현재 프로세스를 복제합니다. 이 때, 새로 생성된 자식 프로세스는 부모 프로세스의 메모리 복사본을 갖습니다. fork()는 부모 프로세스에게는 자식 프로세스의 PID를, 자식 프로세스에게는 0을 반환합니다. 실패 시 -1을 반환합니다.
    if (rc < 0)
    {
        cerr << "fork failed" << endl;
        exit(1);
    }
    else if (rc == 0)
    {
        cout << "hello, I am child (pid:" << getpid() << ")" << endl;
        char *myargs[3];
        myargs[0] = strdup("wc");
        myargs[1] = strdup("p3.c");
        myargs[2] = NULL;
        execvp(myargs[0], myargs); // execvp() 호출 후의 cout 문은 execvp()가 성공적으로 실행되면 절대 실행되지 않습니다. execvp()가 성공하면 현재 프로세스의 이미지가 새로운 프로그램으로 교체되기 때문입니다.
        cout << "this shouldn't print out" << endl; // 실행되지 않는다. Return해도 이 위치로 오지 않는다.
    }
    else if (rc > 0) // 부모 프로세스는 fork()로부터 자식 프로세스의 PID를 양수로 반환받습니다.
    {
        int wc = wait(NULL); // wait(NULL)을 호출하여 자식 프로세스의 종료를 기다립니다. 이 함수는 자식 프로세스가 종료될 때까지 부모 프로세스를 블록(대기) 상태로 만듭니다.
        cout << "hello, I am parent of " << rc << "(wc : " << wc << ")"
             << "(pid:" << getpid() << ")" << endl;
    }
    return 0;
}
