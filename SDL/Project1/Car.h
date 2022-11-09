#pragma once
class Car
{
	public:
		Car();

		void	drive(double deltaTime);
		void	reset();
		void	draw();

		double	m_carx;
		double	m_cary;
		double	m_cardir;

		double	m_x;
		double	m_y;
		double	m_dir;
		double	m_speed;
		double	m_maxSpeed;
		double	m_maxTurnSpeed;
		double	m_steeringWheel;
		double	m_steeringWheelSpeed;
};



