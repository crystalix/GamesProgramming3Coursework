/*
==========================================================================
cCube.h
==========================================================================
*/

#ifndef _CUBE_H
#define _CUBE_H

#include "windowOGL.h"
#include "glm\glm.hpp"
#include "glx\glext.h"
#include "wglext.h"
#include <vector>
#include "cColours.h"
#include "cShapes.h"

class cCube : public cShapes
{
public:
	cCube();
	virtual void render(float rotAngle);
	virtual void initialise(cTexture theTexture);
	void loadTextureCoords();  // Lab 2/3

private:

	glm::vec3 m_topLeftFront;
	glm::vec3 m_bottomLeftFront;
	glm::vec3 m_topRightFront;
	glm::vec3 m_bottomRightFront;
	glm::vec3 m_topLeftBack;
	glm::vec3 m_topRightBack;
	glm::vec3 m_bottomLeftBack;
	glm::vec3 m_bottomRightBack;

	glm::vec3 m_Faces[24];
	GLuint m_Indices[36];

	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec3> m_colourList;
	GLuint m_VertexBufferObjects[3];
	glm::vec2 m_TextureIndices[24];
	GLuint m_TextureID;

};

#endif