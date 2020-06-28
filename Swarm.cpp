#include "Swarm.h"

Swarm::Swarm():lastTime(0)
{
	m_pParticles = new Particle[NPARTICLES];
}

Swarm::~Swarm()
{
	delete[] m_pParticles;
}

void Swarm::update(int elapsed)
{
	//to run the program on same speed in every computer
	//we are using a variable 'interval' to store the time by which update method ran last time

	int interval = elapsed - lastTime;
	for (int i = 0; i < Swarm::NPARTICLES; i++)
	{
		m_pParticles[i].update(interval);
	}
	lastTime = elapsed;
}
