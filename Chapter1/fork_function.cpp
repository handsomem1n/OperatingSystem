#include <iostream>
#include <unistd.h> // For getpid() and fork()
#include <cstdlib>  // For exit()

using namespace std;

int main()
{
    cout << "hello world (pid:" << getpid() << ") \n";
    int rc = fork();
    if (rc < 0)
    {
        cerr << "fork failed \n";
        exit(1);
    }
    else if (rc == 0)
    {
        cout << "hello, I am child (pid:" << getpid() << ")\n";
    }
    else if (rc > 0)
    {
        cout << "hello, I am parent of " << rc << " (pid:" << getpid() << ")\n";
    }
    return 0;
}
