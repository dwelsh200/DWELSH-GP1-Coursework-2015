/*
=================
cIntro.h
- Header file for class definition - SPECIFICATION
- Header file for the Intro screen class which is a child of cSprite class
=================
*/
#ifndef _CINTRO_H
#define _CINTRO_H
#include "cSprite.h"

class cIntro : public cSprite
{
private:


public:
	void render();		// Default render function
	void update(float deltaTime);		// Rocket update method

};
#endif