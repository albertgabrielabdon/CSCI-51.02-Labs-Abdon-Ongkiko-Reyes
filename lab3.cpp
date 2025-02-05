#include "IntStack.hpp" //note: use " and not "
using namespace std;

int main( void ) {
  IntStack stack;
  
  stack.peek(); // should be empty

  stack.push(1);
  stack.push(2);
  stack.push(3);
  stack.peek(); // should have 3, 2, and 1

  stack.pop();
  stack.pop();
  stack.push(4);
  stack.peek(); // should have 4 and 1

  stack.pop();
  stack.peek(); // should have 1

  stack.pop();
  stack.pop(); // should not allow pop
  stack.peek(); // should be empty

  stack.push(1);
  stack.peek(); // should have 1

  return 0;
}
