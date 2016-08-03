/*
==================================================================================
cSphere.cpp
==================================================================================
*/

#include "cSphere.h"


cSphere::cSphere()
{
	setRotAngle(0.0f);
}

cSphere::cSphere(GLdouble dRadius, GLint dSlices, GLint dStacks)
{
	setRotAngle(0.0f);
	sRadius = dRadius;
	sSlices = dSlices;
	sStacks = dStacks;
}

void cSphere::render(float rotAngle)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);


	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	glTranslatef(m_Position.x, m_Position.y, m_Position.z);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Rotate Sphere to take account of gluSphere caps
	glRotatef(getRotAngle(), 0, 0, 1);	// Rotation is now on z rather than Y to make sphere spin

	gluSphere(quad, sRadius, sSlices, sStacks);

	glDisable(GL_NORMALIZE);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void cSphere::initialise(cTexture theTexture)
{
	quad = gluNewQuadric();

	gluQuadricDrawStyle(quad, GLU_FILL);
	gluQuadricNormals(quad, GLU_SMOOTH);
	gluQuadricTexture(quad, GL_TRUE);

	glBindTexture(GL_TEXTURE_2D, theTexture.getTexture());

}

void cSphere::initialise(GLint theTextureID, glm::vec3 thePosition, glm::vec3 theTranslation)
{
	quad = gluNewQuadric();
	m_TextureID = theTextureID;
	m_Position = thePosition;
	m_Translation = theTranslation;

	gluQuadricDrawStyle(quad, GLU_FILL);
	gluQuadricNormals(quad, GLU_SMOOTH);
	gluQuadricTexture(quad, GL_TRUE);

	glBindTexture(GL_TEXTURE_2D, m_TextureID);

}