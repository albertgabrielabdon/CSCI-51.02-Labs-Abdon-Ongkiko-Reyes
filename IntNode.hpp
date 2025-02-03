struct IntNode{
	
	public:
	int currentNode;
	IntNode* nextNode;

    IntNode(int cN){
        currentNode = cN;
        nextNode = nullptr;
    }

};
