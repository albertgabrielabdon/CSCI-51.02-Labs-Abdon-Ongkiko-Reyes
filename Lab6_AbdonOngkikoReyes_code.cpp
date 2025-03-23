#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
using namespace std;

int main(void) {
  pid_t forkRet = fork();

  if (forkRet == 0) {
    if (execl("/usr/bin/xclock", "myXclock", NULL) == -1) {
      cout << "Could not open or find the program." << endl;
    }
  }

  time_t timestamp;
  tm * datetime;
  char output[50];

  time(&timestamp);
  datetime = localtime(&timestamp);
  
  // [yyyy-mm-dd] hh:mm:ss
  strftime(output, 50, "%F %T", datetime);

  int i = 0;

  while (true) {
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
