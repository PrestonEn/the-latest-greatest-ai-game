#include "stdafx.h"


typedef struct{
	HANDLE humanMoveFlag; //!<used to indicate to ai that human move is made
	HANDLE opponentMoveFlag; //!<used to indicate ai has returned a move
	Board board;	 //!<pointer to active game board
	bool game_done; //!< is the game over?
	int humanMove;
}global_stuff;

global_stuff glob_of_stuff;

bool gameCycle(int move){
	glob_of_stuff.board.applyMove(move);
	glob_of_stuff.board.printState();
	glob_of_stuff.game_done = glob_of_stuff.board.testWin();
	if (glob_of_stuff.game_done)
		return true;

	glob_of_stuff.board._play_state = !glob_of_stuff.board._play_state; //next players turn
	return false;
}

///
///<summary>
///Create a windows API thread to operate the opponents
///thought
///</summary>
///<param name="lpParam">Void pointer type allowing arbitrary struct to be passed</param>
///<returns>32-bit unsigned integer, thread identifier</returns>
///
DWORD WINAPI opponentThread(LPVOID lpParam){
	MinMax brain = MinMax();
	bool move_made = false; //must wait for human move
	int move = -1;
	/*AI must ALWAYS be thinking about what to do, IE:THE THREAD LIVES UNTIL THE GAME DIES*/
	while (true){
		/*if the human has not made a move, the ai must begin thinking, by considering all possible
		other moves the human can make*/

		DWORD human_move = WaitForSingleObject(glob_of_stuff.humanMoveFlag, 0);
		
		if(human_move == WAIT_OBJECT_0){
			ResetEvent(glob_of_stuff.humanMoveFlag);
			//test if game over, break out of loop
			glob_of_stuff.game_done = gameCycle(move);
			move = -1;
			move_made = !move_made;
			SetEvent(glob_of_stuff.opponentMoveFlag);
			//set the event that the AI has moved
		}
		else if (human_move == WAIT_TIMEOUT){
			if (!move_made){
				WaitForSingleObject(glob_of_stuff.humanMoveFlag, INFINITE);
				SetEvent(glob_of_stuff.humanMoveFlag);
				move_made = !move_made;
			}

			BoardNode* root = new BoardNode(glob_of_stuff.board);
			root->generateChildren();
			move = brain.buildAndSearch(root, 7);
			
		}

		//once a human action is known, return the result from that tree
		//clean up tree
		//begin again
	}
	return 1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	glob_of_stuff.board = Board(); //!< the board used for the active game
	unsigned int col; //!< user input for making move
	glob_of_stuff.game_done = false;
	bool validMv = false;
	/*create threads*/
	glob_of_stuff.humanMoveFlag = CreateEvent(NULL, false, false, NULL);
	glob_of_stuff.opponentMoveFlag = CreateEvent(NULL, true, false, NULL);
	CreateThread(NULL, 0, opponentThread, NULL, 0, NULL);

	glob_of_stuff.board.printState();

	while (!glob_of_stuff.game_done){
		while (!validMv){
			std::cin >> col;
			validMv = glob_of_stuff.board.applyMove(col);
			glob_of_stuff.board.printState();
		}
		validMv = false;
		glob_of_stuff.game_done = glob_of_stuff.board.testWin();
		if (glob_of_stuff.game_done){
			break;
		}
		glob_of_stuff.board._play_state = !glob_of_stuff.board._play_state; //next players turn
		SetEvent(glob_of_stuff.humanMoveFlag);
		//wait for ai to make its move
		WaitForSingleObject(glob_of_stuff.opponentMoveFlag, INFINITE);
	}

	//WaitForSingleObject(glob_of_stuff.opponentMoveFlag, INFINITE); 
	if (glob_of_stuff.board.state){
		std::cout << "GAMEOVER: PLAYER ONE WINS";
	}
	else{
		std::cout << "GAMEOVER: PLAYER TWO WINS";

	}
	int q;
	std::cin >> q;
	CloseHandle(glob_of_stuff.humanMoveFlag);
	CloseHandle(glob_of_stuff.opponentMoveFlag);
}

