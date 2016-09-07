// Programmer: Dalton Cole
// Class/Assignment: CS5400, Phase 2 of Puzzle Assignment
// Proffesor: Dr. T
// Date: Feb 7th, 2016

struct point
{
	int m_x; 	// X position of node
	int m_y; 	// Y position of node
	char color; // Color of node

	// Defualt Constructor, set point to origin and 'e'
	inline point()
	{
		m_x = 0;
		m_y = 0;
		color = 'e';
	}

	inline ~point() {}

	// Normal constructor
	inline point(const int x, const int y, const char c)
	{
		m_x = x;
		m_y = y;
		color = c;
	}

	inline void operator=(point p)
    { 
         m_x = p.m_x;
         m_y = p.m_y;
         color = p.color;

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