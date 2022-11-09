#include "UI.h"
#include "Header.hpp"
#include <iostream>

Button::Button() : m_x(0), m_y(0), m_sizeX(0), m_sizeY(0)
{
	funptr = NULL;
}

Button::~Button()
{
	//SDL_DestroyTexture(TextTexture);

}

Button::Button(int x, int y, int sizeX, int sizeY, void (*fun)(void), SDL_Color colour, std::string name) :
	m_x(x), m_y(y), m_sizeX(sizeX), m_sizeY(sizeY), color(colour), name(name)
{
	this->funptr = fun;
	SDL_Color TextColor = { 255, 255, 255, 0 };
	SDL_Surface* TextSurface = TTF_RenderText_Solid(FONT, name.c_str(), TextColor);
	TextTexture = SDL_CreateTextureFromSurface(renderer, TextSurface);
	TextRect = { x + (sizeX / 2) - TextSurface->w / 2, y + (sizeY / 2) - TextSurface->h / 2, TextSurface->w, TextSurface->h };
}

void	Button::onClick()
{
	funptr();
}

bool	Button::hasClicked(int x, int y)
{
	if (x > m_x && x < m_x + m_sizeX &&
		y > m_y && y < m_y + m_sizeY)
	{
		this->onClick();
		return (true);
	}
	return (false);
}

void	Button::drawButton()
{
	SDL_Rect rect = { m_x, m_y, m_sizeX, m_sizeY };
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderCopy(renderer, TextTexture, NULL, &TextRect);
}

// ====================================================================	UI

Ui::Ui()
{
	displayInv = false;
}

Ui::~Ui()
{
}

void	Ui::clearUi()
{
}

bool	Ui::checkButtonsClick(int x, int y)
{
	t_menus& cmenu = menus[MENUID];
	for (int i = 0; i < menus[MENUID].v_buttons.size(); i++)
	{
		if (menus[MENUID].v_buttons[i].hasClicked(x, y))
			return (true);
	}
	return (false);
}

void	drawMenu()
{
	// ====================== menu background ===========================
	for (int i = 0; i < UI.menus[MENUID].blocks.size(); i++)
	{
		SDL_Color& c = UI.menus[MENUID].colours[i];
		SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
		SDL_RenderFillRect(renderer, &UI.menus[MENUID].blocks[i]);
	}
	for (int i = 0; i < UI.menus[MENUID].v_buttons.size(); i++)
	{
		UI.menus[MENUID].v_buttons[i].drawButton();
	}
}

void	Ui::drawUi()
{
	drawMenu();
}
