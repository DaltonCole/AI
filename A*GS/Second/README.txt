// Programmer: Dalton Cole
// Class/Assignment: CS5400, Phase 4 of Puzzle Assignment
// Proffesor: Dr. T
// Date: Feb 21, 2016

--------------README.TXT------------

----------------------------------
Required files:

main.cpp	point.cpp	board.cpp	board.h		func.cpp
----------------------------------
How to compile:

g++ -std=c++11 -O3 -w main.cpp
----------------------------------
How to run:

./a.out inputfile.txt outputfile.txt

The program requires three arguments. 
The first argument it the .out file. 
The second argument is the name of the input file. 
The third argument is the name of the output file.
----------------------------------
Must be on a UNIX machine with the standard C++ library
----------------------------------
Heuristic:
If a node is on the same x or y plane as the goal,
favor going in that direction more.
This is only implemented in go_right and go_down
due to how the goal is determined between the
set of points. 
----------------------------------