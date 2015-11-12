// the-latest-greatest-ai-game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Board p = Board();
	bool flag = true;
	bool win = false;
	unsigned int col;

	while (!win){
		std::cin >> col;
		p.applyMove(col, flag);
		win = p.testWin(flag);

		flag = !flag;
	}


	int q;
	std::cout << "Press any key to quit!";
	std::cin >> q;
	return 0;
}

