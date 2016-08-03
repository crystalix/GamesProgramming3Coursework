/*
==========================================================================
cTriangle.h
==========================================================================
*/

#ifndef _TRIANGLE_H
#define _TRIANGLE_H
#include "windowOGL.h"

class cTriangle : public windowOGL
{
public:
	cTriangle();
	void renderTri(float rotAngle);
	float getRotAngle();
	void setRotAngle(float rotAngle);
	void prepareTri(float dt);

private:
	float m_rotAngle;
};

#endif