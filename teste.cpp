#include <sys/time.h>
#include <iostream>

using namespace std;

int main() {
    timeval tv;
    // gettimeofday(&tv, 0);

    cout << tv << endl;
    return 0;
}