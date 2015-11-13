#include <stdio.h>
#include "stdafx.h"
#include "Board.h"

Board::Board(){
	//unsigned shorts do not instantiate to 0
	for (int i = 0; i < 8; i++){
		col_fill[i] = 0;
		for (int j = 0; j < 8; j++){
			state[i][j] = 0;
		}
	}
	_play_state = true;
	last_move = 0;
}


Board::Board(Board& genetic){
	for (int i = 0; i < 8; i++){
		col_fill[i] = genetic.col_fill[i];
		for (int j = 0; j < 8; j++){
			state[i][j] = genetic.state[i][j];
		}
	}
	_play_state = genetic.state;
	last_move = genetic.last_move; //indicates no move has been made
}

 
void Board::printState(){
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			if (state[i][j]==0){ std::cout << "|" << ' '; }
			else if (state[i][j] == 1){ std::cout << "|" << 1; }
			else if (state[i][j] == 8){ std::cout << "|" << 8; }
		}
		std::cout << "|" << std::endl;
	}
	//print filled state of columns
	for (int j = 0; j < 8; j++){
		std::cout << "==";
	}
	std::cout << "=" << "\t how full are the columns?" <<std::endl;

	for (int j = 0; j < 8; j++)
		std::cout << "|" << col_fill[j];

	std::cout << "|" << std::endl;

}


void Board::tetrisDrop(){
	bool flag = true;
	for (auto i : col_fill){
		if (i == 0) flag = false;
	}

	if (flag){
		for (int i = 7; i >= 0; --i){
			for (int j = 7; j >= 0; --j){
				if (i == 0) state[i][j] = 0;
				else state[i][j] = state[i-1][j];
			}
			col_fill[i]--;
		}
	}
}


bool Board::applyMove(int col){
	col = col - 1; //easier to enter 1-8 then 0-7
	
	//unsigned short means 0-1 > 0
	if (col > 7 || col < 0){
		std::cout << "invalid move: columns are 1-8. Attempted move " << col <<std::endl;
		return false;
	}

	unsigned short piece;

	if (_play_state){ piece = 1; }
	else{ piece = 8; }
	if (col_fill[col] > 7){
		std::cout << "invalid move: column "<< col+1 << " is full" << std::endl;
		return false;
	}
	else{
		state[7-col_fill[col]][col] = piece;
		col_fill[col]++;
		tetrisDrop();
		last_move = col;
		return true;
	}
}



bool Board::testWin(){
	int piece;
	if (_play_state) piece = 1;
	else piece = 8;

	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			if (state[i][j] == 0){
				/// do nothing
			}else if(state[i][j]==piece ){
				/// vertical case
				if (i > 2){
					int vertCount = 1;
					int vertPos = i;
					while (state[vertPos][j] == piece){
						vertPos--;
						if (state[vertPos][j] == piece) vertCount++;
					}
					if (vertCount >= 4)
					{
						return true;
					}
					///right lean case
					int count = 1;
					int horPos = j;
					vertPos = i;
					while (state[vertPos][horPos] == piece){
						horPos--;
						vertPos--;
						if (horPos == -1) horPos = 7;
						if (state[vertPos][horPos] == piece) count++;
					}
					if (count >= 4)
					{
						return true;
					}
					///end right lean case
					count = 1;
					horPos = j;
					vertPos = i;
					while (state[vertPos][horPos] == piece){
						horPos++;
						vertPos--;
						if (horPos == 8) horPos = 0;
						if (state[vertPos][horPos] == piece) count++;
					}
					if (count >= 4)
					{
						return true;
					}
				}
				///end vertical case

				///horizontal case
				int horCount = 1;
				int horPos = j;
				while (state[i][horPos] == piece){
					horPos--;
					if (horPos == -1) horPos = 7;
					if (state[i][horPos] == piece) horCount++;
				}
				if (horCount >= 4){
					return true;
				}
			}
		}
	}
	return false;
}

