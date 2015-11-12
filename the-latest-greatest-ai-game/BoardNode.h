#pragma once
#include <list>
#include "Board.h"


///<summary>
///
///</summary>
class BoardNode{
public:
	BoardNode::BoardNode();
	BoardNode::BoardNode(Board b);
	
	BoardNode::BoardNode();

	void BoardNode::generateChildren();

private:
	int BoardNode::evaluateState();

	Board b;
	std::list<BoardNode*> children;


};