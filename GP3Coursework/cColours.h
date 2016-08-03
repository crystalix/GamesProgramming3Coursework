/*
==========================================================================
cColours.h
==========================================================================
*/

#ifndef _COLOURS_H
#define _COLOURS_H

#include "windowOGL.h"
#include "glm\glm.hpp"
#include "glx\glext.h"
#include "wglext.h"

class cColours
{
private:
		glm::vec3 m_ColourList[7];

public:
	enum colours
	{
		RED, YELLOW, GREEN, BLUE, PURPLE, WHITE, GREY
	};

	cColours();
	glm::vec3 getColour(colours colour);
	void setColourList();
};
#endif