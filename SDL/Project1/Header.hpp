#ifndef HEADER_HPP
# define HEADER_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <time.h>
#include <chrono>
#include <thread>

#include "Track.h"
#include "Player.h"
#include "UI.h"
#include "Car.h"

using std::cout;
using std::endl;

extern int	Program_Running;

extern	Ui	UI;
extern	bool	EXIT;
extern	Track	TRACK;
extern	Player	player;
extern	unsigned char	PENID;
extern	unsigned char	MENUID;

// plant array

extern TTF_Font* FONT;
static const int FONT_SIZE = 20;
static const char* FONT_NAME = "font.ttf";
extern const int WINDOW_WIDTH, WINDOW_HEIGHT;

extern SDL_Texture *CAR_TEXTURE;

extern SDL_Event event;
extern SDL_Renderer* renderer;
extern SDL_Window* window;




// Global Functions
void	BuildGlobals();


#endif