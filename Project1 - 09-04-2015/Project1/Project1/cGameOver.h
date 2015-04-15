/*
=================
cGameOver.h
- Header file for class definition - SPECIFICATION
- Header file for the GameOver class which is a child of cSprite class
=================
*/
#ifndef _CGAMEOVER_H
#define _CGAMEOVER_H
#include "cSprite.h"

class cGameOver : public cSprite
{
private:
	

public:
	void render();		// Default render function
	void update(float deltaTime);		// Rocket update method

};
#endif