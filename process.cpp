#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main()
{
	pid_t childID;

	// after creating a new process, the new process will start executing.
	// after end execution of the new process, will `fork()` return address of the new process to the parent process.
	childID = fork(); // new process, its entry point will start form here.

	if (childID == 0)
	{
		cout << "I am the child process" << endl;
	}
	else
	{
		cout
			<< "Hello from file.cpp" << endl;
		cout << "I am in " << get_current_dir_name() << endl;
	}
}