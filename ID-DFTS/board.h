// Programmer: Dalton Cole
// Class/Assignment: CS5400, Phase 2 of Puzzle Assignment
// Proffesor: Dr. T
// Date: Feb 7th, 2016

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int size_of_board = 9;

class board
{
	public:
		int m_x; // Length of board
		int m_y; // Width of board
		int colors; // Number of colors on board
		char display[size_of_board][size_of_board]; // Layout of board

		// Constructor, asks for input from user to creat the board
		board();
		// Constructor, takes in input from a file to create the board
		board(string file);

		// Prints the board
		void print();

		// Find the respective starting points
		int find_first_x(char color);
		int find_first_y(char color);

		// Find the respective goal points
		int find_last_x(char color);
		int find_last_y(char color);

		void operator=(board b);
		bool operator==(board b);
};

#endif