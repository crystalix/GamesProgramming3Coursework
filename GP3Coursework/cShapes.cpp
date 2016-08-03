/*
==================================================================================
cShapes.cpp
==================================================================================
*/

#include "cShapes.h"


cShapes::cShapes()
{
	m_rotAngle = 0.0f;
}

void cShapes::render(float rotAngle)
{
	//glRotatef(rotAngle, 0.0f, 1.0f, 0.0f); 
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

float cShapes::getRotAngle()
{
	return m_rotAngle;
}

void cShapes::setRotAngle(float rotAngle)
{
	m_rotAngle = rotAngle;
}

void cShapes::prepare(float rAngle)
{
	m_rotAngle = rAngle;
	if (m_rotAngle > 360.0f)
	{
		m_rotAngle -= 360.0f;
	}
}
