#include "IntStack.hpp" //note: use " and not "
using namespace std;

int main( void ) {
  IntStack stack;

  stack.push(1);
  stack.push(2);
  stack.push(3);

  stack.pop();
  stack.pop();
  stack.push(4);

  stack.peek();
  stack.pop();
  stack.peek();

  return 0;
}
