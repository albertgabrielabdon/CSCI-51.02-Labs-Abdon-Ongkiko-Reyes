#include <iostream>
#include <string>
#include <list>
#include "IntNode.hpp" //note: use " and not "
using namespace std;

struct IntStack{

	IntNode* topStack;

    void pop(){
        int toRemove = (*topStack).currentNode;
        topStack = (*topStack).nextNode; //error here
        //./IntStack.hpp:15:36: error: member reference base type 'int' is not a structure or union
        cout << "removed value: " << toRemove << endl;

    }

    void push(int v){
        IntNode* node = new IntNode(v);
        (*node).nextNode = topStack;
        topStack = node;

    }

};
