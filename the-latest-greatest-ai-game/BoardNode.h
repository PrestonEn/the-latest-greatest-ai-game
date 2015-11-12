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
	BoardNode::BoardNode(Board b);
	
	///<summary>
	///
	///</summary>
	BoardNode::~BoardNode();

	///<summary>
	///
	///</summary>
	void BoardNode::generateChildren();

	int score; //!<don't want to write a getter for the score so the tree can access it

private:

	///<summary>
	///
	///</summary>
	int BoardNode::evaluateState();

	Board b; //!<considered state
	BoardNode* children[8]; //!<insert childern into the index based on move

};