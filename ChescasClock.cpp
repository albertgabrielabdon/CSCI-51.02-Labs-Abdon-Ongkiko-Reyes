#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
using namespace std;

int main(void) {
  if ((fork() == 0) && (execl("/usr/bin/xclock", "myXclock", NULL) == -1)) {
    cout << "Could not open or find the program." << endl;
  }

  // https://www.programiz.com/cpp-programming/library-function/ctime/strftime
  time_t timestamp;
  tm * datetime;
  char output[50];

  int i = 0;

  while (true) {
    time(&timestamp);
    datetime = localtime(&timestamp);
    strftime(output, 50, "%F %T", datetime);

    cout << output << endl;
    i++;

    if (i == 3) {
      cout << "\"This program has gone on for far too long.\"" << endl;
      cout << "\"Type Ctrl+C to abort this timer application.\"" << endl;
      i = 0;
    }

    sleep(10);
  }
}
