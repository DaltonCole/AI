// Programmer: Dalton Cole
// Class/Assignment: CS5400, Phase 3 of Puzzle Assignment
// Proffesor: Dr. T
// Date: Feb 14, 2016

// Purpose: Helper function for greedyBestFitGraphSearch function
// Pre: Valid board is passed
// Post: Returns a vector of the path from starting nodes to goal nodes
std::vector<point *> startAndGoals(board & layout);

// Purpose: Determins the path from starting nodes to goal nodes
// Pre: No goal is a start. Same number of starts and goals. Colors are in the same order in both
// Post: Returns a vector of the path from starting nodes to goal nodes
std::vector<point *> greedyBestFitGraphSearch(vector<point *> start, vector<point *> goals, const int max_x, const int max_y);

// Purpose: Orders the frontier from furthest to closest from goal
// Pre: Frontier is a valid frontier
// Post: Alters frontier such that the first element is furthest form goal and last element is closest to goal
void order(vector<point *> & frontier);

// Purpose: Find the distance between current node and goal node
// Pre: Both are valid points
// Post: Returns minhatin difference between current and goal node
int find_d(const point * p, const point * goals);

// Purpose: Determins if there is an open node to the left of the test node
// Pre: vectors are corrently filled
// Post: Returns true if the node to the left is open, false otherwise
bool go_left(const point * eval, const vector<point *> path, const vector<point *> & goals);

// Purpose: Determins if there is an open node to the right of the test node
// Pre: vectors are corrently filled
// Post: Returns true if the node to the right is open, false otherwise
bool go_right(const point * eval, const vector<point *> path, const int & x, const vector<point *> & goals);

// Purpose: Determins if there is an open node to the north of the test node
// Pre: vectors are corrently filled
// Post: Returns true if the node to the north is open, false otherwise
bool go_up(const point * eval, const vector<point *> path, const vector<point *> & goals);

// Purpose: Determins if there is an open node to the south of the test node
// Pre: vectors are corrently filled
// Post: Returns true if the node to the south is open, false otherwise
bool go_down(const point * eval, const vector<point *> path, const int & y, const vector<point *> & goals);



std::vector<point *> startAndGoals(board & layout)
{
	// Find the goals (last occurence of a color) on the board and store them
	vector<point *> goals;

	for(int i = 0; i < layout.colors; i++)
	{
		goals.push_back(new point(layout.find_last_x(i+48), layout.find_last_y(i+48), (i+48), 0, NULL));
	}

	// Find the start of each color on the board and store them
	vector<point *> start;

	for(int i = 0; i < layout.colors; i++)
	{
		int first_x = layout.find_first_x(i+48);
		int first_y = layout.find_first_y(i+48);
		int dist = abs(first_x - goals[i] -> m_x) + abs(first_y - goals[i] -> m_y);
		start.push_back(new point(first_x, first_y, i+48, dist, NULL));
	}
	
	// Find solution path
	vector<point *> solution = greedyBestFitGraphSearch(start, goals, layout.m_x, layout.m_y);

	// Delete starting and goal vectors to avoid memory leaks
	for(int i = 0; i < goals.size(); i++)
	{
		delete goals[i];
	}
	goals.clear();

	for(int i = 0; i < start.size(); i++)
	{
		delete start[i];
	}
	start.clear();

	// Return the solution path
	return  solution;
}


std::vector<point *> greedyBestFitGraphSearch(vector<point *> start, vector<point *> goals, const int max_x, const int max_y)
{
	// Elements to explore
	vector<point *> frontier = start;
	// Goal Elements found
	vector<point *> goal_points;
	// Path from start to finish.
	vector<point *> path;

	// Current point to evaluate
	point * eval;
	// Temporary point to be added to frontier
	point * temp;

	// Distance between current point and goal point
	int dist = 0;

	// Find the paths from start to goal nodes
	for(int i = (goals.size() - 1); i >= 0; i--)
	{
		// Get rid of previous explored points in frontier
		frontier = start;
		for(int j = 0; j < ((goals.size() - 1) - i); j++)
		{
			frontier.pop_back();
		}

		// Find path from starting node to goal node
		do
		{

			// Evaluate the back of the frontier (frontier is ordered from furthest away to closest)
			eval = frontier.back();
			// Get rid of last element in frontier and move it to explored
			frontier.pop_back();
			//explored.push_back(new point(eval -> m_x, eval -> m_y, eval -> color, eval -> distance, eval -> parent));
			
			// See if the point next to evaluate can be expanded to
			if(go_left(eval, path, goals))
			{
				// Add point to the left to the frontier
				temp = (new point((eval -> m_x - 1), eval -> m_y, eval -> color, dist, eval));
				dist = find_d(temp, goals[i]);
				temp -> distance = dist;
				frontier.push_back(temp);
			}
			
			if(go_up(eval, path, goals))
			{
				// Add point to the north to the frontier
				temp = (new point((eval -> m_x), (eval -> m_y - 1), eval -> color, dist, eval));
				dist = find_d(temp, goals[i]);
				temp -> distance = dist;
				frontier.push_back(temp);
			}
			if(go_down(eval, path, max_y, goals))
			{
				// Add point to the south to the frontier
				temp = (new point((eval -> m_x), (eval -> m_y + 1), eval -> color, dist, eval));
				dist = find_d(temp, goals[i]);
				temp -> distance = dist;
				frontier.push_back(temp);
			}
			if(go_right(eval, path, max_x, goals))
			{
				// Add point to the right to the frontier
				temp = (new point((eval -> m_x + 1), eval -> m_y, eval -> color, dist, eval));
				dist = find_d(temp, goals[i]);
				temp -> distance = dist;
				frontier.push_back(temp);
			}

			// Order frontier from greatest distance to least distance
			order(frontier); 
		}while(eval -> distance != 0); // Loop until goal is found

		goal_points.push_back(new point((eval -> m_x), (eval -> m_y), eval -> color, dist, eval));

		// Calculate path from goal to start
		point * p = goal_points.back();
		while(p -> parent != NULL)
		{
			path.push_back(new point(p -> m_x, p -> m_y, p -> color, p -> distance, p -> parent));
			p = p -> parent;
		}
		path.push_back(new point(p -> m_x, p -> m_y, p -> color, p -> distance, p -> parent));
	}

	return path;
}

// Reorder vector from furthest to closest distance to goal
void order(vector<point *> & frontier)
{
	for(int i = 0; i < frontier.size(); i++)
	{
		for(int j = i+1; j < frontier.size(); j++)
		{
			if((frontier[i] -> distance) < (frontier[j] -> distance))
			{
				point * temp = frontier[i];
				frontier[i] = frontier[j];
				frontier[j] = temp;

			}
		}
	}

	return;
}

// Find the distance from point to its respective goal 
int find_d(const point * p, const point * goals)
{
	if(p -> color == goals -> color)
	{
		return (abs((p -> m_x) - (goals -> m_x)) + abs((p -> m_y) - (goals -> m_y)));
	}
	return 99;
}


// See if point can go left
bool go_left(const point * eval, const vector<point *> path, const vector<point *> & goals)
{
	// If test is on the left side of the board, cannot go left
	if(eval -> m_x <= 0)
	{
		return false;
	}
	else
	{
		for(int i = 0; i < path.size(); i++)
		{
			//Check to see if point is being used by other colors
			if(((eval -> m_x - 1) == path[i] -> m_x) && (eval -> m_y == path[i] -> m_y))
			{
				return false;
			}

		}
		for(int i = 0; i < goals.size(); i++)
		{
			// Check to see if left goal is another goal point
			if(((eval -> m_x - 1) == goals[i] -> m_x) && (eval -> m_y == goals[i] -> m_y) && (eval -> color != goals[i] -> color))
			{
				return false;
			}
		}
	}
	return true;
}

// See if point can go right
bool go_right(const point * eval, const vector<point *> path, const int & x, const vector<point *> & goals)
{
	// If test is on the right side of the board, cannot go right
	if(eval -> m_x >= (x - 1))
	{
		return false;
	}
	else
	{
		for(int i = 0; i < path.size(); i++)
		{
			//Check to see if point is being used by other colors
			if(((eval -> m_x + 1) == path[i] -> m_x) && (eval -> m_y == path[i] -> m_y))
			{
				return false;
			}

		}
		for(int i = 0; i < goals.size(); i++)
		{
			// Check to see if left goal is another goal point
			if(((eval -> m_x + 1) == goals[i] -> m_x) && (eval -> m_y == goals[i] -> m_y) && (eval -> color != goals[i] -> color))
			{
				return false;
			}
		}
	}
	return true;
}

// See if point can go up
bool go_up(const point * eval, const vector<point *> path, const vector<point *> & goals)
{
	// If test is on the top of the board, cannot go up
	if(eval -> m_y <= 0)
	{
		return false;
	}
	else
	{
		for(int i = 0; i < path.size(); i++)
		{
			//Check to see if point is being used by other colors
			if(((eval -> m_x) == path[i] -> m_x) && (eval -> m_y - 1 == path[i] -> m_y))
			{
				return false;
			}

		}
		for(int i = 0; i < goals.size(); i++)
		{
			// Check to see if north goal is another goal point
			if((eval -> m_x == goals[i] -> m_x) && (eval -> m_y - 1 == goals[i] -> m_y) && (eval -> color != goals[i] -> color))
			{
				return false;
			}
		}
	}
	return true;
}

// See if point can go down
bool go_down(const point * eval, const vector<point *> path, const int & y, const vector<point *> & goals)
{
	// If test is on the bottom of the board, cannot go down
	if(eval -> m_y >= (y - 1))
	{
		return false;
	}
	else
	{
		for(int i = 0; i < path.size(); i++)
		{
			//Check to see if point is being used by other colors
			if(((eval -> m_x) == path[i] -> m_x) && (eval -> m_y + 1 == path[i] -> m_y))
			{
				return false;
			}

		}
		for(int i = 0; i < goals.size(); i++)
		{
			// Check to see if south goal is another goal point
			if(((eval -> m_x) == goals[i] -> m_x) && (eval -> m_y + 1 == goals[i] -> m_y) && (eval -> color != goals[i] -> color))
			{
				return false;
			}
		}
	}
	return true;
}