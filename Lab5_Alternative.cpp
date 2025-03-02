#include <iostream>
#include <cmath>
using namespace std;

struct Point3D{	
    int x;
    int y;
    int z;
};

int manhattan_distance(Point3D p1, Point3D p2) {
    int out;
    out = abs(p1.x - p2.x) + abs(p1.y - p2.y) + abs(p1.z - p2.z);
    return out;
}

int main(void) {

    int T;
    int N;
    cout << "Number of test cases: " << endl;
    cin >> T;

    for(int i = 0; T > i; i++){
        cout << "Number of points " << endl;
        cin >> N;

        Point3D points[N];
        for(int j = 0; N > j; j++){
            cout << "coords: " << endl;
            cin >> points[j].x >> points[j].y >> points[j].z;
        }
        
        for (int k = 0; (N-1) > k; k++){
            cout << manhattan_distance(points[k], points[k+1]) << endl;
        }
    }

    return 0;
}
