#include "Particle.h"
#include<stdlib.h>



//constructor initialisation list to start particles from centre of the screen
Particle::Particle():m_x(0),m_y(0)
{
	init();
}

void Particle::init()
{
	m_x = 0;
	m_y = 0;
	//we need an angle from 0 to 2pi
	m_direction = (2 * M_PI * rand()) / RAND_MAX;
	m_speed = (0.04 * rand()) / RAND_MAX;
	m_speed *= m_speed;
}
Particle::~Particle()
{
}

void Particle::update(int interval)
{
	//adding a curve
	m_direction += interval * 0.0002;
	//math formulla to get speed along x-axis and y-axis
	double xspeed = m_speed * cos(m_direction);
	double yspeed = m_speed * sin(m_direction);

	//speed is multiplied with variable interval to get a moverment propotional in every direction
	//event in a slow system
	//so it helps in actual game implementation
	m_x += xspeed * interval;
	m_y += yspeed * interval;


	//reinitialize
	if (m_x < -1 || m_x>1 || m_y < -1 || m_y>1)
	{
		init();
	}

	//reinitialize
	if (rand() < RAND_MAX / 100)
	{
		init();
	}
}
