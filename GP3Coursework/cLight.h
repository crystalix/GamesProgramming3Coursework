/*
==================================================================================
cLight.cpp
==================================================================================
*/

#ifndef _LIGHT_H
#define _LIGHT_H

#include "GameConstants.h"

class cLight
{
public:
	cLight();
	cLight(GLenum lightID, lightColour4 ambient, lightColour4 diffuse, lightColour4 specular, glm::vec4 position, glm::vec3 spotDirection
		, GLfloat  spotExponent, GLfloat  spotCutoff, GLfloat  constantAttenuation, GLfloat  linearAttenuation, GLfloat  quadraticAttenuation);

	void lightOn();
	void lightOff();

private:

	GLenum m_LightID;
	lightColour4 m_Ambient;
	lightColour4 m_Diffuse;
	lightColour4 m_Specular;
	
	glm::vec4 m_Position;
	glm::vec3 m_SpotDirection;

	GLfloat  m_SpotExponent;
	GLfloat  m_SpotCutoff;
	GLfloat  m_ConstantAttenuation;
	GLfloat  m_LinearAttenuation;
	GLfloat  m_QuadraticAttenuation;
};

#endif