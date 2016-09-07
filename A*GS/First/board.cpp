// Programmer: Dalton Cole
// Class/Assignment: CS5400, Phase 4 of Puzzle Assignment
// Proffesor: Dr. T
// Date: Feb 21, 2016

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


board::board(string file)
{
  	ifstream input(file);

	if(input.is_open())
	{
		// User inputs x/y and the number of colors
		input >> m_x >> colors;

		m_y = m_x;

		// Read in the board layout
		for(int i = 0; i < m_y; i++)
		{
			for(int j = 0; j < m_x; j++)
			{
				input >> display[i][j];
			}
		}
	}
	else
	{
		cout << "Unable to open file" << endl;
	}

	 input.close();
	 
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
	for(int i =  0; i < m_y; i++)
	{
		for(int j = 0; j < m_x; j++)
		{
			if(display[i][j] == color)
			{
				return j;
			}
		}
	}
	return 999;
}

// Finds the y of the starting state, returns 999 if not found
int board::find_first_y(char color)
{
	for(int i =  0; i < m_y; i++)
	{
		for(int j = 0; j < m_x; j++)
		{
			if(display[i][j] == color)
			{
				return i;
			}
		}
	}
	return 999;
}

// Finds the x of the goal state, returns 999 if not found
int board::find_last_x(char color)
{
	for(int i =  (m_y - 1); i >= 0; i--)
	{
		for(int j = (m_x - 1); j >= 0; j--)
		{
			if(display[i][j] == color)
			{
				return j;
			}
		}
	}
	return 999;
}

// Finds the y of the goal state, returns 999 if not found
int board::find_last_y(char color)
{
	for(int i =  (m_y - 1); i >= 0; i--)
	{
		for(int j = (m_x - 1); j >= 0; j--)
		{
			if(display[i][j] == color)
			{
				return i;
			}
		}
	}
	return 999;
}

void board::operator = (board b)
{
	m_x = b.m_x;
	m_y = b.m_y;
	colors = b.colors;
	for(int i = 0; i < m_y; i++)
	{
		for(int j = 0; j < m_x; j++)
		{
			display[i][j] = b.display[i][j];
		}
	}
}

bool board::operator == (board b)
{
	if(m_x == b.m_x && m_y == b.m_y)
	{
		for(int i = 0; i < m_y; i++)
		{
			for(int j = 0; j < m_x; j++)
			{
				if(display[i][j] != b.display[i][j])
				{
					return false;
				}
			}
		}
	}
	else
	{
		return false;
	}
	return true;
}
