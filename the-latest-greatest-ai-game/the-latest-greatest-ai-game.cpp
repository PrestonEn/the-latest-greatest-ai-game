// the-latest-greatest-ai-game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Board p = Board();
	bool flag = true;
	unsigned short col;
	while (true){
		std::cin >> col;
		p.applyMove(col, flag);
		flag = !flag;
	}


	getchar();
	return 0;
}

