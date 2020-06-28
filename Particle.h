#pragma once
#include<math.h>
//M_PI was showing error so i used this condition that if its not considered in math library then consider it ,otherwise ignore it.
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Particle
{
public:
	double m_x;
	double m_y;
private:

	double m_speed;
	double m_direction;

private:
	void init();
public:
	Particle();
	virtual ~Particle();
	void update(int);
};

