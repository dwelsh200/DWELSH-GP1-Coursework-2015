/*
=================
cLife.h
- Header file for class definition - SPECIFICATION
- Header file for the Life class which is a child of cSprite class
=================
*/
#ifndef _CLIFE_H
#define _CLIFE_H
#include "cSprite.h"

class cLife : public cSprite
{
private:
	glm::vec2 LifeVelocity = glm::vec2(0.0f, 0.0f);

public:
	void render();		// Default render function
	void update(float deltaTime);		// Rocket update method
	void setLifeVelocity(glm::vec2 LifeVel);   // Sets the velocity for the rocket
	glm::vec2 getLifeVelocity();				 // Gets the rocket velocity
	void renderCollisionBox();				// Use this function to show the collision box
};
#endif