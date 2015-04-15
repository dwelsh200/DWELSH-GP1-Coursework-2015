/*
=================
cLaser.h
- Header file for class definition - SPECIFICATION
- Header file for the Laser class which is a child of cSprite class
=================
*/
#ifndef _CLASER_H
#define _CLASER_H
#include "cSprite.h"

class cLaser : public cSprite
{
private:
	glm::vec2 LaserVelocity = glm::vec2(0.0f, 0.0f);

public:
	void render();		// Default render function
	void update(float deltaTime);		// Laser update method
	void setLaserVelocity(glm::vec2 LaserVel);   // Sets the velocity for the Laser
	glm::vec2 getLaserVelocity();				 // Gets the Laser velocity
	void renderCollisionBox();				// Use this function to show the collision box
};
#endif