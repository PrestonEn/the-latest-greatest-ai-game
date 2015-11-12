#include "stdafx.h"


typedef struct{
	HANDLE humanMoveFlag; //!<used to indicate to ai that human move is made
	HANDLE opponentMoveFlag; //!<used to indicate ai has returned a move
	Board *board;	 //!<pointer to active game board
	bool game_state; //!<who's turn is it?
	bool game_done; //!< is the game over?
}global_stuff;

global_stuff glob_of_stuff;

///<summary>
///Create a windows API thread to operate the opponents
///thought
///</summary>
///<param name="lpParam">Void pointer type allowing arbitrary struct to be passed</param>
///<returns>32-bit unsigned integer, thread identifier</returns>
DWORD WINAPI opponentThread(LPVOID lpParam){
	//if the human has not made a move, the ai must begin thinking, by considering all possible
	//other moves the human can make

		//once a human action is know, return the result from that tree
		//clean up tree
		//begin again
}

int _tmain(int argc, _TCHAR* argv[])
{
	Board b = Board(); //!< the board used for the active game
	unsigned int col; //!< user input for making moves
	glob_of_stuff.game_state = true;
	glob_of_stuff.game_done = false;

	while (!glob_of_stuff.game_done){
		std::cin >> col;
		b.applyMove(col, glob_of_stuff.game_state);
		glob_of_stuff.game_done = b.testWin(glob_of_stuff.game_state);

		glob_of_stuff.game_state = !glob_of_stuff.game_state; //next players turn
	}


	int q;
	std::cout << "Press any key to quit!";
	std::cin >> q;
	return 0;
}

