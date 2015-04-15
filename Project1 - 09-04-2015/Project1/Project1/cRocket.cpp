/*
=================
cRocket.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cRocket.h"



//xbox test
CXBOXController* Player1;


void cRocket::render()
{
	glPushMatrix();

	glTranslatef(spritePos2D.x, spritePos2D.y, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GLTextureID); // Binding of GLtexture name 

	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glTexCoord2f(spriteTexCoordData[0].x, spriteTexCoordData[0].y);
	glVertex2f(-(textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
	glVertex2f((textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
	glVertex2f((textureWidth / 2), (textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
	glVertex2f(-(textureWidth / 2), (textureHeight / 2));

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cRocket::update(float deltaTime)
{
	setBoundingRect(&boundingRect);
	//xbox test
	Player1 = new CXBOXController(1);
	
	//move ship right
	if ((m_InputMgr->isKeyDown(VK_RIGHT)) || (m_InputMgr->isKeyDown(int('D'))) || ((Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)))
	{

		spriteTranslation = (glm::vec2(5.0f, 0.0f));
	}
	
	
	
	//move ship left
	if ((m_InputMgr->isKeyDown(VK_LEFT)) || (m_InputMgr->isKeyDown(int('A'))) || ((Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)))
	{
			spriteTranslation = -(glm::vec2(5.0f, 0.0f));	
	}



	//if the ship hits the left of the screen, it will bounce back in the other direction
	if (spritePos2D.x < 70.0f)
	{
		spriteTranslation = (glm::vec2(1.0f, 0.0f));
	}

	//if the ship hits the right of the screen, it will bounce back in the other direction
	if (spritePos2D.x > 950.0f)
	{
		spriteTranslation = -(glm::vec2(1.0f, 0.0f));
	}

	
	//if spacebar/w/up/xbox right trigger/xbox a is pressed, create a bullet/red laser
	if (m_InputMgr->isKeyDown(VK_SPACE) || ((Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)) || ((Player1->GetState().Gamepad.bRightTrigger)) || (m_InputMgr->isKeyDown(int('W'))) || (m_InputMgr->isKeyDown(int(VK_UP))))
	{
		Player1->Vibrate(65535, 65535);// controller vibrates

		// Add new bullet sprite to the vector array
		theRocketBullets.push_back(new cBullet);
		int numBullets = theRocketBullets.size() - 1;
		theRocketBullets[numBullets]->setSpritePos(glm::vec2(spritePos2D.x , spritePos2D.y));
		theRocketBullets[numBullets]->setSpriteTranslation(glm::vec2(2.0f, 2.0f));
		theRocketBullets[numBullets]->setTexture(theGameTextures[4]->getTexture());
		theRocketBullets[numBullets]->setTextureDimensions(theGameTextures[4]->getTWidth(), theGameTextures[4]->getTHeight());
		theRocketBullets[numBullets]->setSpriteCentre();
		theRocketBullets[numBullets]->setBulletVelocity(glm::vec2(0.0f, 0.0f));
		theRocketBullets[numBullets]->setSpriteRotation(getSpriteRotation());
		theRocketBullets[numBullets]->setActive(true);
		theRocketBullets[numBullets]->setMdlRadius();
		// play the firing sound
		m_SoundMgr->getSnd("XWING")->playAudio(AL_TRUE);
		
	}

	Player1->Vibrate();


	glm::vec2 spriteVelocityAdd = glm::vec2(0.0f, 0.0f);
	

	spriteVelocityAdd *= spriteTranslation;

	rocketVelocity += spriteTranslation;

	spritePos2D += rocketVelocity * deltaTime;

	rocketVelocity *= 0.97;

	/*
	==============================================================
	| Check for collisions
	==============================================================
	*/

	shipHealth = 0; //ship lives/damage
	kills = 0; //tie fighter kills

	//collisions between bullet and asteroids
	for (vector<cBullet*>::iterator bulletIterartor = theRocketBullets.begin(); bulletIterartor != theRocketBullets.end(); ++bulletIterartor)
	{
		
		(*bulletIterartor)->update(deltaTime);
		for (vector<cAsteroid*>::iterator asteroidIterator = theAsteroids.begin(); asteroidIterator != theAsteroids.end(); ++asteroidIterator)
		{
			if ((*asteroidIterator)->collidedWith((*asteroidIterator)->getBoundingRect(), (*bulletIterartor)->getBoundingRect()))
			{
				// if a collision set the bullet and asteroid to false
				(*asteroidIterator)->setActive(false);
				(*bulletIterartor)->setActive(false);
			}
		}
	}


	//collisions between xwing and asteroids
		for (vector<cAsteroid*>::iterator asteroidIterator = theAsteroids.begin(); asteroidIterator != theAsteroids.end(); ++asteroidIterator)
		{
			if ((*asteroidIterator)->collidedWith((*asteroidIterator)->getBoundingRect(), getBoundingRect()))
			{
				// if a collision set the asteroid to false
				(*asteroidIterator)->setActive(false);
				shipHealth++;
				m_SoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
			}
		}
	

		//collisions between bullet and tie fighters
		for (vector<cBullet*>::iterator bulletIterartor = theRocketBullets.begin(); bulletIterartor != theRocketBullets.end(); ++bulletIterartor)
		{
			(*bulletIterartor)->update(deltaTime);
			for (vector<cTieFighter*>::iterator TieFighterIterator = theTieFighter.begin(); TieFighterIterator != theTieFighter.end(); ++TieFighterIterator)
			{
				if ((*TieFighterIterator)->collidedWith((*TieFighterIterator)->getBoundingRect(), (*bulletIterartor)->getBoundingRect()))
				{
					// if a collision set the bullet and TieFighter to false
					(*TieFighterIterator)->setActive(false);
					(*bulletIterartor)->setActive(false);
					kills++;
				}
			}
		}

		//collisions between xwing and tie fighters
		for (vector<cTieFighter*>::iterator TieFighterIterator = theTieFighter.begin(); TieFighterIterator != theTieFighter.end(); ++TieFighterIterator)
		{
			if ((*TieFighterIterator)->collidedWith((*TieFighterIterator)->getBoundingRect(), getBoundingRect()))
			{
				// if a collision set the asteroid to false
				(*TieFighterIterator)->setActive(false);
				shipHealth++;
				m_SoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
			}
		}


		//collisions between xwing and green lasers
		for (vector<cLaser*>::iterator LaserIterator = theLaser.begin(); LaserIterator != theLaser.end(); ++LaserIterator)
		{
			if ((*LaserIterator)->collidedWith((*LaserIterator)->getBoundingRect(), getBoundingRect()))
			{
				// if a collision set the asteroid to false
				(*LaserIterator)->setActive(false);
				shipHealth++;
				m_SoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
			}
		}


		//collisions between xwing and finishing line
		for (vector<cFinish*>::iterator FinishIterator = theFinish.begin(); FinishIterator != theFinish.end(); ++FinishIterator)
		{
			if ((*FinishIterator)->collidedWith((*FinishIterator)->getBoundingRect(), getBoundingRect()))
			{
				// if a collision set the asteroid to false
				m_SoundMgr->getSnd("XWING")->playAudio(AL_TRUE);
			}
		}













//update and render bullets / red lasers
	vector<cBullet*>::iterator bulletIterartor = theRocketBullets.begin();
	while (bulletIterartor != theRocketBullets.end())
	{
		if ((*bulletIterartor)->isActive() == false)
		{
			bulletIterartor = theRocketBullets.erase(bulletIterartor);
			// play the explosion sound.
			m_SoundMgr->getSnd("Boom")->playAudio(AL_TRUE);
		}
		else
		{
			
			(*bulletIterartor)->render();
			++bulletIterartor;
		}
	}

}
/*
=================================================================
  Sets the velocity for the rocket
=================================================================
*/
void cRocket::setRocketVelocity(glm::vec2 rocketVel)
{
	rocketVelocity = rocketVel;
}
/*
=================================================================
  Gets the rocket velocity
=================================================================
*/
glm::vec2 cRocket::getRocketVelocity()
{
	return rocketVelocity;
}
/*
=================================================================
Gets the rocket health
=================================================================
*/
int cRocket::setRocketHealth()
{
	rocketHealth = shipHealth;
	return rocketHealth;
}
/*
=================================================================
Gets the amount of tiefighter kills
=================================================================
*/
int cRocket::getTieKills()
{
	tieKills = kills;
	return tieKills;
}
/*
=================================================================
when rocket reaches the finishing line
=================================================================
*/
bool cRocket::reachedEnd()
{
	for (vector<cFinish*>::iterator FinishIterator = theFinish.begin(); FinishIterator != theFinish.end(); ++FinishIterator)
	{
		if ((*FinishIterator)->collidedWith((*FinishIterator)->getBoundingRect(), getBoundingRect()))
		{
			// if a collision set the asteroid to false
			m_SoundMgr->getSnd("XWING")->playAudio(AL_TRUE);
			return true;
		}
	}


}
/*
=================================================================
when certain keys pressed
=================================================================
*/
bool cRocket::startKey()
{
	if (m_InputMgr->anyKeyPressed() || ((Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)))
	{
		return true;
	}
}



/*
=================================================================
when certain keys pressed
=================================================================
*/

bool cRocket::endKey()
{
	if (m_InputMgr->isKeyDown(VK_RETURN) || ((Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)) || m_InputMgr->isKeyDown(VK_ESCAPE))
	{
		return true;
	}
}

