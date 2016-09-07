// Programmer: Dalton Cole
// Class/Assignment: CS5400, Phase 1 of Puzzle Assignment
// Proffesor: Dr. T
// Date: Jan 31, 2016

#include <iostream>
#include <queue>
#include <ctime>
#include <string>
#include <sstream>
#include "board.cpp"
#include "point.cpp"
#include "functions.cpp"
using namespace std;

// Namespace used to fix to_string conversion on the much hated school computers
namespace patch
{
	template <typename T> std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}



int main()
{
	// Constants
	const int colors = 2;
	const char char_colors[2] = {'0','1'};

	// Start clock
	int start_time = clock();

	// Create board
	board layout;

	// Declair starting posistions
	point start[colors] = {point(layout.find_first_x('0'), layout.find_first_y('0'), '0', true, false),
							point(layout.find_first_x('1'), layout.find_first_y('1'), '1', true, false)};

	// Declair goal posistions
	point goal[colors] = {point(layout.find_last_x('0'), layout.find_last_y('0'), '0', false, true),
							point(layout.find_last_x('1'), layout.find_last_y('1'), '1', false, true)};

	// Iniialize data sturctures
	queue <point> frontier;
	vector <point> explored;

	// Make the output meet standards, output correction
	vector<string> output;
	string path;
	ostringstream oss;

	// Number of steps to reach the goal
	int steps = 0;
	// Initial step
	int next_x, next_y;
	// Keep track if we are at the goal yet, for output purposes
	bool again = true;

	// Add starting locations to the frontier
	for(int i = 0; i < colors; i++)
	{
		frontier.push(start[i]);
	}

	// Make the first evaluation point be the first item in the frontier
	point eval = frontier.front();
	frontier.pop();

	// Add goal states in explore for checking if next point is a goal state purposes
	for(int i = 0; i < colors; i++)
	{
		explored.push_back(goal[i]);
	}

	while(true)
	{
		// Keep track of next possible states, for queueing
		point next;

		// Check to see if any of the four touching squares can be added to the frontier
		// If they can, add them to the explored and frontier
		if(go_left(eval, explored))
		{
			next.m_x = eval.m_x - 1;
			next.m_y = eval.m_y;
			next.color = eval.color;
			next.p_x = eval.m_x;
			next.p_y = eval.m_y;
			frontier.push(next);
			explored.push_back(next);
		}
		if(go_down(eval, explored, layout))
		{
			next.m_x = eval.m_x;
			next.m_y = eval.m_y + 1;
			next.color = eval.color;
			next.p_x = eval.m_x;
			next.p_y = eval.m_y;
			frontier.push(next);
			explored.push_back(next);
		}
		if(go_right(eval, explored, layout))
		{
			next.m_x = eval.m_x + 1;
			next.m_y = eval.m_y;
			next.color = eval.color;
			next.p_x = eval.m_x;
			next.p_y = eval.m_y;
			frontier.push(next);
			explored.push_back(next);
		}
		if(go_up(eval, explored))
		{
			next.m_x = eval.m_x;
			next.m_y = eval.m_y - 1;
			next.color = eval.color;
			next.p_x = eval.m_x;
			next.p_y = eval.m_y;
			frontier.push(next);
			explored.push_back(next);
		}

		// Add eval to explored
		explored.push_back(eval);

		// First element of frontier becomes the next element to check, part of FIFO
		eval = frontier.front();

		// If frontier is empty, break. This is not the while statement due to the pop-ing of the queue.
		if(frontier.empty())
		{
			break;
		}

		// Pop explored point from the frontier
		frontier.pop();
	}

	//  Erase the duplicate goal posistions
	for(int j = 0; j < colors; j++)
	{
		for(int i = 0; i < explored.size(); i++)
		{
			if(explored[i].m_x == goal[j].m_x && explored[i].m_y == goal[j].m_y && explored[i].color == char_colors[j])
			{
				explored.erase(explored.begin()+i);
				break;
			}
		}
	}

	// Find the path from goal to starting node
	// Tracks steps and path. Updates layout.
	for(int j = 0; j < colors; j++)
	{
		// Sets variables for the next goal
		next_x = goal[j].m_x;
		next_y = goal[j].m_y;
		again = true;
		while(again)
		{
			if(next_x == 0 && next_y == 0)
			{
				again = false;
			}
			for(int i = 0; i < explored.size(); i++)
			{
				if(explored[i].m_x == next_x && explored[i].m_y == next_y && explored[i].color == char_colors[j])
				{
					layout.display[explored[i].m_x][explored[i].m_y] = char_colors[j];

					steps++;

					//oss << explored[i].color << " " << explored[i].m_x << " " << explored[i].m_x << ',';
					//output.push_back(str(oss));
					//oss.str("");
/*
					path = ",";
					output.push_back(path);
					path = explored[i].m_x;
					output.push_back(path);
					path = " ";
					output.push_back(path);
					path = explored[i].m_y;
					output.push_back(path);
					path = " ";
					output.push_back(path);
					path = explored[i].color;
					output.push_back(path);


					path = explored[i].color;
					output.push_back(path);
					path = " ";
					output.push_back(path);
					path = explored[i].m_y;
					output.push_back(path);
					path = " ";
					output.push_back(path);
					path = explored[i].m_x;
					output.push_back(path);
					path = ",";
					output.push_back(path);
*/

					path.push_back(explored[i].color);
					path.push_back(' ');
					path += patch::to_string(explored[i].m_y);
					path.push_back(' ');
					path += patch::to_string(explored[i].m_x);
					path.push_back(',');

					output.push_back(path);
					path = "";

					next_x = explored[i].p_x;
					next_y = explored[i].p_y;
					break;
				}
			}
		}
	}

	// Stop clock. Ready for output
	int stop_clock = clock();

	// Output time in microseconds
	cout << (stop_clock - start_time)/double(CLOCKS_PER_SEC)*1000000 << endl;

	// Steps output. Minus 2 due to starting states
	cout << steps - colors << endl;

	// Path output. Used vector in order to output correctly
	for(int i = (output.size() - 1); i >= 0; i--)
	{
		cout << output[i];
		output.pop_back();
	}
	cout << endl;

	// Output the finished board
	layout.print();

	return 0;
}
