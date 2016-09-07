// Programmer: Dalton Cole
// Class/Assignment: CS5400, Phase 4 of Puzzle Assignment
// Proffesor: Dr. T
// Date: Feb 21, 2016

struct point
{
	int m_x; 	// X position of node
	int m_y; 	// Y position of node
	char color; // Color of node
	int distance; // Distance to goal
	point * parent;
	char previous_direction;

	// Defualt Constructor, set point to origin and 'e'
	inline point()
	{
		m_x = 0;
		m_y = 0;
		color = 'e';
		distance = 11; // Greater distance than any board size
		parent = NULL;
		previous_direction = 'e';
	}

	inline ~point() 
	{
		delete parent;
	}

	// Normal constructor
	inline point(const int x, const int y, const char c, const int d, point * p)
	{
		m_x = x;
		m_y = y;
		color = c;
		distance = d;
		parent = p;
		previous_direction = 'e';
	}

	// Normal constructor with privious direction
	inline point(const int x, const int y, const char c, const int d, point * p, const char pc)
	{
		m_x = x;
		m_y = y;
		color = c;
		distance = d;
		parent = p;
		previous_direction = pc;
	}

	inline void operator=(point p)
    { 
         m_x = p.m_x;
         m_y = p.m_y;
         color = p.color;
         distance = p.distance;
         parent = p.parent;
         previous_direction = p.previous_direction;
    }

    inline bool operator==(point p)
    { 
    	if(m_x == p.m_x && m_y == p.m_y && color == p.color)
    	{
    		return true;
    	}
    	else
    	{
    		return false;
    	}
    }

};