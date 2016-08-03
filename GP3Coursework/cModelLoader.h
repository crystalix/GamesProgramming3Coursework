#ifndef _CMODELLOADER_H
#define _CMODELLOADER_H

#include "GameConstants.h"

class cModelLoader
{
public:
	cModelLoader();

	void loadModel(const char* mdlFilename);
	void loadModel(const char* mdlFilename, GLuint textureID);
	void loadModel(const char* mdlFilename, cTexture mdlTexture);
	void renderMdl(glm::vec3 mdlPosition, float mdlRotationAngle, glm::vec3 mdlScale);
	mdlDimensions getModelDimensions();

	~cModelLoader();
private:
	// Set the position of the model in world space, and set the rotation.
	GLMmodel* m_model;
	GLuint m_TextureID;
	float m_TextWidth;
	float m_TextHeight;

	//GLuint initTexture(char* txtFilename);

};
#endif