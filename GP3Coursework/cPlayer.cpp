#include "cPlayer.h"



cPlayer::cPlayer() : cModel()
{

}

void cPlayer::attachInputMgr(cInputMgr* inputMgr)
{
	m_InputMgr = inputMgr;
}

void cPlayer::update(float elapsedTime)
{
	if (m_InputMgr->isKeyDown(VK_RIGHT))
	{
		//this is used to move the player right
		xValue = 0.1f;
		
	}
	if (m_InputMgr->isKeyDown(VK_LEFT))
	{
		//this is used to move the player left
		xValue = -0.1f;
	}


	if (m_InputMgr->isKeyDown(VK_SPACE))
	{
		//This is used to allow the player to shoot bullets when they press the space bar
		glm::vec3 mdlLaserDirection;
		mdlLaserDirection.x = -(float)glm::sin(glm::radians(this->getRotation()));
		mdlLaserDirection.y = 0.0f;
		mdlLaserDirection.z = (float)glm::cos(glm::radians(this->getRotation()));
		mdlLaserDirection *= -1;

		// Add new bullet sprite to the vector array
		theTardisLasers.push_back(new cLaser);
		int numLasers = theTardisLasers.size() - 1;
		theTardisLasers[numLasers]->setDirection(mdlLaserDirection);
		theTardisLasers[numLasers]->setRotation(0.0f);
		theTardisLasers[numLasers]->setScale(glm::vec3(1, 1, 1));
		theTardisLasers[numLasers]->setSpeed(5.0f);
		theTardisLasers[numLasers]->setPosition(this->getPosition());
		theTardisLasers[numLasers]->setIsActive(true);
		theTardisLasers[numLasers]->update(elapsedTime);

		// if the sound is on the firing sound is played
		if (soundOn)
		{
			m_SoundMgr->getSnd("Shot")->playAudio(AL_TRUE);
		}
	}

	//this toggles the audio
	if (m_InputMgr->isKeyDown(VK_RETURN))
	{
		if (soundOn)
		{
			soundOn = false;
		}
		else
		{
			soundOn = true;
			Active = true;
		}
	}

	//this toggles the camera
	if (m_InputMgr->isKeyDown(VK_CONTROL))
	{
		if (firstPersonCam)
		{
			firstPersonCam = false;
		}
		else
		{
			firstPersonCam = true;
		}
	}

	//this toggles the fog
	if (m_InputMgr->isKeyDown(70))
	{
		if (gp == false)
		{
			gp = true;
		}
		else if (gp == true)
		{
			gp = false;
		}
	}

	
	for (vector<cLaser*>::iterator laserIterartor = theTardisLasers.begin(); laserIterartor != theTardisLasers.end(); ++laserIterartor)
	{
		(*laserIterartor)->update(elapsedTime);

		
	}

	//adds lasers to the player's weapon to fire
	vector<cLaser*>::iterator laserIterartor = theTardisLasers.begin();
	while (laserIterartor != theTardisLasers.end())
	{
		if ((*laserIterartor)->isActive() == false)
		{
			laserIterartor = theTardisLasers.erase(laserIterartor);
		}
		else
		{
			++laserIterartor;
		}
	}

	// Find out what direction we should be thrusting, using rotation.
	glm::vec3 mdlVelocityAdd;
	mdlVelocityAdd.x = -(float)glm::sin(glm::radians(m_mdlRotation));  // Remember to adjust for radians
	mdlVelocityAdd.y = 0.0f;
	mdlVelocityAdd.z = -(float)glm::cos(glm::radians(m_mdlRotation));

	m_mdlRotation -= rotationAngle;

	mdlVelocityAdd *= translationZ;
	m_mdlDirection += mdlVelocityAdd;

	m_mdlPosition += m_mdlDirection * m_mdlSpeed *elapsedTime;
	m_mdlDirection *= 0.95f;

	rotationAngle = 0;
	translationZ = 0;
}

cPlayer::~cPlayer()
{

}