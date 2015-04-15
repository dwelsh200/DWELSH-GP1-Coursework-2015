/*
=================
cWin.h
- Header file for class definition - SPECIFICATION
- Header file for the Win Screen class which is a child of cSprite class
=================
*/
#ifndef _CWIN_H
#define _CWIN_H
#include "cSprite.h"

class cWin : public cSprite
{
private:


public:
	void render();		// Default render function
	void update(float deltaTime);		// Rocket update method

};
#endif