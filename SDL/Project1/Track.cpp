#include "Track.h"
#include "Header.hpp"

Track::Track()
{
	startLine = {500, 500};
	startdir = 0;
}

void	Track::Draw()
{
	int len;

	// ====================== walls
	len = walls.size();
	if (walls.size() > 1)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		for (int i = 0; i + 2 <= len; i += 2)
			SDL_RenderDrawLine(renderer, walls[i].x, walls[i].y, walls[i + 1].x, walls[i + 1].y);
	}

	// ====================== CheckPoints
	len = checkpoint.size();
	if (checkpoint.size() > 1)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		for (int i = 0; i + 2 <= len; i += 2)
			SDL_RenderDrawLine(renderer, checkpoint[i].x, checkpoint[i].y, checkpoint[i + 1].x, checkpoint[i + 1].y);
	}

	// ====================== Finish
	len = finish.size();
	if (finish.size() > 1)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		for (int i = 0; i + 2 <= len; i += 2)
			SDL_RenderDrawLine(renderer, finish[i].x, finish[i].y, finish[i + 1].x, finish[i + 1].y);
	}
}
