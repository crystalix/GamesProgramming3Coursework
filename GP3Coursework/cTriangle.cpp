/*
==================================================================================
cTriangle.cpp
==================================================================================
*/

#include "cTriangle.h"

cTriangle::cTriangle()
{
	m_rotAngle = 0.0f;
}

void cTriangle::renderTri(float rotAngle)
{
	glRotatef(rotAngle, 0, 0, 1);

	glBegin(GL_TRIANGLES);
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, -0.5f, -4.0f);
		glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, -0.5f, -4.0f);
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		glVertex3f(0.0f, 0.5f, -4.0f);
	glEnd();
}

float cTriangle::getRotAngle()
{
	return m_rotAngle;
}

void cTriangle::setRotAngle(float rotAngle)
{
	m_rotAngle = rotAngle;
}

void cTriangle::prepareTri(float dt)
{
	const float SPEED = 15.0f;
	m_rotAngle += SPEED * dt;
	if (m_rotAngle > 360.0f)
	{
		m_rotAngle -= 360.0f;
	}
}
