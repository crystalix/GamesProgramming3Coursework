/*
==================================================================================
cMaterial.cpp
==================================================================================
*/

#include "cMaterial.h"

cMaterial::cMaterial()
{
	m_Ambient = lightColour4(0.2f, 0.2f, 0.2f, 1.0f);
	m_Diffuse = lightColour4(0.8f, 0.8f, 0.8f, 1.0f);
	m_Specular = lightColour4(0.0f, 0.0f, 0.0f, 1.0f);
	m_Emission = lightColour4(0.0f, 0.0f, 0.0f, 1.0f);
	m_Shininess = 0;
}
cMaterial::cMaterial(lightColour4 ambient, lightColour4 diffuse, lightColour4 specular, lightColour4 emission, GLfloat shininess)
{
	m_Ambient = ambient;
	m_Diffuse = diffuse;
	m_Specular = specular;
	m_Emission = emission;
	m_Shininess = shininess;

}

void cMaterial::useMaterial()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &(m_Ambient.r));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &(m_Diffuse.r));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &(m_Specular.r));
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, &(m_Emission.r));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_Shininess);
}
