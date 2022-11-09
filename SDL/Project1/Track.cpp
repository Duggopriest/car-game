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
	if (walls.size() > 0)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		for (int i = 0; i < len; i++)
			SDL_RenderDrawLine(renderer, walls[i].ax, walls[i].ay, walls[i].bx, walls[i].by);
	}

	// ====================== CheckPoints
	len = checkpoint.size();
	if (checkpoint.size() > 0)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		for (int i = 0; i < len; i++)
			SDL_RenderDrawLine(renderer, checkpoint[i].ax, checkpoint[i].ay, checkpoint[i].bx, checkpoint[i].by);
	}

	// ====================== Finish
	len = finish.size();
	if (finish.size() > 0)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		for (int i = 0; i < len; i++)
			SDL_RenderDrawLine(renderer, finish[i].ax, finish[i].ay, finish[i].bx, finish[i].by);
	}
}
