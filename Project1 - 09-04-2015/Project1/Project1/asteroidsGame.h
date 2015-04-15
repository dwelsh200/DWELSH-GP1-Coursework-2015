#ifndef _ASTEROIDSGAME_H
#define _ASTEROIDSGAME_H

// Card game headers
#include "cAsteroid.h"
#include "cRocket.h"
#include "cBullet.h"
#include "cBkGround.h"
#include "cTieFighter.h"
#include "cLaser.h"
#include "cHealth.h"
#include "cLife.h"
#include "cFinishLine.h"
#include "cGameOver.h"
#include "cWin.h"
#include "cIntro.h"

extern vector<cTexture*> theGameTextures;
extern vector<cAsteroid*> theAsteroids;
extern vector<cBullet*> theRocketBullets;
extern vector<cTieFighter*> theTieFighter;
extern vector<cLaser*> theLaser;
extern vector<cLife*> theLife;
extern vector<cFinish*> theFinish;
extern vector<cGameOver*> theOver;
#endif