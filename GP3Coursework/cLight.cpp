/*
==================================================================================
cLight.cpp
==================================================================================
*/

#include "cLight.h"

cLight::cLight()
{
	m_LightID = GL_LIGHT0;
	m_Ambient = lightColour4(0.0, 0.0, 0.0, 1.0);
	m_Diffuse = lightColour4(1.0, 1.0, 1.0, 1.0);
	m_Specular = lightColour4(1.0, 1.0, 1.0, 1.0);
	m_Position = glm::vec4(0.0, 0.0, 1.0, 0.0);
	m_SpotDirection = glm::vec3(0.0, 0.0, 1.0);
	m_SpotExponent = 0.0f;
	m_SpotCutoff = 180.0f;
	m_ConstantAttenuation = 1.0;
	m_LinearAttenuation = 0.0;
	m_QuadraticAttenuation = 0.0;
}
cLight::cLight(GLenum lightID, lightColour4 ambient, lightColour4 diffuse, lightColour4 specular, glm::vec4 position, glm::vec3 spotDirection
	, GLfloat  spotExponent, GLfloat  spotCutoff, GLfloat  constantAttenuation, GLfloat  linearAttenuation, GLfloat  quadraticAttenuation)
{
	m_LightID = lightID;
	m_Ambient = ambient;
	m_Diffuse = diffuse;
	m_Specular = specular;
	m_Position = position;
	m_SpotDirection = spotDirection;
	m_SpotExponent = spotExponent;
	m_SpotCutoff = spotCutoff;
	m_ConstantAttenuation = constantAttenuation;
	m_LinearAttenuation = linearAttenuation;
	m_QuadraticAttenuation = quadraticAttenuation;

}

void cLight::lightOn()
{
	glEnable(m_LightID);
	glLightfv(m_LightID, GL_AMBIENT, &(m_Ambient.r));
	glLightfv(m_LightID, GL_DIFFUSE, &(m_Diffuse.r));
	glLightfv(m_LightID, GL_SPECULAR, &(m_Specular.r));
	glLightfv(m_LightID, GL_POSITION, &(m_Position.x));
	glLightfv(m_LightID, GL_SPOT_DIRECTION, &(m_SpotDirection.x));
	glLightf(m_LightID, GL_SPOT_EXPONENT, m_SpotExponent);
	glLightf(m_LightID, GL_SPOT_CUTOFF, m_SpotCutoff);
	glLightf(m_LightID, GL_CONSTANT_ATTENUATION, m_ConstantAttenuation);
	glLightf(m_LightID, GL_LINEAR_ATTENUATION, m_LinearAttenuation);
	glLightf(m_LightID, GL_QUADRATIC_ATTENUATION, m_QuadraticAttenuation);
}

void cLight::lightOff()
{
	glDisable(m_LightID);
}
