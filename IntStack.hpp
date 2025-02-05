#include <iostream>
#include "IntNode.hpp" //note: use " and not "
using namespace std;

struct IntStack{

	IntNode* top;

  IntStack() {
    top = nullptr;
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
    newNode->next = top;
    top = newNode;
    cout << "added a node with data " << v << endl;
  }
  
  // show all items
  void peek() {   
    if (top == nullptr) {
        cout << "stack is empty" << endl;
    }

    else {
        cout << "list of data in stack (starting from the top):" << endl;
        IntNode* currentNode = top;
        while (currentNode != nullptr) {
            cout << currentNode->data << endl;
            currentNode = currentNode->next;
        }
    }
  }

};
