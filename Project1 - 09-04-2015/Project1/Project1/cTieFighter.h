/*
=================
cTieFighter.h
- Header file for class definition - SPECIFICATION
- Header file for the TieFighter class which is a child of cSprite class
=================
*/
#ifndef _CTIEFIGHTER_H
#define _CTIEFIGHTER_H
#include "cSprite.h"

class cTieFighter : public cSprite
{
private:
	glm::vec2 TieFighterVelocity = glm::vec2(0.0f, 0.0f);

public:
	void render();		// Default render function
	void update(float deltaTime);		// Rocket update method
	void setTieFighterVelocity(glm::vec2 TieFighterVel);   // Sets the velocity for the rocket
	glm::vec2 getTieFighterVelocity();				 // Gets the rocket velocity
	void renderCollisionBox();				// Use this function to show the collision box
};
#endif