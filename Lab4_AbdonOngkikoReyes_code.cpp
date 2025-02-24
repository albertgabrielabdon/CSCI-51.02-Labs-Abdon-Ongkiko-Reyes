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
using namespace std;

int shlmul(int x, int y){
    int product = 0;
    int count = 0;
    bool isNegative = (x < 0) ^ (y < 0);

    x = abs(x);
    y = abs(y);

    while (y) {
        if (y & 1) {
            product += x << count;
        }
        count ++;
        y = y >> 1;
    }

    if (isNegative)
        return -(product);
    
    return product;
}

int main() {
    int x;
    int y;
    cout << "Multiply two numbers optimally!" <<endl;
    cout << "First number: ";
    cin >> x;
    cout << "Last number: ";
    cin >> y;
    cout << "Their product is " << shlmul(x, y) << endl;
}
