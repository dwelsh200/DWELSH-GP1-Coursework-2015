/*
=================
cRocket.h
- Header file for class definition - SPECIFICATION
- Header file for the Rocket class which is a child of cSprite class
=================
*/
#ifndef _CROCKET_H
#define _CROCKET_H
#include "cSprite.h"
#include "asteroidsGame.h"
#include "CXBOXController.h"

class cRocket : public cSprite
{
private:
	glm::vec2 rocketVelocity = glm::vec2(0.0f, 0.0f);
	int rocketHealth;
	int shipHealth;
	int kills;
	int tieKills;
public:
	void render();		// Default render function
	void update(float deltaTime);		// Rocket update method
	void setRocketVelocity(glm::vec2 rocketVel);   // Sets the velocity for the rocket
	glm::vec2 getRocketVelocity();				 // Gets the rocket velocity
	int setRocketHealth(); //gets/sets the health of the ship
	int getTieKills(); //gets the amount of tie fighter kills
	bool reachedEnd(); //returns true when reached the finish line
	bool startKey(); //returns true when certain kays pressed
	bool endKey();	//returns true when certain kays pressed

	

};
#endif