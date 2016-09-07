// Programmer: Dalton Cole
// Class/Assignment: CS5400, Phase 3 of Puzzle Assignment
// Proffesor: Dr. T
// Date: Feb 14, 2016
// Purpose: Solve a free flow like problem by using the ID-DFS method

#include <iostream>
#include <stack> 
#include <ctime>
#include <vector>
#include <algorithm>
#include <cmath>
#include "board.cpp"
#include "point.cpp"
#include "func.cpp"

using namespace std;

int main(int argc, char* argv[])
{
	// Start clock
	int start_time = clock();

	// Initialize the board using the file specified by the first argument
	board layout(argv[1]);

	// Caputre cout and output it into a file
	freopen(argv[2], "w", stdout);

	// Find the path from each starting node to its corresponding goal node
	vector<point *> solution = startAndGoals(layout);

	// Stop clock. Ready for output
	int stop_clock = clock();

	// Output time in microseconds
	cout << (stop_clock - start_time)/double(CLOCKS_PER_SEC)*1000000 << endl;

	// Output the number of total steps from starting nodes to goal nodes (-layout.colors to get ride of starting states)
	cout << solution.size() - layout.colors << endl;

	// Print out the path from starting to goal nodes and updates the board
	for(int l = (solution.size() - 1); l >= 0; l--)
	{
		layout.display[solution[l] -> m_y][solution[l] -> m_x] = solution[l] -> color;
		cout << solution[l] -> color << " " << solution[l] -> m_x << " " << solution[l] -> m_y << ",";
	}
	cout << endl;

	// Prints the updated board
	layout.print();

	// Output cout into a file
	fclose(stdout);

	return 0;
}
