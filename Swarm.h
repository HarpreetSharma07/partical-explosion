#pragma once
#include "Particle.h"
class Swarm
{
public:
	const static int NPARTICLES = 3000;

private:
	Particle* m_pParticles;

public:
	Swarm();
	virtual ~Swarm();

	const Particle* const getParticles() { return m_pParticles; };

};

