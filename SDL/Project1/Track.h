#pragma once

#include <vector>

typedef struct vec
{
	int	x;
	int	y;
};

class Track
{
	public:
		Track();
		void	Draw();

		vec startLine;
		double	startdir;
		std::vector<vec> walls;
		std::vector<vec> checkpoint;
		std::vector<vec> finish;
};

