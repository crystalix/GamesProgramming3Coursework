/*
==========================================================================
cSphere.h
==========================================================================
*/

#ifndef _SPHERE_H
#define _SPHERE_H

#include "windowOGL.h"
#include "glm\glm.hpp"
#include "glx\glext.h"
#include "wglext.h"
#include "GL\glut.h"
#include "cShapes.h"

class cSphere : public cShapes
{
public:
	cSphere();
	cSphere(GLdouble dRadius, GLint dSlices, GLint dStacks);
	virtual void render(float rotAngle);
	virtual void initialise(cTexture theTexture);
	virtual void initialise(GLint theTextureID, glm::vec3 thePosition, glm::vec3 theTranslation);

private:

	GLdouble sRadius;
	GLint sSlices;
	GLint sStacks;
	glm::vec3 m_Position;
	glm::vec3 m_Translation;
	GLUquadric *quad;
	GLuint m_TextureID;

};

#endif