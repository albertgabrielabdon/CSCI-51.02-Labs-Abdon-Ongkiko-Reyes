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
