#include <iostream>
#include <thread>

using namespace std;

void threadFunction()
{
    cout << "Hello from thread!" << endl;
    this_thread::sleep_for(1s);
}

int main()
{
    thread t(threadFunction); // t object from thread class, allocated in the **stack**.
    cout << "Hello from main!" << endl;

    t.join(); // wait for the thread to finish.

    return 0;
}