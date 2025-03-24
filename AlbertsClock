#include <iostream>
#include <ctime>
#include <cstdio>
#include <unistd.h> 
using namespace std;

int main(void) {
    int id = getpid(); 
    cout << "This process' ID is: " << id << endl;

    int count = 1;
    time_t rawtime;
    tm* timeinfo;
    char buffer [80];
    // https://stackoverflow.com/questions/5438482/getting-the-current-time-as-a-yyyy-mm-dd-hh-mm-ss-string

    if (fork() == 0) {
        execl("/Users/albertgabrielabdon/Desktop/temporary clean up/practice C++/xclock",
              "myXclock", NULL);
        exit(1);
    }

    while (true) {
        if (count > 0 && count % 3 == 0) { 
            cout << "\"This program has gone on for far too long. Type Ctrl+C to abort this timer application.\"" << endl;
        }

        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer, 80, "[%Y-%m-%d] %H:%M:%S", timeinfo);
        puts(buffer);

        sleep(10);
        count++;
    }

    return 0;
}
