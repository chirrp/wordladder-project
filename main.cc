#include <iostream>
#include "dijkstra.H"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc==4)
	{
		WordLadder y(argv[1]);
		y.outputLadder(argv[2], argv[3]);
	}

	return 0;
}