/*
=================
cFinishLine.h
- Header file for class definition - SPECIFICATION
- Header file for the Finish Line class which is a child of cSprite class
=================
*/
#ifndef _CFINISH_H
#define _CFINISH_H
#include "cSprite.h"

class cFinish : public cSprite
{
private:
	glm::vec2 FinishVelocity = glm::vec2(0.0f, 0.0f);

public:
	void render();		// Default render function
	void update(float deltaTime);		// Rocket update method
	void setFinishVelocity(glm::vec2 FinishVel);   // Sets the velocity for the rocket
	glm::vec2 getFinishVelocity();				 // Gets the rocket velocity
	void renderCollisionBox();				// Use this function to show the collision box
};
#endif