#pragma once
#include "stdafx.h"


///Implementation of minmax search algorithm, 
///using Breadth First Search, adapted from
///"Artificial Intelligence, A Modern Approach 3rd Edition"
class MinMax{
private:
	//given some boardnode, perform minimax search and return the appropriate move
	int MinMax::moveSeach(BoardNode *origin, int ply, bool maximizingTurn);


public:	 
	int allActs[8];
	int MinMax::buildAndSearch(BoardNode* bnode, int ply);
	int move; //minmax returns a 
	std::deque<BoardNode*> frontier;
	std::list<BoardNode*> explored;
};