#pragma once

#include <vector>

typedef struct vec
{
	int	x;
	int	y;
};

typedef struct linevec
{
	int	ax;
	int	ay;
	int	bx;
	int	by;
};

class Track
{
	public:
		Track();
		void	Draw();

		vec startLine;
		double	startdir;
		std::vector<linevec> walls;
		std::vector<linevec> checkpoint;
		std::vector<linevec> finish;
};

