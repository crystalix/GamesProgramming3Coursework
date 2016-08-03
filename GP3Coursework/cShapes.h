/*
==========================================================================
cShapes.h
==========================================================================
*/

#ifndef _SHAPES_H
#define _SHAPES_H

#include "windowOGL.h"
#include "glm\glm.hpp"
#include "glx\glext.h"
#include "wglext.h"
#include <vector>
#include "cColours.h"
#include "cTexture.h"

class cShapes : public windowOGL
{
public:
	cShapes();
	virtual void render(float rotAngle) = 0;
	float getRotAngle();
	void setRotAngle(float rotAngle);
	void prepare(float rAngle);
	virtual void initialise(cTexture theTexture) = 0;

	PFNGLGENBUFFERSARBPROC glGenBuffers = NULL;
	PFNGLBINDBUFFERPROC glBindBuffer = NULL;
	PFNGLBUFFERDATAPROC glBufferData = NULL;

private:
	float m_rotAngle;
};

#endif