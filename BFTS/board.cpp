// Programmer: Dalton Cole
// Class/Assignment: CS5400, Phase 1 of Puzzle Assignment
// Proffesor: Dr. T
// Date: Jan 31, 2016

#include "board.h"

board::board()
{
	// User inputs x/y and the number of colors
	cin >> m_x >> colors;

	m_y = m_x;

	// Read in the board layout
	for(int i = 0; i < m_y; i++)
	{
		for(int j = 0; j < m_x; j++)
		{
			cin >> display[i][j];
		}
	}
}

void board::print()
{
	// Print board
	for(int i = 0; i < m_y; i++)
	{
		for(int j = 0; j < m_x; j++)
		{
			cout << display[i][j] << " ";
		}
		cout << endl;
	}
	return;
}

// Finds the x of the starting state, returns 999 if not found
int board::find_first_x(char color)
{
	for(int i =  0; i < m_x; i++)
	{
		for(int j = 0; j < m_y; j++)
		{
			if(display[i][j] == color)
			{
				return i;
			}
		}
	}
	return 999;
}

// Finds the y of the starting state, returns 999 if not found
int board::find_first_y(char color)
{
	for(int i =  0; i < m_x; i++)
	{
		for(int j = 0; j < m_y; j++)
		{
			if(display[i][j] == color)
			{
				return j;
			}
		}
	}
	return 999;
}

// Finds the x of the goal state, returns 999 if not found
int board::find_last_x(char color)
{
	for(int i =  (m_x - 1); i >= 0; i--)
	{
		for(int j = (m_y - 1); j >= 0; j--)
		{
			if(display[i][j] == color)
			{
				return i;
			}
		}
	}
	return 999;
}

// Finds the y of the goal state, returns 999 if not found
int board::find_last_y(char color)
{
	for(int i =  (m_x - 1); i >= 0; i--)
	{
		for(int j = (m_y - 1); j >= 0; j--)
		{
			if(display[i][j] == color)
			{
				return j;
			}
		}
	}
	return 999;
}