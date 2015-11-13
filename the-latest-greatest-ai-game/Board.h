#pragma once
#include <iostream>

class Board{
public:
	///default constructor
	Board::Board();

	///<summary>
	///Construct a new board idnetical to this one
	///</summary>
	///<returns>Deep copy of this Board</returns>
	Board::Board(Board& genetic);

	///Write a representation of the state to
	///console
	void Board::printState();

	///<summary>
	///drop the last row 
	///</summary>
	void Board::tetrisDrop();

	///<summary>
	///Attempt to drop a piece into column col, based on player indicated by turn
	///</summary>
	///<param name="col"> the column attempting to move in </param>
	///<param name="turn"> flag indicating whose turn it is </param>
	///<returns>True if move is applied to the Board, False otherwise</returns>
	bool Board::applyMove( int col);

	///<summary>
	///Tests the board for a string of 4, with horizontal wrapping
	///</summary>
	///<param name="turn">Player who's turn we are testing or win condition on</param>
	bool Board::testWin();

	///used to indicate min or max
	bool _play_state;

	///move creating current state
	int last_move;

	///Board itself
	unsigned char state[8][8];

	///if columns are full
	unsigned short col_fill[8];
};

