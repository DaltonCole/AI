// Programmer: Dalton Cole
// Class/Assignment: CS5400, Phase 3 of Puzzle Assignment
// Proffesor: Dr. T
// Date: Feb 14, 2016

struct point
{
	int m_x; 	// X position of node
	int m_y; 	// Y position of node
	char color; // Color of node
	int distance; // Distance to goal
	point * parent;

	// Defualt Constructor, set point to origin and 'e'
	inline point()
	{
		m_x = 0;
		m_y = 0;
		color = 'e';
		distance = 11; // Greater distance than any board size
		parent = NULL;

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
	}

	inline void operator=(point p)
    { 
         m_x = p.m_x;
         m_y = p.m_y;
         color = p.color;
         distance = p.distance;
         parent = p.parent;

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