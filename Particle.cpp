#include "Particle.h"
#include<stdlib.h>
Particle::Particle()
{
	//random number between 0 and 1
	m_x = ((2.0 * rand()) / RAND_MAX) - 1;
	m_y = ((2.0 * rand()) / RAND_MAX) - 1;


}

Particle::~Particle()
{
}
