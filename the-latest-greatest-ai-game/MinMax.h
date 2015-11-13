#include "stdafx.h"


///Implementation of minmax search algorithm, 
///using Breadth First Search, adapted from
///"Artificial Intelligence, A Modern Approach 3rd Edition"
class MinMax{
private:
	//given some boardnode, perform minimax search and return the appropriate move
	int MinMax::moveSeach(BoardNode *origin, int ply, int maximizingTurn);


public:
	MinMax::MinMax();
	
	MinMax::~MinMax();

	///
	///
	///
	int MinMax::buildAndSearch(Board gameState, int ply);

	
	std::deque<BoardNode*> frontier;
	std::list<BoardNode*> explored 
};