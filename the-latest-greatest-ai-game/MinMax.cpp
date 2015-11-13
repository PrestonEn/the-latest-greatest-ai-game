#include "stdafx.h"
#include <deque>
#include <list>
#include "MinMax.h"

int MinMax::moveSeach(BoardNode *node, int depth, bool maximizingTurn){

	if (depth == 0 || !node->hasChildren){
		return node->evaluateState();
	}

	if (false){
		int bestValue = INT_MIN;
		for (auto p : node->children){
				int val = moveSeach(p, depth - 1, true);
				if (val > bestValue){
					node->score = val;
					bestValue = val;
				}
		}
		return bestValue;
	}else{
		int bestValue = INT_MAX;
		for (auto p : node->children){
			int val = moveSeach(p, depth - 1, false);
			if (val < bestValue){
				node->score = val;
				bestValue = val;
			}
		}
		return bestValue;
	}
}

int MinMax::buildAndSearch(BoardNode* bnode, int ply){
	BoardNode *working;
	if (bnode->b.testWin()){
		return bnode->b.last_move;
	}

	frontier.push_back(bnode);
	int dpt = ply;
	while (!frontier.empty() && dpt >= 0){
		working = frontier.front();
		frontier.pop_front(); //pop_front returns void, but removes element....
		working->generateChildren();
		explored.push_back(working);
		for (auto p : working->children){
			frontier.push_back(p);
		}
		--dpt;
	}
	
	int act=-1;
	int val = INT_MIN;
	std::cout << "THE CHILDREN" << std::endl;
	for (auto p : bnode->children){
		p->b.printState();
		p->score = moveSeach(p, ply, !p->b._play_state);
		if (p->score > val){

			val = p->score;
			act = p->b.last_move;
			std::cout << p->score;
		}

	}
	std::cout << "END THE CHILDREN" << std::endl;

	if (act == -1){
		return rand() % 8 + 1;
	}

	return act;
}