#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


#include <windows.h>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cInputMgr.h"
#include "cSoundMgr.h"
#include "cFontMgr.h"
#include "cSprite.h"
#include "asteroidsGame.h"

//remnant of attempted restart function
//bool restart = false;




int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR cmdLine,
                   int cmdShow)

				   
{
	
		//Set our window settings
		const int windowWidth = 1024;
		const int windowHeight = 768;
		const int windowBPP = 16;



		//This is our window
		static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

		// This is the input manager
		static cInputMgr* theInputMgr = cInputMgr::getInstance();

		// This is the sound manager
		static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();

		// This is the Font manager
		static cFontMgr* theFontMgr = cFontMgr::getInstance();

		//The example OpenGL code
		windowOGL theOGLWnd;

		//Attach our the OpenGL window
		pgmWNDMgr->attachOGLWnd(&theOGLWnd);

		// Attach the keyboard manager
		pgmWNDMgr->attachInputMgr(theInputMgr);

		//Attempt to create the window
		if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
		{
			//If it fails

			MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
			pgmWNDMgr->destroyWND(); //Reset the display and exit
			return 1;
		}

		if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
		{
			MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
			pgmWNDMgr->destroyWND(); //Reset the display and exit
			return 1;
		}

		//Clear key buffers
		theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

		/* initialize random seed: */
		srand((unsigned int)time(NULL));

		// Create vector array of textures
		LPCSTR texturesToUse[] = { "Images\\asteroids11.png", "Images\\asteroids22.png", "Images\\asteroids33.png", "Images\\asteroids44.png", "Images\\redlaser1.png", "Images\\tiefighterbit1.png", "Images\\greenlaser1.png", "Images\\healthBar2.png", "Images\\health.png", "Images\\finishLine1.png" };
		for (int tCount = 0; tCount < 10; tCount++)
		{
			theGameTextures.push_back(new cTexture());
			theGameTextures[tCount]->createTexture(texturesToUse[tCount]);
		}

		// load game sounds
		// Load Sound
		LPCSTR gameSounds[6] = { "Audio/themewav.wav", "Audio/shot007.wav", "Audio/explosion2.wav", "Audio/xwingwav.wav", "Audio/explosionwav.wav", "Audio/RedAlert.wav" };

		theSoundMgr->add("Theme", gameSounds[0]);
		theSoundMgr->add("Shot", gameSounds[1]);
		theSoundMgr->add("Explosion", gameSounds[2]);
		theSoundMgr->add("XWING", gameSounds[3]);
		theSoundMgr->add("Boom", gameSounds[4]);
		theSoundMgr->add("Alert", gameSounds[5]);

		theSoundMgr->getSnd("Theme")->playAudio(AL_TRUE);



		// load game fontss
		// Load Fonts
		LPCSTR gameFonts[2] = { "Fonts/digital-7.ttf", "Fonts/space age.ttf" };

		theFontMgr->addFont("SevenSeg", gameFonts[0], 24);
		theFontMgr->addFont("Space", gameFonts[1], 50);

		// Create vector array of textures




		//asteroids
		for (int astro = 0; astro < 200; astro++)
		{
			float yCoOrd = rand() % (-30) + (-1000);
			int dimension = rand() % 128 + 35;
			theAsteroids.push_back(new cAsteroid);
			theAsteroids[astro]->setSpritePos(glm::vec2((rand() % 1024), -(rand() % 15000 + 3000)));
			theAsteroids[astro]->setSpriteTranslation(glm::vec2(0.0f, 75.0f));
			int randAsteroid = rand() % 4;
			theAsteroids[astro]->setTexture(theGameTextures[randAsteroid]->getTexture());
			theAsteroids[astro]->setTextureDimensions(dimension, dimension);
			theAsteroids[astro]->setSpriteCentre();
			theAsteroids[astro]->setAsteroidVelocity(glm::vec2(glm::vec2(0.0f, 0.0f)));
			theAsteroids[astro]->setActive(true);
			theAsteroids[astro]->setMdlRadius();
			
			

		}

		//tiefighters
		for (int ties = 0; ties < 150; ties++)
		{
			theTieFighter.push_back(new cTieFighter);
			theTieFighter[ties]->setSpritePos(glm::vec2((rand() % 1024), -(rand() % 20000 + 4000)));
			theTieFighter[ties]->setSpriteTranslation(glm::vec2(0.0f, 125.0f));
			int randTieFighter = 5;
			theTieFighter[ties]->setTexture(theGameTextures[randTieFighter]->getTexture());
			theTieFighter[ties]->setTextureDimensions(theGameTextures[randTieFighter]->getTWidth(), theGameTextures[randTieFighter]->getTHeight());
			theTieFighter[ties]->setSpriteCentre();
			theTieFighter[ties]->setTieFighterVelocity(glm::vec2(glm::vec2(0.0f, 0.0f)));
			theTieFighter[ties]->setActive(true);
			theTieFighter[ties]->setMdlRadius();

		}


		//Lasers
		for (int zapp = 0; zapp < 300; zapp++)
		{
			
			theLaser.push_back(new cLaser);
			theLaser[zapp]->setSpritePos(glm::vec2((rand() % 1024), -(rand() % 100000 + 5000)));
			theLaser[zapp]->setSpriteTranslation(glm::vec2(0.0f, 250.0f));
			int randLaser = 6;
			theLaser[zapp]->setTexture(theGameTextures[randLaser]->getTexture());
			theLaser[zapp]->setTextureDimensions(theGameTextures[randLaser]->getTWidth(), theGameTextures[randLaser]->getTHeight());
			theLaser[zapp]->setSpriteCentre();
			theLaser[zapp]->setLaserVelocity(glm::vec2(glm::vec2(0.0f, 0.0f)));
			theLaser[zapp]->setActive(true);
			theLaser[zapp]->setMdlRadius();

		}

		//Life
		float xCoOrd3 = 788.0f;
		float yCoOrd3 = 743.0f;
		for (int lvs = 0; lvs < 18; lvs++)
		{
			theLife.push_back(new cLife);
			theLife[lvs]->setSpritePos(glm::vec2(xCoOrd3, yCoOrd3));
			theLife[lvs]->setSpriteTranslation(glm::vec2(0.0f, 0.0f));
			int randLife = 8;
			theLife[lvs]->setTexture(theGameTextures[randLife]->getTexture());
			theLife[lvs]->setTextureDimensions(theGameTextures[randLife]->getTWidth(), theGameTextures[randLife]->getTHeight());
			theLife[lvs]->setSpriteCentre();
			theLife[lvs]->setLifeVelocity(glm::vec2(glm::vec2(0.0f, 0.0f)));
			theLife[lvs]->setActive(true);
			theLife[lvs]->setMdlRadius();
			xCoOrd3 = xCoOrd3 + 12.0f;

		}


		//Finish
		float xCoOrd4 = 510.0f;
		float yCoOrd4 = -18000.0f;
		for (int fin = 0; fin < 1; fin++)
		{
			theFinish.push_back(new cFinish);
			theFinish[fin]->setSpritePos(glm::vec2(xCoOrd4, yCoOrd4));
			theFinish[fin]->setSpriteTranslation(glm::vec2(0.0f, 75.0f));
			int randFinish = 9;
			theFinish[fin]->setTexture(theGameTextures[randFinish]->getTexture());
			theFinish[fin]->setTextureDimensions(theGameTextures[randFinish]->getTWidth(), theGameTextures[randFinish]->getTHeight());
			theFinish[fin]->setSpriteCentre();
			theFinish[fin]->setFinishVelocity(glm::vec2(glm::vec2(0.0f, 0.0f)));
			theFinish[fin]->setActive(true);
			theFinish[fin]->setMdlRadius();

		}



		//Background
		cTexture textureBkgd;
		textureBkgd.createTexture("Images\\SpaceBackgroundbit.png");
		cBkGround spriteBkgd;
		spriteBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
		spriteBkgd.setTexture(textureBkgd.getTexture());
		spriteBkgd.setTextureDimensions(textureBkgd.getTWidth(), textureBkgd.getTHeight());

		//rocket
		cTexture rocketTxt;
		rocketTxt.createTexture("Images\\xwingbitsmall.png");
		cRocket rocketSprite;
		rocketSprite.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
		rocketSprite.setSpritePos(glm::vec2(512.0f, 700.0f));
		rocketSprite.setTexture(rocketTxt.getTexture());
		rocketSprite.setTextureDimensions(rocketTxt.getTWidth(), rocketTxt.getTHeight());
		rocketSprite.setSpriteCentre();
		rocketSprite.setRocketVelocity(glm::vec2(0.0f, 0.0f));


		//health bar
		cTexture textureHealth;
		textureHealth.createTexture("Images\\healthBar2.png");
		cHealth spriteHealth;
		spriteHealth.setSpritePos(glm::vec2(717.0f, 705.0f));
		spriteHealth.setTexture(textureHealth.getTexture());
		spriteHealth.setTextureDimensions(textureHealth.getTWidth(), textureHealth.getTHeight());

		//GameOver
		cTexture textureGameOver;
		textureGameOver.createTexture("Images\\GAMEOVER1.png");
		cGameOver spriteGameOver;
		spriteGameOver.setSpritePos(glm::vec2(0.0f, 0.0f));
		spriteGameOver.setTexture(textureGameOver.getTexture());
		spriteGameOver.setTextureDimensions(textureGameOver.getTWidth(), textureGameOver.getTHeight());

		//Win screen
		cTexture textureWin;
		textureWin.createTexture("Images\\WIN1.png");
		cWin spriteWin;
		spriteWin.setSpritePos(glm::vec2(0.0f, 0.0f));
		spriteWin.setTexture(textureWin.getTexture());
		spriteWin.setTextureDimensions(textureWin.getTWidth(), textureWin.getTHeight());

		//Intro1 screen
		cTexture textureIntro;
		textureIntro.createTexture("Images\\Intro1.png");
		cIntro spriteIntro;
		spriteIntro.setSpritePos(glm::vec2(0.0f, 0.0f));
		spriteIntro.setTexture(textureIntro.getTexture());
		spriteIntro.setTextureDimensions(textureIntro.getTWidth(), textureIntro.getTHeight());

		//Intro2 screen
		cTexture textureIntro2;
		textureIntro2.createTexture("Images\\Intro2.png");
		cIntro spriteIntro2;
		spriteIntro2.setSpritePos(glm::vec2(0.0f, 0.0f));
		spriteIntro2.setTexture(textureIntro2.getTexture());
		spriteIntro2.setTextureDimensions(textureIntro2.getTWidth(), textureIntro2.getTHeight());



		// Attach sound manager to rocket sprite
		rocketSprite.attachSoundMgr(theSoundMgr);

		//counter variables
		int strt = 0;
		int tempo = 0;
		int counter = 0;  //health/lives counter
		int tieCounter = 0;   //amount of tie fighters killed, counter
		bool startKey = false;


		//This is the mainloop, we render frames until isRunning returns false
		while (pgmWNDMgr->isWNDRunning())
		{

			pgmWNDMgr->processWNDEvents(); //Process any window events

			//We get the time that passed since the last frame
			float elapsedTime = pgmWNDMgr->getElapsedSeconds();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
		
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////play state//////////////////////////////////////////////
			
			//render the background
			spriteBkgd.render();


			//update the player ship
			rocketSprite.update(elapsedTime);





			//update and render the asteroids
			vector<cAsteroid*>::iterator asteroidIterator = theAsteroids.begin();
			while (asteroidIterator != theAsteroids.end())
			{
				if ((*asteroidIterator)->isActive() == false)
				{
					asteroidIterator = theAsteroids.erase(asteroidIterator);
				}
				else
				{
					(*asteroidIterator)->update(elapsedTime);
					(*asteroidIterator)->render();
					++asteroidIterator;
				}
			}


			//update and render the tie fighters
			vector<cTieFighter*>::iterator TieFighterIterator = theTieFighter.begin();
			while (TieFighterIterator != theTieFighter.end())
			{
				if ((*TieFighterIterator)->isActive() == false)
				{
					TieFighterIterator = theTieFighter.erase(TieFighterIterator);
				}
				else
				{
					(*TieFighterIterator)->update(elapsedTime);
					(*TieFighterIterator)->render();
					++TieFighterIterator;
				}
			}

			//update and render the green lasers
			vector<cLaser*>::iterator LaserIterator = theLaser.begin();
			while (LaserIterator != theLaser.end())
			{
				if ((*LaserIterator)->isActive() == false)
				{
					LaserIterator = theLaser.erase(LaserIterator);
				}
				else
				{
					(*LaserIterator)->update(elapsedTime);
					(*LaserIterator)->render();
					++LaserIterator;
				}
			}

			//update and render the finishing line
			vector<cFinish*>::iterator FinishIterator = theFinish.begin();
			while (FinishIterator != theFinish.end())
			{
				if ((*FinishIterator)->isActive() == false)
				{
					FinishIterator = theFinish.erase(FinishIterator);
				}
				else
				{
					(*FinishIterator)->update(elapsedTime);
					(*FinishIterator)->render();
					++FinishIterator;
				}
			}



			//counts the number of tie fighters destroyed
			if (rocketSprite.getTieKills() == 1)
			{
				tieCounter++;
			}



			//lowers the players health and removes a health/life from the health bar.
			if ((rocketSprite.setRocketHealth() == 1) && (counter < 18))
			{
				theLife[0]->setActive(false);
				counter++;

			}


			//renders the xwing
			rocketSprite.render();

			//renders the health bar
			spriteHealth.render();
			

			//update and renders the lives/health blocks
			vector<cLife*>::iterator LifeIterator = theLife.begin();
			while (LifeIterator != theLife.end())
			{
				if ((*LifeIterator)->isActive() == false)
				{
					LifeIterator = theLife.erase(LifeIterator);
				}
				else
				{
					(*LifeIterator)->update(elapsedTime);
					(*LifeIterator)->render();
					++LifeIterator;
				}
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//end results///
			bool temp = false;
			bool comp = false;
			bool camp = false;


			//GAME OVER if healths depleted
			if (counter == 18) 
			{
				//renders the game over screen
				spriteGameOver.render();


				//ends game when player enters specific key
				if (rocketSprite.endKey() == true)
				{
					return 0;
				}
				
			}


			//converts the tieKill counter (int) to a string, then a LPCSTR
			std::string score = std::to_string(tieCounter);
			LPCSTR lpMyString = score.c_str();
			//display the tie fighter kills in the upper right of the screen
			theFontMgr->getFont("Space")->printText("KILLS:  ", FTPoint(720.0f, -50.0f, 0.0f));
			theFontMgr->getFont("Space")->printText(lpMyString, FTPoint(920.0f, -50.0f, 0.0f));



			//if the xwing has reached the finishing line
			if (rocketSprite.reachedEnd() == true)
			{
				
				temp = true;
				std::string score = std::to_string(tieCounter);
				LPCSTR lpMyString = score.c_str();
				
				
				if (rocketSprite.endKey() == true)
				{

					return 0;
				}
				
			}
			//renders the win screen and the tie fighter kills
			if (temp == true)
			{
				spriteWin.render();
				theFontMgr->getFont("Space")->printText("Tie-Fighters", FTPoint(280.0f, -300.0f, 0.0f));
				theFontMgr->getFont("Space")->printText("Destroyed:", FTPoint(320.0f, -350.0f, 0.0f));
				theFontMgr->getFont("Space")->printText(lpMyString, FTPoint(480.0f, -400.0f, 0.0f));
			}


			///INTRO SCREENS



			//intro screen 2, i.e controls
			//this 1st because the Intro1 will be on top of Intro2
			if (tempo < 2)
			{
				camp = true;
			}
			if (camp == true)
			{
				spriteIntro2.render();
				if (rocketSprite.endKey() == true)
				{
					tempo++;
				}
			}
			

			//intro screen 1
			if (strt < 1)
			{				
				comp = true;
			}		
			if (comp == true)
			{
				spriteIntro.render();
				if (rocketSprite.endKey() == true)
				{
					strt++;
				}
			}

			
			
			

			pgmWNDMgr->swapBuffers();
			theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);
		}
		
		theOGLWnd.shutdown(); //Free any resources
		pgmWNDMgr->destroyWND(); //Destroy the program window
		//}while (rocketSprite.restart() ==true);
		return 0; //Return success
	
}
