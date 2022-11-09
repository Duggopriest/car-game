/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL and standard IO

#include "../SDL/Project1/Header.hpp"


int	Program_Running;

/*
void	Draw_Grid()
{
	SDL_SetRenderDrawColor(renderer, 100, 0, 100, 0);
	for (float y = 0; y < 1000; y++)
	{
		if (((int)(y + player.y) % 50) == 0)
			SDL_RenderDrawLine(renderer, 0, y, 1920, y);
	}
	SDL_SetRenderDrawColor(renderer, 100, 100, 0, 0);
	for (float x = 0; x < 1920; x++)
	{
		if (((int)(x + player.x) % 50) == 0)
			SDL_RenderDrawLine(renderer, x, 0, x, 1920);
	}
}
*/

void CreateText(const char* Message) 
{
	TTF_Init();
	TTF_Font* font = TTF_OpenFont(FONT_NAME, FONT_SIZE);
	if (!font)
		std::cout << "Couldn't find/init open ttf font." << std::endl;
	SDL_Color TextColor = { 255, 255, 255, 255 };
	SDL_Surface* TextSurface = TTF_RenderText_Solid(font, Message, TextColor);;
	SDL_Texture* TextTexture = SDL_CreateTextureFromSurface(renderer, TextSurface);;
	SDL_Rect TextRect = { 0, 0, TextSurface->w, TextSurface->h };
	SDL_FreeSurface(TextSurface);
	SDL_RenderCopy(renderer, TextTexture, NULL, &TextRect);
	TTF_Quit();
}


void Display_Frame_Time(int &delta)
{
	TTF_Init();
	std::string Message;

	TTF_Font* font = TTF_OpenFont(FONT_NAME, FONT_SIZE);

	if (!font)
		std::cout << "Couldn't find/init open ttf font." << std::endl;

	SDL_Color TextColor = { 255, 255, 255, 255 };

	Message = "frame time: " + std::to_string(delta);


	SDL_Surface* TextSurface = TTF_RenderText_Solid(font, &Message.at(0), TextColor);
	SDL_Texture* TextTexture = SDL_CreateTextureFromSurface(renderer, TextSurface);

	SDL_Rect TextRect = { 0, 80, TextSurface->w, TextSurface->h };


	SDL_RenderCopy(renderer, TextTexture, NULL, &TextRect);

	SDL_FreeSurface(TextSurface);
	SDL_DestroyTexture(TextTexture);
	TTF_CloseFont(font);


	TTF_Quit();
}

void render_frame()
{
	
}

void	PenDrawLine(int x, int y)
{
	if (PENID == 1)
		TRACK.walls.push_back(vec(x, y));
	cout << x << " , " << y << endl;
}

bool	doKeyboard(double Tdelta)
{
	const Uint8* state;
	if (0 > Tdelta > 10)
		Tdelta = .0001;

	state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_W] && player.car.m_speed < player.car.m_maxSpeed)
		player.car.m_speed += Tdelta;
	else if (player.car.m_speed > 0)
		player.car.m_speed -= Tdelta;
	else if (player.car.m_speed < 0)
		player.car.m_speed = 0;

	if (state[SDL_SCANCODE_A])
	{
		if (player.car.m_steeringWheel > -1)
			player.car.m_steeringWheel -= player.car.m_steeringWheelSpeed;
	}
	else if (state[SDL_SCANCODE_D])
	{
		if (player.car.m_steeringWheel < 1)
			player.car.m_steeringWheel += player.car.m_steeringWheelSpeed;
	}
	else if (player.car.m_steeringWheel != 0)
		player.car.m_steeringWheel -= player.car.m_steeringWheel * player.car.m_steeringWheelSpeed;

	player.car.m_dir = player.car.m_cardir + (45 * player.car.m_steeringWheel);

	if (state[SDL_SCANCODE_R])
		player.car.reset();

	static bool tabLock = true;
	if (state[SDL_SCANCODE_ESCAPE]) // ============== escape
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				tabLock = false;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				tabLock = true;
			break;
		}
		if (tabLock)
		{
			if (MENUID == 0)
				MENUID = 1;
			else
			{
				MENUID = 0;
				UI.clearUi();
			}
			tabLock = false;
		}
	}
	return (0);
}

void	doMouse(SDL_Event& event)
{
	if (event.type == SDL_MOUSEWHEEL)
	{
		/*
		if (event.wheel.y > 0) // scroll up
		{
			// Put code for handling "scroll up" here!

			if (ZOOM < 90)
				ZOOM += event.wheel.y;
			cout << ZOOM << endl;
		}
		else if (event.wheel.y < 0) // scroll down
		{
			// Put code for handling "scroll down" here!

			if (ZOOM > 10)
				ZOOM += event.wheel.y;
			cout << ZOOM << endl;
		}
		
		if (event.wheel.x > 0) // scroll right
		{
			// ...
		}
		else if (event.wheel.x < 0) // scroll left
		{
			// ...
		}
		*/
	}
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		// ... handle mouse clicks ...
		SDL_MouseButtonEvent mouseEvent;

		int	ww = WINDOW_WIDTH / 2;
		int	wh = WINDOW_HEIGHT / 2;

		int	x, y;

		Uint32 MouseState = SDL_GetMouseState(&x, &y);

		if (event.button.button == SDL_BUTTON_LEFT)
		{
			if (UI.checkButtonsClick(x, y))
				return;
			if (PENID != 0)
				PenDrawLine(x, y);
		}
		else if (event.button.button == SDL_BUTTON_MIDDLE)
		{
			cout << "X: " << player.car.m_x << endl;
			cout << "Y: " << player.car.m_y << endl;
			cout << "DIR: " << player.car.m_dir << endl;
			cout << "speed: " << player.car.m_speed << endl;
			cout << "walls: " << TRACK.walls.size() << endl;
		}
		else if (event.button.button == SDL_BUTTON_RIGHT)
		{
		}
	}
}

int main(int argc, char* args[]) {
	
	Program_Running = 1;

	TTF_Init();
	BuildGlobals();

	const Uint8* state; // for keyboard


	time_t seconds = time(NULL);
	time_t next = time(NULL);
	int	frame = 0;
	int	fps = 300;

	std::cout << "Stating\n";
	EXIT = 1;
	while (EXIT)
	{
		//std::thread TerrainThread(&Map::RenderChunks, map);
		player.car.drive(player.car.m_maxSpeed / (double)fps);
       
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;

		doMouse(event);
		if (doKeyboard(player.car.m_maxTurnSpeed / (double)fps))
		{
			//TerrainThread.join(); TerrainThread.~thread();
			break;
		}

		


		seconds = time(NULL);
		if (seconds == next + 1)
		{
			fps = frame;
			frame = 0;
			next = time(NULL);
		}
		else
			frame++;
		
		//TerrainThread.join(); TerrainThread.~thread(); // waits for map.RenderChunks(); to be done

		TRACK.Draw();
		player.car.draw();
		UI.drawUi();
		Display_Frame_Time(fps);
		SDL_RenderPresent(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
    }
	Program_Running = 0;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	return 0;
}
