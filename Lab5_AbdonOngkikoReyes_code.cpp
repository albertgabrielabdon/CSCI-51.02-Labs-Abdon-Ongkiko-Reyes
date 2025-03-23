#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {
        int N;
        cin >> N;
        int arr[N-1];

        int ax, ay, az, bx, by, bz;
        cin >> ax >> ay >> az;

        for (int i = 0; i < N-1; i++) {
            cin >> bx >> by >> bz;
            int distance = abs(ax - bx) +
                           abs(ay - by) +
                           abs(az - bz);
            arr[i] = distance;
            ax = bx;
            ay = by;
            az = bz;
        }

        for (int i = 0; i < N-1; i++) {
          cout << arr[i] << endl;
        }

        if (i < T - 1) {
            cout << endl;
        }
    }   
    return 0;
}
