// Programmer: Dalton Cole
// Class/Assignment: CS5400, Phase 1 of Puzzle Assignment
// Proffesor: Dr. T
// Date: Jan 31, 2016

struct point
{
	int m_x; // X position of node
	int m_y; // Y position of node
	char color; // Color of node
	bool goal; // Is the node a goal state
	bool start; // Is the node a start state
	int p_x; // The X position of the partent node
	int p_y; // The y position of the parent node

	inline point()
	{
		m_x = 0;
		m_y = 0;
		color = 'e';
		goal = false;
		start = false;
		p_x = 0;
		p_y = 0;
	}

	inline point(int x, int y, char c)
	{
		m_x = x;
		m_y = y;
		color = c;
		goal = false;
		start = false;
		p_x = 0;
		p_y = 0;
	}

	inline point(int x, int y, char c, bool s, bool g)
	{
		m_x = x;
		m_y = y;
		color = c;
		start = s;
		goal = g;
		p_x = 0;
		p_y = 0;
	}

	inline void operator=(point p )
      { 
         m_x = p.m_x;
         m_y = p.m_y;
         color = p.color;
         start = p.start;
         goal = p.goal;
         p_x = p.p_x;
         p_y = p.p_y;
      }
};