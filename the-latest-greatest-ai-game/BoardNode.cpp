#include "stdafx.h"

BoardNode::BoardNode(){

}

BoardNode::BoardNode(Board& board){
	this->b = board;
	score = this->evaluateState();
	parent = NULL;
	depth = 0;
}


void BoardNode::generateChildren(){
	bool flag;
	Board _b;
	///attempt to make every move
	for (int i = 0; i < 8; ++i){
		_b = Board(b);
		//update state to reflect turn
		_b._play_state = !_b._play_state;
		flag = _b.applyMove(i);
		if (flag){
			this->children[i] = new BoardNode(_b);
			this->children[i]->parent = this;
			this->children[i]->depth = this->depth + 1;
		}
	}
}


int BoardNode::evaluateState(){
	int piece;
	if (b._play_state){
		piece = 1;
	}
	else{ piece = 8; }
	int score = 0;

	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			if (this->b.state[i][j] == 0){
				/// do nothing
			}
			else if (this->b.state[i][j] == piece){
				/// vertical case
				if (i > 2){
					int vertCount = 1;
					int vertPos = i;
					while (this->b.state[vertPos][j] == piece){
						vertPos--;
						if (this->b.state[vertPos][j] == piece) vertCount++;
					}
					if (vertCount >= 4)
					{
						return INT_MAX;
					}
					else if(vertCount > 1){
						score = score + vertCount;
					}
					///right lean case
					int count = 1;
					int horPos = j;
					vertPos = i;
					while (this->b.state[vertPos][horPos] == piece){
						horPos--;
						vertPos--;
						if (horPos == -1) horPos = 7;
						if (this->b.state[vertPos][horPos] == piece) count++;
					}
					if (count >= 4)
					{
						return INT_MAX;
					}
					else if (count > 1){
						score = score + count;
					}
					///end right lean case
					count = 1;
					horPos = j;
					vertPos = i;
					while (this->b.state[vertPos][horPos] == piece){
						horPos++;
						vertPos--;
						if (horPos == 8) horPos = 0;
						if (this->b.state[vertPos][horPos] == piece) count++;
					}
					if (count >= 4)
					{
						return INT_MAX;
					}
					else if (count > 1){
						score = score + count;
					}
				}
				///end vertical case

				///horizontal case
				int horCount = 1;
				int horPos = j;
				while (this->b.state[i][horPos] == piece){
					horPos--;
					if (horPos == -1) horPos = 7;
					if (this->b.state[i][horPos] == piece) horCount++;
				}
				if (horCount >= 4){
			
						return INT_MAX;
					}
				else{
					score = score + horCount;
				}
			}
		}
	}
	return score;
}




