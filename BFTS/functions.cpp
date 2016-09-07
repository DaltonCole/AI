// Programmer: Dalton Cole
// Class/Assignment: CS5400, Phase 1 of Puzzle Assignment
// Proffesor: Dr. T
// Date: Jan 31, 2016

// Purpose: Determins if the square to the left can be added to the frontier
// Post: Returns true if the left square is able to be added to the frontier, false otherwise
bool go_left(point a, vector<point> & explored)
{
	// If the left square is out of bounds, return false
	if(a.m_x == 0)
	{
		return false;
	}
	else
	{
		// Go through each element in the explored list to see if the left element has already been explored
		for(int i = 0; i < explored.size(); i++)
		{
			// If left is the same color and already explored, return false
			if((explored[i].m_x == (a.m_x - 1)) && (explored[i].m_y == a.m_y) && (explored[i].color == a.color) && (explored[i].goal == false))
			{
				return false;
			}
			// If the left is a start state, return false
			if((explored[i].m_x == (a.m_x - 1)) && (explored[i].m_y == a.m_y) && (explored[i].start == true))
			{
				return false;
			}
			// If left is a goal state of a different color, return false
			if((explored[i].m_x == (a.m_x - 1)) && (explored[i].m_y == a.m_y) && (explored[i].goal == true) && (explored[i].color != a.color))
			{
				return false;
			}
		}
	}
	return true;
}

// Purpose: Determins if the square to the right can be added to the frontier
// Post: Returns true if the right square is able to be added to the frontier, false otherwise
bool go_right(point a, vector<point> & explored, board & layout)
{
	// If the right square is out of bounds, return false
	if(a.m_x == (layout.m_x - 1))
	{
		return false;
	}
	else
	{
		// Go through each element in the explored list to see if the right element has already been explored
		for(int i = 0; i < explored.size(); i++)
		{
			// If right is the same color and already explored, return false
			if((explored[i].m_x == (a.m_x + 1)) && (explored[i].m_y == a.m_y) && (explored[i].color == a.color) && (explored[i].goal == false))
			{
				return false;
			}
			// If the right is a start state, return false
			if((explored[i].m_x == (a.m_x + 1)) && (explored[i].m_y == a.m_y) && (explored[i].start == true))
			{
				return false;
			}
			// If right is a goal state of a different color, return false
			if((explored[i].m_x == (a.m_x + 1)) && (explored[i].m_y == a.m_y) && (explored[i].goal == true) && (explored[i].color != a.color))
			{
				return false;
			}
		}
	}
	return true;
}

// Purpose: Determins if the square to the north can be added to the frontier
// Post: Returns true if the north square is able to be added to the frontier, false otherwise
bool go_up(point a, vector<point> & explored)
{
	// If the north square is out of bounds, return false
	if(a.m_y == 0)
	{
		return false;
	}
	else
	{
		// Go through each element in the explored list to see if the right element has already been explored
		for(int i = 0; i < explored.size(); i++)
		{
			// If north is the same color and already explored, return false
			if((explored[i].m_y == (a.m_y - 1)) && (explored[i].m_x == a.m_x) && (explored[i].color == a.color) && (explored[i].goal == false))
			{
				return false;
			}
			// If the north is a start state, return false
			if((explored[i].m_y == (a.m_y - 1)) && (explored[i].m_x== a.m_x) && (explored[i].start == true))
			{
				return false;
			}
			// If north is a goal state of a different color, return false
			if((explored[i].m_y == (a.m_y - 1)) && (explored[i].m_x== a.m_x) && (explored[i].goal == true) && (explored[i].color != a.color))
			{
				return false;
			}
		}
	}
	return true;
}

// Purpose: Determins if the square to the south can be added to the frontier
// Post: Returns true if the south square is able to be added to the frontier, false otherwise
bool go_down(point a, vector<point> & explored, board & layout)
{
	// If the south square is out of bounds, return false
	if(a.m_y == (layout.m_y - 1))
	{
		return false;
	}
	else
	{
		// Go through each element in the explored list to see if the right element has already been explored
		for(int i = 0; i < explored.size(); i++)
		{
			// If south is the same color and already explored, return false
			if((explored[i].m_y == (a.m_y + 1)) && (explored[i].m_x == a.m_x) && (explored[i].color == a.color) && (explored[i].goal == false))
			{
				return false;
			}
			// If the south is a start state, return false
			if((explored[i].m_y == (a.m_x + 1)) && (explored[i].m_x == a.m_x) && (explored[i].start == true))
			{
				return false;
			}
			// If south is a goal state of a different color, return false
			if((explored[i].m_y == (a.m_x + 1)) && (explored[i].m_x == a.m_x) && (explored[i].goal == true) && (explored[i].color != a.color))
			{
				return false;
			}
		}
	}
	return true;
}