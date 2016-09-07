// Programmer: Dalton Cole
// Class/Assignment: CS5400, Phase 2 of Puzzle Assignment
// Proffesor: Dr. T
// Date: Feb 7th, 2016


// Purpose: Perform iterative deepening depth first search on the given board
// Pre: A valid board with equal number of start and goal states, one for each color
// Post: Returns a vector of a path for each start to each corresponding goal
std::vector<point *> iterative_deepening_search(board & layout, std::vector<point *> & goals);

// Purpose: Recursively find the path from each starting node to its corresponding goal node until depth limit is reached
// Pre: Valid x and y limits of a board are given. Goals has the same number of points as display has colors
//		start is the current succpected path from the start nodes to goal nodes
// Post: If success is true, then a path was found and the path is start, false if no path is found/ depth limit reached
void recursive_dls(std::vector<point *> & start, const int & x, const int & y, const std::vector<point *> & goals, int limit, bool & success);

// Purpose: Tests to see if the current path reaches each goal
// Pre: start contains a possible path from start nodes to goal nodes and goals contains a vector of goal states
// Post: Returns true if start is a path from starting nodes to the goals, false otherwise
bool goal_state(const vector<point *> & start, const vector<point *> & goals);

// Purpose: Determins if there is an open node to the left of the test node
// Pre: test is a member of total
// Post: Returns true if the node to the left is open, false otherwise
bool go_left(const point * test, const vector<point *> & total);

// Purpose: Determins if there is an open node to the right of the test node
// Pre: test is a member of total
// Post: Returns true if the node to the right is open, false otherwise
bool go_right(const point * test, const vector<point *> & total, const int & x);

// Purpose: Determins if there is an open node to the north of the test node
// Pre: test is a member of total
// Post: Returns true if the node to the north is open, false otherwise
bool go_up(const point * test, const vector<point *> & total);

// Purpose: Determins if there is an open node to the south of the test node
// Pre: test is a member of total
// Post: Returns true if the node to the south is open, false otherwise
bool go_down(const point * test, const vector<point *> & total, const int & y);

std::vector<point *> iterative_deepening_search(board & layout, std::vector<point *> & goals)
{
	// Initial depth of the tree
	int depth = 0;
	// Initial no path from each start node to goal node is known
	bool success = false;

	// X and Y maxes of the board
	int x = layout.m_x;
	int y = layout.m_y;

	// Vector of the starting states on the board
	vector<point *> start;
	for(int i = 0; i < layout.colors; i++)
	{
		start.push_back(new point(layout.find_first_x(i+48), layout.find_first_y(i+48), i+48));
	}

	// While no path is found, increase the depth until a path is found
	while(true)
	{
		//cout << depth << endl;
		// Start is a possible path from start nodes to goal nodes, is path if success is true
		// If success if false, increase depth and try again
		recursive_dls(start, x, y, goals, depth, success);
		if(success == true)
		{
			return start;
		}
		depth++;
	}
}

void recursive_dls(std::vector<point *> & start, const int & x, const int & y, const std::vector<point *> & goals, int limit, bool & success)
{
	// Keep track wether or not a point was pushed in the current recursion
	int index = 0;
	// Follow the path that was most recently created for each color
	vector<char> previous_color;

	// Tests to see if the current state is a goal state
	if(goal_state(start, goals) == true)
	{
		success = true;
		return;
	}
	// If depth limit is reached, return
	else if(limit == 0)
	{
		return;
	}
	else
	{
		// For each element in the current path, see if it can be expanded
		// If it can be expanded, then it is recursively calls this functions
		// Making this a depth first search
		for(int i = (start.size() - 1); i >= 0; i--)
		{
			// Find if we already went down a colors path, so we can alternate. Allows us to expand each color's path
			if(std::find(previous_color.begin(), previous_color.end(), start[i] -> color) != previous_color.end())
			{
				break;
			}
			else
			{
				previous_color.push_back(start[i] -> color);
			}
			// See if the current node can expand left
			if(go_right(start[i], start, x) == true)
			{
				index++;
				start.push_back(new point((start[i]->m_x+1), start[i]->m_y, start[i]->color));
				recursive_dls(start, x, y, goals, (limit-1), success);
				if(success == true)
				{
					return;
				}
			}
			// If going right did not work out, pop it off of start and delete it
			if(index != 0)
			{
				index--;
				point * temp = start.back();
				delete temp;
				start.pop_back();

			}

			// See if the current node can expand south
			if(go_down(start[i], start, y) == true)
			{
				index++;
				start.push_back(new point(start[i]->m_x, (start[i]->m_y+1), start[i]->color));
				recursive_dls(start, x, y, goals, (limit-1), success);
				if(success == true)
				{
					return;
				}
			}
			// If going south did not work out, pop it off of start and delete it
			if(index != 0)
			{
				index--;
				point * temp = start.back();
				delete temp;
				start.pop_back();
			}

			// See if the current node can expand left
			if(go_left(start[i], start) == true)
			{
				index++;
				start.push_back(new point((start[i]->m_x-1), start[i]->m_y, start[i]->color));
				recursive_dls(start, x, y, goals, (limit-1), success);
				if(success == true)
				{
					return;
				}
			}
			// If going left did not work out, pop it off of start and delete it
			if(index != 0)
			{
				index--;
				point * temp = start.back();
				delete temp;
				start.pop_back();
			}

			// See if the current node can expand north
			if(go_up(start[i], start) == true)
			{
				index++;
				start.push_back(new point(start[i]->m_x, (start[i]->m_y-1), start[i]->color));
				recursive_dls(start, x, y, goals, (limit-1), success);
				if(success == true)
				{
					return;
				}
			}
			// If going north did not work out, pop it off of start and delete it
			if(index != 0)
			{
				index--;
				point * temp = start.back();
				delete temp;
				start.pop_back();
			}
		}
	}
	// If any pops did not get caught above (due to success) pop and delete them here
	for(int i = 0; i < index; i++)
	{
		point * temp = start.back();
		delete temp;
		start.pop_back();
	}
	return;
}




bool goal_state(const vector<point *> & start, const vector<point *> & goals)
{
	// Keeps track of wether or not each goal node is in start
	int tracker = 0;
	for(int i = 0; i < goals.size(); i++)
	{
		for(int j = 0; j < start.size(); j++)
		{
			// If goal equals a start element, update tracker and test the next goal
			if((goals[i] -> m_x == start[j] -> m_x) && (goals[i] -> m_y == start[j] -> m_y) && (goals[i] -> color == start[j] -> color)) 
			{
				tracker++;
				break;
			}
		}
	}
	// If tracker equals the number of elements in goal, each goal is in state
	if(tracker == goals.size())
	{
		return true;
	}
	return false;
}

bool go_left(const point * test, const vector<point *> & total)
{
	// If test is on the left side of the board, cannot go left
	if(test -> m_x <= 0)
	{
		return false;
	}
	else
	{
		for(int i = 0; i < total.size(); i++)
		{
			// See if there is any node to the left of this node, if so, then return false
			if(((test -> m_x - 1) == total[i] -> m_x) && (test -> m_y == total[i] -> m_y))
			{
				return false;
			}
		}
	}
	return true;
}

bool go_right(const point * test, const vector<point *> & total, const int & x)
{
	// If test is on the right side of the board, cannot go right
	if(test -> m_x >= (x - 1))
	{
		return false;
	}
	else
	{
		for(int i = 0; i < total.size(); i++)
		{
			// See if there is any node to the right of this node, if so, then return false
			if(((test -> m_x + 1) == total[i] -> m_x) && (test -> m_y == total[i] -> m_y))
			{
				return false;
			}
		}
	}
	return true;
}

bool go_up(const point * test, const vector<point *> & total)
{
	// If test is on the top of the board, cannot go up
	if(test -> m_y <= 0)
	{
		return false;
	}
	else
	{
		for(int i = 0; i < total.size(); i++)
		{
			// See if there is any node to the north of this node, if so, then return false
			if(((test -> m_y - 1) == total[i] -> m_y) && (test -> m_x == total[i] -> m_x))
			{
				return false;
			}
		}
	}
	return true;
}

bool go_down(const point * test, const vector<point *> & total, const int & y)
{
	// If test is on the bottom of the board, cannot go down
	if(test -> m_y >= (y - 1))
	{
		return false;
	}
	else
	{
		for(int i = 0; i < total.size(); i++)
		{
			// See if there is any node to the south of this node, if so, then return false
			if(((test -> m_y + 1) == total[i] -> m_y) && (test -> m_x == total[i] -> m_x))
			{
				return false;
			}
		}
	}
	return true;
}