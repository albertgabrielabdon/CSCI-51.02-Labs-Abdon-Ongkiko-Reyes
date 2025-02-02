#include <iostream>
#include <string>
#include "IntStack.hpp" //note: use " and not "
using namespace std;

int main( void ) {
   
    IntStack stack;
    stack.push(1);
    cout << "pushed 1" << endl;
    stack.push(2);
    cout << "pushed 2" << endl;
    stack.push(3);
    cout << "pushed 3" << endl;

    stack.pop();
    stack.pop();

    //cout << stack. << endl;
    return 0;
}