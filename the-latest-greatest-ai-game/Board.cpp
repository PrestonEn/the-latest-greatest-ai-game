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
	_play_state = false;
}


Board::Board(Board& genetic){
	for (int i = 0; i < 8; i++){
		col_fill[i] = genetic.col_fill[i];
		for (int j = 0; j < 8; j++){
			state[i][j] = genetic.state[i][j];
		}
	}
	_play_state = genetic.state;
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


bool Board::applyMove(unsigned int col, bool turn){
	col = col - 1; //easier to enter 1-8 then 0-7
	
	//unsigned short means 0-1 > 0
	if (col > 7){
		std::cout << "invalid move: columns are 1-8" << std::endl;
		return false;
	}

	unsigned short piece;
	std::cout << "turn is " << turn;
	if (turn){ piece = 1; }
	else{ piece = 8; }
	std::cout << " piece it " << piece << std::endl;
	if (col_fill[col] > 7){
		std::cout << "invalid move: column "<< col << " is full" << std::endl;
		return false;
	}
	else{
		state[7-col_fill[col]][col] = piece;
		col_fill[col]++;
		tetrisDrop();
		printState();
		return true;
	}
}


bool Board::testWin(bool turn){
	int piece;

	if (turn) piece = 1;
	else piece = 8;

	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			if (state[i][j] == 0){
				/// do nothing
			}else if(state[i][j]==piece){
				/// check 
			}
		}
	}
	return true;
}