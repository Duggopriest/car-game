#include "Header.hpp"

Ui UI;

Track	TRACK;
Player	player;

TTF_Font* FONT;
const int WINDOW_WIDTH = 1920, WINDOW_HEIGHT = 1000;

SDL_Texture *CAR_TEXTURE;

SDL_Event event;
SDL_Renderer* renderer;
SDL_Window* window;

bool	EXIT;
unsigned char	PENID;
unsigned char	MENUID;

void	exitGame(void)
{
	EXIT = 0;
}

void	SaveGame()
{
	std::ofstream TextFile("Saves/SaveFile.txt");
	TextFile << "s " << TRACK.startLine.x << " , " << TRACK.startLine.y << endl;
	TextFile << "d " << TRACK.startdir << endl;
	for (int i = 0; i < TRACK.walls.size(); i++)
		TextFile << "w " << TRACK.walls[i].x << " , " << TRACK.walls[i].y << endl;
	/*
	for (int i = 0; i < TRACK.walls.size(); i++)
		TextFile << "c " << TRACK.checkpoint[i].x << " , " << TRACK.checkpoint[i].y << endl;
	for (int i = 0; i < TRACK.walls.size(); i++)
		TextFile << "f " << TRACK.finish[i].x << " , " << TRACK.finish[i].y << endl;
		*/
	TextFile.close();
	cout << "done\n";
}

void	LoadGame()
{
	std::ifstream TextFile;
	TextFile.open("Saves/SaveFile.txt");

	std::string line;
	int	x, y, i;

	while (std::getline(TextFile, line))
	{
		i = 1;
		x = atoi(&line.at(i));
		if (line.at(0) == 'd')
		{
			TRACK.startdir = x;
			continue;
		}
		while (line.at(i++) != ',');
		y = atoi(&line.at(i));

		if (line.at(0) == 's')
			TRACK.startLine = vec(x, y);
		else if (line.at(0) == 'w')
			TRACK.walls.push_back(vec(x, y));
		else if (line.at(0) == 'c')
			TRACK.checkpoint.push_back(vec(x, y));
		else if (line.at(0) == 'f')
			TRACK.finish.push_back(vec(x, y));
	}
	player.car.reset();
	cout << "done\n";
}

void	togglepen()
{
	MENUID = 2;
	PENID = 0;
}

void	penSelectDraw()
{
	PENID = 1;
}

void	buildUi()
{
	//UI.v_buttons.push_back(Button(0, 0, 5, 5));
	UI.menus.resize(3);
	MENUID = 0;
	t_menus* cmenu;

	// =================================== Esc menu
	cmenu = &UI.menus[1];
	cmenu->id = 1;
	cmenu->name = "menu";
	cmenu->blocks.push_back(SDL_Rect(WINDOW_WIDTH / 2 - 125, WINDOW_HEIGHT / 2 - 120, 250, 500));
	cmenu->colours.push_back(SDL_Color(40, 30, 20, 0));

	cmenu->v_buttons.push_back(Button(WINDOW_WIDTH / 2 - 110, WINDOW_HEIGHT / 2 - 100, 220, 95, togglepen, SDL_Color(255, 0, 255, 0), "Pen Mode"));

	cmenu->v_buttons.push_back(Button(WINDOW_WIDTH / 2 - 110, WINDOW_HEIGHT / 2, 220, 95, SaveGame, SDL_Color(0, 255, 0, 0), "Save"));

	cmenu->v_buttons.push_back(Button(WINDOW_WIDTH / 2 - 110, WINDOW_HEIGHT / 2 + 100, 220, 95, LoadGame, SDL_Color(255, 0, 100, 0), "Load"));

	cmenu->v_buttons.push_back(Button(WINDOW_WIDTH / 2 - 110, WINDOW_HEIGHT / 2 + 200, 220, 95, exitGame, SDL_Color(100, 100, 100, 0), "Exit"));

	// =================================== MAP menu
	cmenu = &UI.menus[2];
	cmenu->id = 2;
	cmenu->name = "pen menu";
	cmenu->blocks.push_back(SDL_Rect(0, WINDOW_HEIGHT / 2 - 105, 105, 500));
	cmenu->colours.push_back(SDL_Color(40, 30, 20, 0));

	cmenu->v_buttons.push_back(Button(0, WINDOW_HEIGHT / 2 - 100, 100, 50, penSelectDraw, SDL_Color(100, 100, 100, 0), "Draw"));
}

SDL_Texture* Load_Texture(const char* str)
{
	SDL_Surface* S = SDL_LoadBMP(str);
	if (S == NULL)
	{
		std::cout << "		!!!!!!!!! Failed to load !!!!!!!!!	" << str << std::endl;
		return (NULL);
	}
	SDL_Texture* temp = SDL_CreateTextureFromSurface(renderer, S);
	SDL_FreeSurface(S);
	std::cout << "		successfuly loaded " << str << std::endl;
	return(temp);
}

void	BuildGlobals()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	FONT = TTF_OpenFont("font.ttf", 40);
	if (!FONT)
		std::cout << "Couldn't find/init open ttf font." << std::endl;
	CAR_TEXTURE = Load_Texture("textures/car.bmp");


	cout << "Building UI\n";
	buildUi();
	cout << "Globals Loaded!\n";
}
