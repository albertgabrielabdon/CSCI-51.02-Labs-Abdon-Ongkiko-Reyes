#include <iostream>
#include <ctime>
#include <cstdio>
#include <unistd.h> 
using namespace std;

int main(void) {
    int count = 1;

    // https://stackoverflow.com/questions/5438482/getting-the-current-time-as-a-yyyy-mm-dd-hh-mm-ss-string
    time_t rawtime;
    tm* timeinfo;
    char buffer [80];

    if (fork() == 0) {
        if (execl("/usr/bin/xclock", "myXclock", NULL) == -1) {
          exit(1);
        }
    }

    while (true) {
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer, 80, "[%Y-%m-%d] %H:%M:%S", timeinfo);
        puts(buffer);

        if (count > 0 && count % 3 == 0) { 
            cout << "\"This program has gone on for far too long. Type Ctrl+C to abort this timer application.\"" << endl;
        }

        sleep(10);
        count++;
    }

    return 0;
}
