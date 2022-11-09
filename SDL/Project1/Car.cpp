#include "Car.h"
#include "Header.hpp"


double	dot(double ax, double ay, double bx, double by)
{
	return ((ax * bx) + (ay * by));
}

double getAngle(double ax, double ay, double bx, double by)
{
	//return (acos(dot(ax, ay, bx, by) / ((sqrt(ax * ax + ay * ay)) * (sqrt(bx * bx + by * by)))));
	return atan2(by - ay, bx - ax);
}

Car::Car()
{
	m_x = TRACK.startLine.x;
	m_y = TRACK.startLine.y;
	m_dir = TRACK.startdir;

	m_carx = m_x;
	m_cary = m_y;
	m_cardir = getAngle(m_x, m_y, m_carx, m_cary);
	m_speed = 0;
	m_maxSpeed = 30;
	m_maxTurnSpeed = 200;
	m_steeringWheel = 0;
	m_steeringWheelSpeed = .003;

	m_velocityDir = 0;

	m_x += cos(m_dir * 3.14 / 180) * 100;
	m_y += sin(m_dir * 3.14 / 180) * 100;
}

void Car::reset()
{
	m_x = TRACK.startLine.x;
	m_y = TRACK.startLine.y;
	m_dir = TRACK.startdir;

	m_carx = m_x;
	m_cary = m_y;
	m_cardir = getAngle(m_x, m_y, m_carx, m_cary);
	m_speed = 0;
	m_maxSpeed = 100;
	m_maxTurnSpeed = 200;
	m_steeringWheel = 0;
	m_steeringWheelSpeed = .003;

	m_x += cos(m_dir * 3.14 / 180) * 100;
	m_y += sin(m_dir * 3.14 / 180) * 100;
}

void Car::draw()
{
	/*
	SDL_Rect dstrect;
	dstrect.h = 50;
	dstrect.w = 100;
	dstrect.x = 500;
	dstrect.y = 500;
	*/

	SDL_Point center;
	center.x = 10;
	center.y = 12;

	SDL_Rect rect;
	//rect = { (int)m_y, (int)m_x, 100, 50 };
	rect = { (int)m_x, (int)m_y, 10, 10 };
	SDL_SetRenderDrawColor(renderer, 255, 48, 38, 0);
	SDL_RenderFillRect(renderer, &rect);
	
	rect = { (int)m_carx, (int)m_cary, 50, 25 };
	SDL_RenderCopyEx(renderer,
		CAR_TEXTURE,
		NULL,
		&rect,
		player.car.m_cardir,
		&center,
		SDL_FLIP_NONE);
	
}

double	min(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

void	Car::drive(double deltaTime)
{
	static double angle = 0;

	m_x += cos(m_dir * 3.14 / 180) * ((m_speed + abs(m_steeringWheel * 15)) / 5) * deltaTime;
	m_y += sin(m_dir * 3.14 / 180) * ((m_speed + abs(m_steeringWheel * 15)) / 5) * deltaTime;
	m_x += cos(m_velocityDir) * m_speed / 5 * deltaTime;
	m_y += sin(m_velocityDir) * m_speed / 5 * deltaTime;

	m_cardir = getAngle(m_carx, m_cary, m_x, m_y);
	m_carx = m_x + cos(m_velocityDir) * m_speed / 5 * deltaTime;
	m_cary = m_y + sin(m_velocityDir) * m_speed / 5 * deltaTime;
	m_carx += cos(m_cardir) * -40;
	m_cary += sin(m_cardir) * -40;
	

	double a = m_velocityDir * 180 / M_PI;
	double b = m_cardir * 180 / M_PI;
	double c = fmod(a - b + 360, 360);
	double d = fmod(b - a + 360, 360);
	angle = min(c, d);
	if (c < d)
		m_velocityDir -= deltaTime * (angle / 2000); // adjusts how fast vel Dir straightens
	else if (d < c)
		m_velocityDir += deltaTime * (angle / 2000);
	if (m_velocityDir > M_PI)
		m_velocityDir = -M_PI;
	if (m_velocityDir < -M_PI)
		m_velocityDir = M_PI;
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderDrawLine(renderer, m_carx, m_cary, m_carx + cos(m_velocityDir) * 100, m_cary + sin(m_velocityDir) * 100);
	m_cardir *= 180 / M_PI;
}