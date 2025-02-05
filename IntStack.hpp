#include <iostream>
#include "IntNode.hpp" //note: use " and not "
using namespace std;

struct IntStack{

	IntNode* top;
    
  // remove a node
  void pop(){
      IntNode* newTop = top->next;
      delete top;
      top = newTop;
      cout << "removed a node" << endl;
  }
  
  // add a node
  void push(int v) {
      IntNode* newNode = new IntNode(v);
      newNode->next = top;
      top = newNode;
      cout << "added a node with data " << v << endl;
  }
  
  // show all items
  void peek() {
    cout << "list of data in stack (starting from the top):" << endl;
    IntNode* currentNode = top;
    IntNode* nextNode = top->next;
    while (nextNode != nullptr) {
      cout << currentNode->data << endl;
      currentNode = nextNode;
      nextNode = currentNode->next;
    }
  }

};
