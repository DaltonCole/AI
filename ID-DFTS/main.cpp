// Programmer: Dalton Cole
// Class/Assignment: CS5400, Phase 2 of Puzzle Assignment
// Proffesor: Dr. T
// Date: Feb 7th, 2016
// Purpose: Solve a free flow like problem by using the ID-DFS method

#include <iostream>
#include <stack> 
#include <ctime>
#include <vector>
#include <algorithm>
#include "board.cpp"
#include "point.cpp"
#include "functions.cpp"

using namespace std;

int main(int argc, char* argv[])
{
	// Start clock
	int start_time = clock();

	// Initialize the board using the file specified by the first argument
	board layout(argv[1]);

	freopen(argv[2], "w", stdout);

	// Find the goals (last occurence of a color) on the board and store them
	vector<point *> goals;

	for(int i = 0; i < layout.colors; i++)
	{
		goals.push_back(new point(layout.find_last_x(i+48), layout.find_last_y(i+48), (i+48)));
	}

	// Find the path from each starting node to its corresponding goal node
	vector<point *> solution = iterative_deepening_search(layout, goals);

	// Stop clock. Ready for output
	int stop_clock = clock();

	// Output time in microseconds
	cout << (stop_clock - start_time)/double(CLOCKS_PER_SEC)*1000000 << endl;

	// Output the number of total steps from starting nodes to goal nodes (-layout.colors to get ride of starting states)
	cout << solution.size() - layout.colors << endl;

	// Print out the path from starting to goal nodes and updates the board
	for(int l = 0; l < solution.size(); l++)
	{
		layout.display[solution[l] -> m_y][solution[l] -> m_x] = solution[l] -> color;
		cout << solution[l] -> color << " " << solution[l] -> m_x << " " << solution[l] -> m_y << ",";
	}
	cout << endl;

	// Prints the updated board
	layout.print();

	// Recover memory from solution vector
	for(int i = 0; i < solution.size(); i++)
	{
		delete solution[i];
	}
	solution.clear();

	// Recovery memory from goals vector
	for(int i = 0; i <goals.size(); i++)
	{
		delete goals[i];
	}
	goals.clear();

	fclose(stdout);

	return 0;
}
