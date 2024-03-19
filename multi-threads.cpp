#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
using namespace std;

// To Run in command line
//  g++ <file>.cpp −lpthread −o <output_file>

// Calculate the Partial Sum in Page (95) of the book.

void partial_sum(vector<double>::iterator start, vector<double>::iterator end, double *reducerVal)
{
    printf("StartVariable = %f,\n EndVariable = %f\n", *start, *end);
    // Reset before refit - not neccessary some cases
    *reducerVal = 0;

    for (auto elm = start; elm < end; elm++)
    {
        *reducerVal += *elm;
    }

    printf("Reducer Value = %f", *reducerVal);

    /**
     * Threads usually not pure function, it is affect to global environment!
     */
}

int main(int argc, char **argv)
{
    int numberOfThreads = atoi(argv[1]); // atoi() converts a string to an integer.
    thread *threads[numberOfThreads];    // elements of array t are pointers to thread objects.

    int numberOfElementsArray = atoi(argv[2]);
    vector<double> data(numberOfElementsArray); // elements can be entered are "doubles"

    for (int i = 0; i < data.size(); i++)
    {
        cin >> data[i];
    }

    // Steps
    int steps = (int)ceil(numberOfElementsArray * 1.0 / numberOfThreads); // this variable tracks how partials sum should be calculated per thread.
    /**
     * for example
     * we have 100 elements in the array, and we have 4 threads.
     * so, each thread should calculate 25 elements. (0-24, 25-49, 50-74, 75-99)
     */

    // DEBUG
    printf("Number of Threads = %d\nNumber of Elements in Array = %d\nSteps to calculate = %d\n", numberOfThreads, numberOfElementsArray, steps);

    double outlet[numberOfThreads] = {0.0}; // المصب الي بيتحط فيه نتايج كل thread - `reducer`

    // Iterate over the threads
    // to track the calculated elements of array, we need to use the following variables.
    vector<double>::iterator localStart = data.begin(); // iterator to the start of the array.
    vector<double>::iterator localEnd;                  // should be changed in each iteration.
    // 0-24, 25-49, 50-74, 75-99

    // Loop through the threads
    for (int i = 0; i < numberOfThreads; i++)
    {
        localEnd = localStart + steps;

        if (i == numberOfThreads - 1) // if i == last_thread_element: do
            localEnd = data.end();    // override to solve error (out-of-range)

        threads[i] = new thread(partial_sum, localStart, localEnd, &outlet[i]);

        // up-change localStart
        localStart += steps; // 25-...
    }

    double total = 0;

    for (int i = 0; i < numberOfThreads; i++)
    {
        threads[i]->join(); // or (*threads[i]).join()
        delete threads[i];

        total += outlet[i]; // outlet now has value, came from partial_sum.
    }

    printf("The Average is = %f", (total / numberOfElementsArray));
    return 0;
}

// INPUT: 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10