#pragma once
#include <list>

#include "Board.h"


///<summary>
///
///</summary>
class BoardNode{
public:

	///<summary>
	///
	///</summary>
	BoardNode::BoardNode();

	///<summary>
	///
	///</summary>
	BoardNode::BoardNode(Board& b);
	
	///<summary>
	///
	///</summary>
	//BoardNode::~BoardNode();

	///<summary>
	///
	///</summary>
	void BoardNode::generateChildren();

	///<summary>
	///
	///</summary>
	int BoardNode::evaluateState();

	Board b; //!<considered state
	BoardNode* parent;
	std::list<BoardNode*> children; //!<insert childern into the index based on move
	int score; //!<don't want to write a getter for the score so the tree can access it
	int depth;
	bool hasChildren;

};