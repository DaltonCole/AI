// Programmer: Dalton Cole
// Class/Assignment: CS5400, Phase 1 of Puzzle Assignment
// Proffesor: Dr. T
// Date: Jan 31, 2016

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
using namespace std;

class board
{
	public:
		int m_x; // Length of board
		int m_y; // Width of board
		int colors; // Number of colors on board
		char display[6][6]; // Layout of board

		// Constructor, asks for input from user to creat the board
		board();

		// Prints the board
		void print();

		// Find the respective starting points
		int find_first_x(char color);
		int find_first_y(char color);

		// Find the respective goal points
		int find_last_x(char color);
		int find_last_y(char color);
};

#endif