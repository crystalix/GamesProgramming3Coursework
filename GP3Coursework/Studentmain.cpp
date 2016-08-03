#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


//#include <windows.h>
#include "GameConstants.h"
#include "windowOGL.h"
#include "cWNDManager.h"
#include "cColours.h"
#include "cShapes.h"
#include "cPyramid.h"
#include "cCube.h"
#include "cSphere.h"
#include "cMaterial.h"
#include "cLight.h"
#include "cStarfield.h"
#include "cFontMgr.h"
#include "cCamera.h"
#include "cInputMgr.h"
#include "cSoundMgr.h"
#include "cModelLoader.h"
#include "cModel.h"
#include "cPlayer.h"
#include "cEnemy.h"
#include "cLaser.h"
#include "tardisWarsGame.h"

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR cmdLine,
                   int cmdShow)
{
	float timer = 2.0f;
	bool enemyShooting = false;
    //Set our window settings
    const int windowWidth = 1024;
    const int windowHeight = 768;
    const int windowBPP = 16;
	//used for UI
	int playerLives = 3;
	int playerScore = 0;
	//fog filter variables
	GLuint filter;
	GLuint fogMode = GL_LINEAR;
	GLfloat fogColour[4] = { 0.5f, 0.5f, 0.5f, 1.0f };


	float lookAt = 5.0f;

    //This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	// This is the Font manager
	static cFontMgr* theFontMgr = cFontMgr::getInstance();

	// This is the sound manager
	static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();
	
	//The example OpenGL code
    windowOGL theOGLWnd;

    //Attach our example to our window
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

	// Create Texture maps
	cTexture tardisTexture;
	tardisTexture.createTexture("Models/tardis.png");
	cTexture spaceShipTexture;
	spaceShipTexture.createTexture("Models/SpaceShip/sh3.jpg");
	cTexture laserTexture;
	laserTexture.createTexture("Models/laser.tga");
	cTexture starTexture;
	starTexture.createTexture("Images/star.png");
	cTexture sunTexture;
	sunTexture.createTexture("Images/sun.png");
	cTexture earthTexture;
	earthTexture.createTexture("Images/EarthFlip.png");

	//creates sphere objects for the sun and earth
	cSphere Sun(1, 20, 20);
	cSphere Earth(1, 20, 20);

	// the starfield
	cStarfield theStarField(starTexture.getTexture(), glm::vec3(50.0f, 50.0f, 50.0f));
	Sun.initialise(sunTexture.getTexture(), glm::vec3(9, 12, -5), glm::vec3(0, 0, 0));
	Earth.initialise(earthTexture.getTexture(), glm::vec3(-5,12,-5), glm::vec3(0, 0, 0));
	

	// Create Materials for lights
	cMaterial sunMaterial(lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(0, 0, 0, 1.0f), 50.0f);
	cMaterial earthMaterial(lightColour4(0.0f, 0.0f, 0.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f),lightColour4(0,0,0,1.0f),50.0f);

	// Create Light
	cLight sunLight(GL_LIGHT0, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(9, 12, -5, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	cLight lfLight(GL_LIGHT1, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(30, 0, 100, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	cLight rfLight(GL_LIGHT2, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(-30, 0, 100, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	cLight cbLight(GL_LIGHT3, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(0, 0, -100, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	//Define Ambient light for scene
	GLfloat g_Ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, g_Ambient);

	// load game fonts
	// Load Fonts
	LPCSTR gameFonts[3] = { "Fonts/digital-7.ttf", "Fonts/space age.ttf", "Fonts/doctor_who.ttf" };

	theFontMgr->addFont("SevenSeg", gameFonts[0], 24);
	theFontMgr->addFont("Space", gameFonts[1], 24);
	theFontMgr->addFont("DrWho", gameFonts[2], 48);

	// load game sounds
	// Load Sound
	LPCSTR gameSounds[3] = { "Audio/who10Edit.wav", "Audio/shot007.wav", "Audio/explosion2.wav" };

	theSoundMgr->add("Theme", gameSounds[0]);
	theSoundMgr->add("Shot", gameSounds[1]);
	theSoundMgr->add("Explosion", gameSounds[2]);

	// Create a camera
	cCamera theCamera;
	theCamera.setTheCameraPos(glm::vec3(0.0f, 0.0f, 30.0f));
	theCamera.setTheCameraLookAt(glm::vec3(0.0f, 0.0f, 0.0f));
	theCamera.setTheCameraUpVector(glm::vec3(0.0f, 1.0f, 0.0f)); // pointing upwards in world space
	theCamera.setTheCameraAspectRatio(windowWidth, windowHeight);
	theCamera.setTheProjectionMatrix(90.0f, theCamera.getTheCameraAspectRatio(), 0.1f, 5000.0f);
	theCamera.update();

	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	//Player Model
	cModelLoader tardisMdl;
	tardisMdl.loadModel("Models/tardis1314.obj", tardisTexture); // Player

	//enemy
	cModelLoader spaceShipMdl;
	spaceShipMdl.loadModel("Models/SpaceShip/Sample_Ship.obj", spaceShipTexture); // Enemy
	
	//laser projectiles
	cModelLoader theLaser;
	theLaser.loadModel("Models/laser.obj", laserTexture);

	//Initialises the player at the bottom of the screen
	cPlayer thePlayer;
	thePlayer.initialise(glm::vec3(-5, -5, -5), 0.0f, glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), 5.0f, true);
	thePlayer.setMdlDimensions(tardisMdl.getModelDimensions());
	thePlayer.attachInputMgr(theInputMgr);
	thePlayer.attachSoundMgr(theSoundMgr);

	//Initialises the enemies at the top of the screen in a row
	cEnemy theEnemy;
	theEnemy.initialise(glm::vec3(-4, 5, -5), 0.0f, glm::vec3(3, 3, 3), glm::vec3(0, 0, 0), 5.0f, true);
	theEnemy.setMdlDimensions(spaceShipMdl.getModelDimensions());
	theEnemy.attachInputMgr(theInputMgr);
	theEnemy.attachSoundMgr(theSoundMgr);

	cEnemy theEnemy2;
	theEnemy2.initialise(glm::vec3(0, 5, -5), 0.0f, glm::vec3(3, 3, 3), glm::vec3(0, 0, 0), 5.0f, true);
	theEnemy2.setMdlDimensions(spaceShipMdl.getModelDimensions());
	theEnemy2.attachInputMgr(theInputMgr);
	theEnemy2.attachSoundMgr(theSoundMgr);

	cEnemy theEnemy3;
	theEnemy3.initialise(glm::vec3(4, 5, -5), 0.0f, glm::vec3(3, 3, 3), glm::vec3(0, 0, 0), 5.0f, true);
	theEnemy3.setMdlDimensions(spaceShipMdl.getModelDimensions());
	theEnemy3.attachInputMgr(theInputMgr);
	theEnemy3.attachSoundMgr(theSoundMgr);

	cEnemy theEnemy4;
	theEnemy4.initialise(glm::vec3(8, 5, -5), 0.0f, glm::vec3(3, 3, 3), glm::vec3(0, 0, 0), 5.0f, true);
	theEnemy4.setMdlDimensions(spaceShipMdl.getModelDimensions());
	theEnemy4.attachInputMgr(theInputMgr);
	theEnemy4.attachSoundMgr(theSoundMgr);

	cEnemy theEnemy5;
	theEnemy5.initialise(glm::vec3(12, 5, -5), 0.0f, glm::vec3(3, 3, 3), glm::vec3(0, 0, 0), 5.0f, true);
	theEnemy5.setMdlDimensions(spaceShipMdl.getModelDimensions());
	theEnemy5.attachInputMgr(theInputMgr);
	theEnemy5.attachSoundMgr(theSoundMgr);
	

	float tCount = 0.0f;
	string outputMsg;
	string score;

	std::vector<cLaser*> laserList;
	std::vector<cLaser*>::iterator index;

   //This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
    {
		pgmWNDMgr->processWNDEvents(); //Process any window events

        //We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();

		//Timer used to have enemies shooting every 2 seconds
		timer -= elapsedTime;
		if (timer <= 0)
		{
			enemyShooting = true;
			timer = 2.0f;
		}
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		theOGLWnd.initOGL(windowWidth,windowHeight);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glLoadMatrixf((GLfloat*)&theCamera.getTheViewMatrix());

		//renders the sun, earth and stars, adding light to the sun
		theStarField.render(0.0f);
		sunMaterial.useMaterial();
		Sun.render(0.0f);
		sunLight.lightOn();
		lfLight.lightOn();
		rfLight.lightOn();
		cbLight.lightOn();
		
		//earthMaterial.useMaterial();
		Earth.render(0.0f);

		//renders the player if they are active
		if (thePlayer.isActive() == true)
		{
			tardisMdl.renderMdl(thePlayer.getPosition(), thePlayer.getRotation(), thePlayer.getScale());
			thePlayer.update(elapsedTime);
		}

		//renders the enemies if they are active
		if (theEnemy.isActive() == true)
		{
			spaceShipMdl.renderMdl(theEnemy.getPosition(), theEnemy.getRotation(), theEnemy.getScale());
		}

		if (theEnemy2.isActive() == true)
		{
			spaceShipMdl.renderMdl(theEnemy2.getPosition(), theEnemy2.getRotation(), theEnemy2.getScale());
		}

		if (theEnemy3.isActive() == true)
		{
			spaceShipMdl.renderMdl(theEnemy3.getPosition(), theEnemy3.getRotation(), theEnemy3.getScale());
		}
		
		if (theEnemy4.isActive() == true)
		{
			spaceShipMdl.renderMdl(theEnemy4.getPosition(), theEnemy4.getRotation(), theEnemy4.getScale());
		}

		if (theEnemy5.isActive() == true)
		{
			spaceShipMdl.renderMdl(theEnemy5.getPosition(), theEnemy5.getRotation(), theEnemy5.getScale());
		}

		theCamera.update();

		//if the timer for the enemy shooting has gone to 0, enemy shooting is true and they each get a new lazer
		if (enemyShooting == true)
		{
			int numLasers = 0;
			theEnemyLasers.push_back(new cLaser);
			
			theEnemyLasers[numLasers]->setDirection(glm::vec3(0.0f,-1.0f,0.0f));
			theEnemyLasers[numLasers]->setRotation(0.0f);
			theEnemyLasers[numLasers]->setScale(glm::vec3(1, 1, 1));
			theEnemyLasers[numLasers]->setSpeed(5.0f);
			theEnemyLasers[numLasers]->setPosition(theEnemy.getPosition());
			theEnemyLasers[0]->setIsActive(true);
			theEnemyLasers[numLasers]->update(elapsedTime);
			

			theEnemyLasers2.push_back(new cLaser);
			
			theEnemyLasers2[numLasers]->setDirection(glm::vec3(0.0f, -1.0f, 0.0f));
			theEnemyLasers2[numLasers]->setRotation(0.0f);
			theEnemyLasers2[numLasers]->setScale(glm::vec3(1, 1, 1));
			theEnemyLasers2[numLasers]->setSpeed(5.0f);
			theEnemyLasers2[numLasers]->setPosition(theEnemy2.getPosition());
			theEnemyLasers2[numLasers]->setIsActive(true);
			theEnemyLasers2[numLasers]->update(elapsedTime);

			theEnemyLasers3.push_back(new cLaser);
	
			theEnemyLasers3[numLasers]->setDirection(glm::vec3(0.0f, -1.0f, 0.0f));
			theEnemyLasers3[numLasers]->setRotation(0.0f);
			theEnemyLasers3[numLasers]->setScale(glm::vec3(1, 1, 1));
			theEnemyLasers3[numLasers]->setSpeed(5.0f);
			theEnemyLasers3[numLasers]->setPosition(theEnemy3.getPosition());
			theEnemyLasers3[numLasers]->setIsActive(true);
			theEnemyLasers3[numLasers]->update(elapsedTime);

			theEnemyLasers4.push_back(new cLaser);
		
			theEnemyLasers4[numLasers]->setDirection(glm::vec3(0.0f, -1.0f, 0.0f));
			theEnemyLasers4[numLasers]->setRotation(0.0f);
			theEnemyLasers4[numLasers]->setScale(glm::vec3(1, 1, 1));
			theEnemyLasers4[numLasers]->setSpeed(5.0f);
			theEnemyLasers4[numLasers]->setPosition(theEnemy4.getPosition());
			theEnemyLasers4[numLasers]->setIsActive(true);
			theEnemyLasers4[numLasers]->update(elapsedTime);

			theEnemyLasers5.push_back(new cLaser);
		
			theEnemyLasers5[numLasers]->setDirection(glm::vec3(0.0f, -1.0f, 0.0f));
			theEnemyLasers5[numLasers]->setRotation(0.0f);
			theEnemyLasers5[numLasers]->setScale(glm::vec3(1, 1, 1));
			theEnemyLasers5[numLasers]->setSpeed(5.0f);
			theEnemyLasers5[numLasers]->setPosition(theEnemy5.getPosition());
			theEnemyLasers5[numLasers]->setIsActive(true);
			theEnemyLasers5[numLasers]->update(elapsedTime);
			
		}
		
		//This handles the player shooting at the enemies, setting the lazers to fire upwards
		for (vector<cLaser*>::iterator laserIterartor = theTardisLasers.begin(); laserIterartor != theTardisLasers.end(); ++laserIterartor)
		{
			if ((*laserIterartor)->isActive())
			{
				theLaser.renderMdl((*laserIterartor)->getPosition() , (*laserIterartor)->getRotation(), (*laserIterartor)->getScale());
				(*laserIterartor)->setDirection(glm::vec3(0.0f, 1.0f, 0.0f));				
				(*laserIterartor)->update(elapsedTime);
			}

			//if a lazer hits an alive enemy they are killed, the player gets points and the explosion noise plays
			if (theEnemy.SphereSphereCollision((*laserIterartor)->getPosition(), (*laserIterartor)->getMdlRadius()))
			{	
				if (theEnemy.isActive() == true)
				{
					playerScore += 200;
					theSoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
				}
				theEnemy.setIsActive(false);
				
		
			}

			if (theEnemy2.SphereSphereCollision((*laserIterartor)->getPosition(), (*laserIterartor)->getMdlRadius()))
			{
				if (theEnemy2.isActive() == true)
				{
					playerScore += 200;
					theSoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
				}
				theEnemy2.setIsActive(false);

			}
			if (theEnemy3.SphereSphereCollision((*laserIterartor)->getPosition(), (*laserIterartor)->getMdlRadius()))
			{
				if (theEnemy3.isActive() == true)
				{
					playerScore += 200;
					theSoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
				}
				theEnemy3.setIsActive(false);

			}
			if (theEnemy4.SphereSphereCollision((*laserIterartor)->getPosition(), (*laserIterartor)->getMdlRadius()))
			{
				if (theEnemy4.isActive() == true)
				{
					playerScore += 200;
					theSoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
				}
				theEnemy4.setIsActive(false);

			}
			if (theEnemy5.SphereSphereCollision((*laserIterartor)->getPosition(), (*laserIterartor)->getMdlRadius()))
			{
				if (theEnemy5.isActive() == true)
				{
					playerScore += 200;
					theSoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
				}
				theEnemy5.setIsActive(false);

			}
		}

		//This handles the enemies bullet fire, rendering the bullets
		//if a bullet hits the player they lose a life
		//if they have no more lives the game is reset
		for (vector<cLaser*>::iterator enemyLaserIterartor = theEnemyLasers.begin(); enemyLaserIterartor != theEnemyLasers.end(); ++enemyLaserIterartor)
		{
			if ((*enemyLaserIterartor)->isActive()&&theEnemy.isActive())
			{

				theLaser.renderMdl((*enemyLaserIterartor)->getPosition(), (*enemyLaserIterartor)->getRotation(), (*enemyLaserIterartor)->getScale());
			}

			if (thePlayer.SphereSphereCollision((*enemyLaserIterartor)->getPosition(), (*enemyLaserIterartor)->getMdlRadius()))
			{
				playerLives--;
				if (playerLives <= 0)
				{
					//thePlayer.setIsActive(false);
					playerLives = 3;
					playerScore = 0;
					theEnemy.setIsActive(true);
					theEnemy2.setIsActive(true);
					theEnemy3.setIsActive(true);
					theEnemy4.setIsActive(true);
					theEnemy5.setIsActive(true);

				}
			}
				enemyShooting = false;
		}

		for (vector<cLaser*>::iterator enemyLaserIterartor2 = theEnemyLasers2.begin(); enemyLaserIterartor2 != theEnemyLasers2.end(); ++enemyLaserIterartor2)
		{
			if ((*enemyLaserIterartor2)->isActive() && theEnemy2.isActive())
			{

				theLaser.renderMdl((*enemyLaserIterartor2)->getPosition(), (*enemyLaserIterartor2)->getRotation(), (*enemyLaserIterartor2)->getScale());
				(*enemyLaserIterartor2)->setDirection(glm::vec3(0.0f, -1.0f, 0.0f));
				(*enemyLaserIterartor2)->update(elapsedTime);
				if (thePlayer.SphereSphereCollision((*enemyLaserIterartor2)->getPosition(), (*enemyLaserIterartor2)->getMdlRadius()))
				{
					playerLives--;
					if (playerLives <= 0)
					{
						playerLives = 3;
						playerScore = 0;
						theEnemy.setIsActive(true);
						theEnemy2.setIsActive(true);
						theEnemy3.setIsActive(true);
						theEnemy4.setIsActive(true);
						theEnemy5.setIsActive(true);

					}
				}
				enemyShooting = false;
			}

		}

		
		for (vector<cLaser*>::iterator enemyLaserIterartor3 = theEnemyLasers3.begin(); enemyLaserIterartor3 != theEnemyLasers3.end(); ++enemyLaserIterartor3)
		{
			if ((*enemyLaserIterartor3)->isActive() && theEnemy3.isActive())
			{

				theLaser.renderMdl((*enemyLaserIterartor3)->getPosition(), (*enemyLaserIterartor3)->getRotation(), (*enemyLaserIterartor3)->getScale());
				(*enemyLaserIterartor3)->setDirection(glm::vec3(0.0f, -1.0f, 0.0f));
				(*enemyLaserIterartor3)->update(elapsedTime);
				if (thePlayer.SphereSphereCollision((*enemyLaserIterartor3)->getPosition(), (*enemyLaserIterartor3)->getMdlRadius()))
				{
					playerLives--;
					if (playerLives <= 0)
					{
						//thePlayer.setIsActive(false);
						playerLives = 3;
						playerScore = 0;
						theEnemy.setIsActive(true);
						theEnemy2.setIsActive(true);
						theEnemy3.setIsActive(true);
						theEnemy4.setIsActive(true);
						theEnemy5.setIsActive(true);

					}
				}
				enemyShooting = false;
			}

		}
		for (vector<cLaser*>::iterator enemyLaserIterartor4 = theEnemyLasers4.begin(); enemyLaserIterartor4 != theEnemyLasers4.end(); ++enemyLaserIterartor4)
		{
			if ((*enemyLaserIterartor4)->isActive() && theEnemy4.isActive())
			{

				theLaser.renderMdl((*enemyLaserIterartor4)->getPosition(), (*enemyLaserIterartor4)->getRotation(), (*enemyLaserIterartor4)->getScale());
				(*enemyLaserIterartor4)->setDirection(glm::vec3(0.0f, -1.0f, 0.0f));

				(*enemyLaserIterartor4)->update(elapsedTime);
				if (thePlayer.SphereSphereCollision((*enemyLaserIterartor4)->getPosition(), (*enemyLaserIterartor4)->getMdlRadius()))
				{
					playerLives--;
					if (playerLives <= 0)
					{
						//thePlayer.setIsActive(false);
						playerLives = 3;
						playerScore = 0;
						theEnemy.setIsActive(true);
						theEnemy2.setIsActive(true);
						theEnemy3.setIsActive(true);
						theEnemy4.setIsActive(true);
						theEnemy5.setIsActive(true);

					}
				}
				enemyShooting = false;
			}

			for (vector<cLaser*>::iterator enemyLaserIterartor5 = theEnemyLasers5.begin(); enemyLaserIterartor5 != theEnemyLasers5.end(); ++enemyLaserIterartor5)
			{
				if ((*enemyLaserIterartor5)->isActive() && theEnemy5.isActive())
				{

					theLaser.renderMdl((*enemyLaserIterartor5)->getPosition(), (*enemyLaserIterartor5)->getRotation(), (*enemyLaserIterartor5)->getScale());
					(*enemyLaserIterartor5)->setDirection(glm::vec3(0.0f, -1.0f, 0.0f));

					(*enemyLaserIterartor5)->update(elapsedTime);
					if (thePlayer.SphereSphereCollision((*enemyLaserIterartor5)->getPosition(), (*enemyLaserIterartor5)->getMdlRadius()))
					{
						playerLives--;
						if (playerLives <= 0)
						{
							//thePlayer.setIsActive(false);
							playerLives = 3;
							playerScore = 0;
							theEnemy.setIsActive(true);
							theEnemy2.setIsActive(true);
							theEnemy3.setIsActive(true);
							theEnemy4.setIsActive(true);
							theEnemy5.setIsActive(true);

						}
					}
					enemyShooting = false;
				}
			}

			

		}
		

		//This toggles the audio
		if (thePlayer.soundOn == false)
		{
			theSoundMgr->getSnd("Theme")->stopAudio();
			theSoundMgr->getSnd("Shot")->stopAudio();
			theSoundMgr->getSnd("Explosion")->stopAudio();
		}

		if (thePlayer.soundOn == true & thePlayer.Active == true)
		{
			theSoundMgr->getSnd("Theme")->playAudio(AL_LOOPING);
			theSoundMgr->getSnd("Shot")->playAudio(AL_TRUE);
			theSoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
			thePlayer.Active = false;
		}

		glFogi(GL_FOG_MODE, fogMode);

		//this handles the toggling of fog mode
		if (thePlayer.gp == true)
		{
			//fog is enables, the mode and colour is chosen as defined at the top, as well as the density and where it lies
			glEnable(GL_FOG);
			glFogi(GL_FOG_MODE, fogMode);
			glFogfv(GL_FOG_COLOR, fogColour);
			glFogf(GL_FOG_DENSITY, 0.35f);
			glHint(GL_FOG_HINT, GL_DONT_CARE);
			glFogf(GL_FOG_START, 1.0f);
			glFogf(GL_FOG_END, 5.0f);
		//	thePlayer.gp = false;
		}

		//disables fog
		if (thePlayer.gp == false)
		{
			glDisable(GL_FOG);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		}

		//This toggles the camera mode
		//In this mode, the camera is essentially zoomed out so the player can see more
		if (thePlayer.firstPersonCam == false)
		{
			theCamera.setTheCameraPos(glm::vec3(-30.0f, 0.0f, 0.0f));
			theCamera.setTheCameraLookAt(glm::vec3(0.0f, 0, 0));
			//the xValue is used to move the player back and forth on the x axis, giving them movement
			//It goes from 1 to -1 when the player presses the left or right key
			thePlayer.setPosition(glm::vec3(thePlayer.getPosition().x, thePlayer.getPosition().y, thePlayer.getPosition().z + (thePlayer.xValue*-1)));
			theEnemy.setPosition(glm::vec3(thePlayer.getPosition().x, 5, 10));
			theEnemy2.setPosition(glm::vec3(thePlayer.getPosition().x, 5, 8));
			theEnemy3.setPosition(glm::vec3(thePlayer.getPosition().x, 5, 6));
			theEnemy4.setPosition(glm::vec3(thePlayer.getPosition().x, 5, 4));
			theEnemy5.setPosition(glm::vec3(thePlayer.getPosition().x, 5, 2));
	
		}
		

		//This is the normal camera and so the values of objects are reset to their initial values
		if (thePlayer.firstPersonCam == true)
		{

			theCamera.setTheCameraPos(glm::vec3(0.0f, 0.0f, 30.0f));
			theCamera.setTheCameraLookAt(glm::vec3(0, 0, 0));
			//the xValue is used to move the player back and forth on the x axis, giving them movement
			//It goes from 1 to -1 when the player presses the left or right key
			thePlayer.setPosition(glm::vec3(thePlayer.getPosition().x + thePlayer.xValue, thePlayer.getPosition().y, thePlayer.getPosition().z));
			theEnemy.setPosition(glm::vec3(-4, 5, -5));
			theEnemy2.setPosition(glm::vec3(0, 5, -5));
			theEnemy3.setPosition(glm::vec3(4, 5, -5));
			theEnemy4.setPosition(glm::vec3(8, 5, -5));
			theEnemy5.setPosition(glm::vec3(12, 5, -5));
		}

		//This part handles the UI
		//The player's score and lives are set and then displayed on the screen as well as the game title
		outputMsg = "Lives: " + to_string(playerLives);
		score = "Score: " + to_string(playerScore);
		
		glPushMatrix();
		theOGLWnd.setOrtho2D(windowWidth, windowHeight);
		theFontMgr->getFont("DrWho")->printText("Pew Pew Laserz", FTPoint(10, 70, 0.0f), colour3f(0.0f,0.0f,255.0f));
		theFontMgr->getFont("DrWho")->printText(outputMsg.c_str(), FTPoint(850, 70, 0.0f), colour3f(255.0f, 255.0f, 0.0f)); // uses c_str to convert string to LPCSTR
		theFontMgr->getFont("DrWho")->printText(score.c_str(), FTPoint(500, 70, 0.0f), colour3f(255.0f, 255.0f, 0.0f)); // uses c_str to convert string to LPCSTR
		glPopMatrix();

		pgmWNDMgr->swapBuffers();

		tCount += elapsedTime;

		//Clear key buffers
		theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);
		
	}

	

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success
}
