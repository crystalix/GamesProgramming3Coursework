/*
==================================================================================
cMaterial.cpp
==================================================================================
*/

#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "GameConstants.h"

class cMaterial
{
public:
	cMaterial();
	cMaterial(lightColour4 ambient, lightColour4 diffuse, lightColour4 specular, lightColour4 emission, GLfloat  shininess);

	void useMaterial();

private:

	lightColour4 m_Ambient;
	lightColour4 m_Diffuse;
	lightColour4 m_Specular;
	lightColour4 m_Emission;

	GLfloat  m_Shininess;
};

#endif