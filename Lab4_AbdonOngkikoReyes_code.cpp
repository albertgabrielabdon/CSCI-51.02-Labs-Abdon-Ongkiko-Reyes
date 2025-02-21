#include <iostream>
using namespace std;


int shlmul(int x, int y){
    int product = 0;
    int count = 0;
    bool isNegative = (x < 0) ^ (y < 0); //true if one is negative but not both (XOR)

    x = abs(x);
    y = abs(y);

    while (y) {
        if (y % 2 == 1)              // check if rightmost bit of y is 1
            product += x << count;   // add (x << 2^count) to product

        count++;
        y /= 2;                     //equivalent of shifting y right by 1
    }

    if (isNegative)
        return -(product);
    
    return product;
}

int main() {
    cout << shlmul(86, 45) << endl; //3870
    cout << shlmul(5, -83) << endl; // -415
    cout << shlmul(-24, -61) << endl; // 1464
    cout << shlmul(-55, 5) << endl; // -275
    cout << shlmul(42, 0) << endl; // 0
}
