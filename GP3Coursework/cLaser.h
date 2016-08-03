#ifndef _CLASER_H
#define _CLASER_H

#include "GameConstants.h"
#include "cModel.h"

class cLaser : public cModel
{
public:
	cLaser();

	virtual void update(float elapsedTime);

	~cLaser();

};
#endif