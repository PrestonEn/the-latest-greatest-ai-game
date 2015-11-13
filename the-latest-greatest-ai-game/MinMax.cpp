#include "stdafx.h"

int buildAndSearch(Board gameState, int ply){
	BoardNode *node = new BoardNode(gameState);
	if (gameState.testWin()) return gameState.last_move;
	
}