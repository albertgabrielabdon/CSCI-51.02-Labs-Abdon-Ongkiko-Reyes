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

struct IntNode{
	
  int data;
  IntNode* next;

  IntNode() {
    data = 0;  
    next = nullptr;
  }

  IntNode(int v) {
    data = v;
    next = nullptr;
  }

};

struct IntStack{

	IntNode* top;

  IntStack() {
    top = nullptr;
  }

  ~IntStack() {
    if (top != nullptr) {
      cout << "destroying stack..." << endl;
      IntNode* currentNode = top;
      IntNode* nextNode = top->next;
      while (true) {
        cout << "destroyed node with data " << currentNode->data << endl;
        delete currentNode;
        currentNode = nextNode;
        if (currentNode == nullptr) {
          break;
        }
        else {
          nextNode = currentNode->next;
        }
      }
    }
  }
    
  // remove a node
  // if this empties the stack, change top to null
  // if stack is already empty, do not allow pop
  void pop(){
    if (top == nullptr) {
      cout << "tried to remove a node but stack is already empty" << endl;
    }
    else {
      IntNode* newTop = top->next;
      if (newTop == nullptr) {
        delete top;
        top = nullptr;
        cout << "removed a node, stack is now empty" << endl;
      }
      else {
        delete top;
        top = newTop;
        cout << "removed a node" << endl;
      }
    }
  }
  
  // add a node
  // if adding to an empty stack, change next to null
  void push(int v) {
    IntNode* newNode = new IntNode(v);
    if (top == nullptr) {
      newNode->next = nullptr;
    }
    else {
      newNode->next = top;
    }
    top = newNode;
    cout << "added a node with data " << v << endl;
  }
  
  // show all items
  void peek() {
    cout << "list of data in stack (starting from the top):" << endl;
    if (top == nullptr) {
      cout << "stack is empty" << endl;
    }
    else {
      IntNode* currentNode = top;
      IntNode* nextNode = top->next;
      while (true) {
        cout << currentNode->data << endl;
        currentNode = nextNode;
        if (currentNode == nullptr) {
          break;
        }
        else {
          nextNode = currentNode->next;
        }
      }
    }
  }

};

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
  stack.push(2);
  stack.push(3);
  stack.peek(); // should have 1

  return 0;
}
