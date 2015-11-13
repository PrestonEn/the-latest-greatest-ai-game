#include "stdafx.h"

BoardNode::BoardNode(){

}

BoardNode::BoardNode(Board& board){
	this->b = Board(board);
	score = this->evaluateState();
	parent = NULL;
	depth = 0;
	hasChildren = false;
}


void BoardNode::generateChildren(){
	bool flag;
	Board _b;
	///attempt to make every move
	for (int i = 1; i < 9; i++){
		_b = Board(b);
		//update state to reflect turn
		_b._play_state = !_b._play_state;
		flag = _b.applyMove(i);
		if (flag){
			hasChildren = true;
			BoardNode* newChild = new BoardNode(_b);
			newChild->parent = this;
			newChild->b.last_move = i;
			newChild->depth = this->depth + 1;
			this->children.push_back(newChild);
		}
	}
}


int BoardNode::evaluateState(){
	int piece;
	piece = 8;
	int gscore = 0;
	int count;
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			if (this->b.state[i][j] == 0){
				/// do nothing
			}
			else if (this->b.state[i][j] == piece){
				/// vertical case
				if (i > 2){
					count = 1;
					int vertPos = i;
					while (this->b.state[vertPos][j] == piece){
						vertPos--;
						if (this->b.state[vertPos][j] == piece) count++;
					}
					if (count >= 4)
					{
						gscore = INT_MAX/2;

					}
					else if(count > 1){
						score = score + count*count;
					}
					///right lean case
				    count = 1;
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
						gscore = INT_MAX/2;
					}
					else if (count > 1){
						gscore = gscore + count*count;
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
						gscore = INT_MAX/2;
					}
					else if (count > 1){
						gscore = gscore + count*count;
					}
				}
				///end vertical case

				///horizontal case
			    count = 1;
				int horPos = j;
				while (this->b.state[i][horPos] == piece){
					horPos--;
					if (horPos == -1) horPos = 7;
					if (this->b.state[i][horPos] == piece) count++;
				}
				if (count >= 4){
					gscore = INT_MAX/2;
					}
				else{
					gscore = gscore + count*count;
				}
			}
		}
	}


	piece = 8;
	int bscore = 0;;
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			if (this->b.state[i][j] == 0){
				/// do nothing
			}
			else if (this->b.state[i][j] == piece){
				/// vertical case
				if (i > 2){
					count = 1;
					int vertPos = i;
					while (this->b.state[vertPos][j] == piece){
						vertPos--;
						if (this->b.state[vertPos][j] == piece) count++;
					}
					if (count >= 4)
					{
						bscore = INT_MAX;
					}
					else if (count > 1){
						bscore = bscore + count*count;
					}
					///right lean case
					count = 1;
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
						bscore = INT_MAX;
					}
					else if (count > 1){
						bscore = bscore + count*count;
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
						bscore = INT_MAX;
					}
					else if (count > 1){
						bscore = bscore + count*count;
					}
				}
				///end vertical case

				///horizontal case
				count = 1;
				int horPos = j;
				while (this->b.state[i][horPos] == piece){
					horPos--;
					if (horPos == -1) horPos = 7;
					if (this->b.state[i][horPos] == piece) count++;
				}
				if (count >= 4){
					bscore = INT_MAX;
				}
				else{
					bscore = bscore + count*count;
				}
			}
		}
	}

	return gscore - bscore;
}




