/*
================
cHealth.h
- Header file for class definition - SPECIFICATION
- Header file for the Health class which is a child of cSprite class
=================
*/
#ifndef _CHEALTH_H
#define _CHEALTH_H
#include "cSprite.h"

class cHealth : public cSprite
{
public:
	void render();		// Default render function
	void update(float deltaTime);		// Update method
};
#endif