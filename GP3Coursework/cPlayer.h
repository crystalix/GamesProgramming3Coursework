#ifndef _CPLAYER_H
#define _CPLAYER_H

#include "GameConstants.h"
#include "tardisWarsGame.h"
#include "cModel.h"
#include "cInputMgr.h"

class cPlayer : public cModel
{
private:
	cInputMgr* m_InputMgr;
public:
	cPlayer();
	void attachInputMgr(cInputMgr* inputMgr);
	virtual void update(float elapsedTime);
	bool soundOn=true;
	bool Active;
	float xValue;
	bool firstPersonCam=true;
	bool gp=false;

	~cPlayer();
};
#endif