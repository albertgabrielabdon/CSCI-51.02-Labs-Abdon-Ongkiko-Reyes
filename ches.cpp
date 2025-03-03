/*
 * I hereby attest to the truth of the following facts:
 *
 * I have not discussed the C++ code in my program with anyone
 * other than my instructor or the teaching assistants assigned to this course.
 * 
 * I have not used C++ code obtained from another student, or
 * any other unauthorized source, whether modified or unmodified.
 *
 * If any C++ code or documentation used in my program was
 * obtained from another source, it has been clearly noted with citations in the
 * comments of my program.
*/

#include <iostream>
#include <cmath>
using namespace std;

int caseAmt = 0;
int pointAmt = 0;
int i = 0;
int j = 0;
int mDistance;

struct Point {
  int x, y, z;
  Point() {
    x = 0;
    y = 0;
    z = 0;
  }
  Point(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }
};

int main(void) {
  cin >> caseAmt;
  while (i < caseAmt) {
    cin >> pointAmt;
    Point* points = new Point[pointAmt];
    int answers[pointAmt-1];
    j = 0;
    while (j < pointAmt) {
      int x, y, z;
      cin >> x >> y >> z;
      points[j] = Point(x, y, z);
      if (j > 0) {
        Point* point1 = &points[j];
        Point* point2 = &points[j-1];
        mDistance = abs(point1->x - point2->x) + abs(point1->y - point2->y) + abs(point1->z - point2->z);
        answers[j-1] = mDistance;
      }
      j++;
    }
    for (int answer : answers) {
      cout << answer << endl;
    }
    if (i < caseAmt-1) {
      cout << endl;
    }
    delete[] points;
    i++;
  }
}
