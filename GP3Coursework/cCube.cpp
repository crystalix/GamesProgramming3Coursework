/*
==================================================================================
cCube.cpp
==================================================================================
*/

#include "cCube.h"


cCube::cCube()
{
	setRotAngle(0.0f);
}

void cCube::render(float rotAngle)
{
	//glRotatef(rotAngle, 0.0f, 1.0f, 0.0f); 
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); // Lab 2/3

	glVertexPointer(3, GL_FLOAT, 0, 0);
	glTexCoordPointer(2, GL_FLOAT, 0,0);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY); // Lab 2/3

	glDisable(GL_TEXTURE_2D);
}

void cCube::loadTextureCoords()   // Lab 2/3
{
	m_TextureIndices[0] = glm::vec2(0.0f, 0.0f);
	m_TextureIndices[1] = glm::vec2(1.0f, 0.0f);
	m_TextureIndices[2] = glm::vec2(1.0f, 1.0f);
	m_TextureIndices[3] = glm::vec2(0.0f, 1.0f);

	m_TextureIndices[4] = glm::vec2(1.0f, 0.0f);
	m_TextureIndices[5] = glm::vec2(0.0f, 0.0f);
	m_TextureIndices[6] = glm::vec2(0.0f, 1.0f);
	m_TextureIndices[7] = glm::vec2(0.0f, 0.0f);

	m_TextureIndices[8] = glm::vec2(0.0f, 1.0f);
	m_TextureIndices[9] = glm::vec2(0.0f, 0.33f);
	m_TextureIndices[10] = glm::vec2(1.0f, 0.0f);
	m_TextureIndices[11] = glm::vec2(1.0f, 1.0f);

	m_TextureIndices[12] = glm::vec2(1.0f, 1.0f);
	m_TextureIndices[13] = glm::vec2(0.0f, 1.0f);
	m_TextureIndices[14] = glm::vec2(0.0f, 0.0f);
	m_TextureIndices[15] = glm::vec2(1.0f, 0.0f);

	m_TextureIndices[16] = glm::vec2(1.0f, 0.0f);
	m_TextureIndices[17] = glm::vec2(1.0f, 1.0f);
	m_TextureIndices[18] = glm::vec2(0.0f, 1.0f);
	m_TextureIndices[19] = glm::vec2(0.0f, 0.0f);

	m_TextureIndices[20] = glm::vec2(0.0f, 0.0f);
	m_TextureIndices[21] = glm::vec2(1.0f, 0.0f);
	m_TextureIndices[22] = glm::vec2(1.0f, 1.0f);
	m_TextureIndices[23] = glm::vec2(0.0f, 1.0f);
}

void cCube::initialise(cTexture theTexture)
{
	m_topLeftFront = glm::vec3(-1.0f, 1.0f, 1.0f);
	m_bottomLeftFront = glm::vec3(-1.0f, -1.0f, 1.0f);
	m_topRightFront = glm::vec3(1.0f, 1.0f, 1.0f);
	m_bottomRightFront = glm::vec3(1.0f, -1.0f, 1.0f);
	m_topLeftBack = glm::vec3(-1.0f, 1.0f, -1.0f);
	m_topRightBack = glm::vec3(1.0f, 1.0f, -1.0f);
	m_bottomLeftBack = glm::vec3(-1.0f, -1.0f, -1.0f);
	m_bottomRightBack = glm::vec3(1.0f, -1.0f, -1.0f);

	//Push back 8 vertices that make up a cube 
	m_vertices.push_back(m_bottomLeftFront);
	m_vertices.push_back(m_bottomLeftBack);
	m_vertices.push_back(m_bottomRightBack);
	m_vertices.push_back(m_bottomRightFront);


	m_vertices.push_back(m_topLeftFront);
	m_vertices.push_back(m_topLeftBack);
	m_vertices.push_back(m_topRightBack);
	m_vertices.push_back(m_topRightFront);



	m_Indices[0] = 0; // red front face 
	m_Indices[1] = 2;
	m_Indices[2] = 3;
	m_Indices[3] = 0;
	m_Indices[4] = 1;
	m_Indices[5] = 2;

	m_Indices[6] = 4; // orange back face 
	m_Indices[7] = 6;
	m_Indices[8] = 7;
	m_Indices[9] = 4;
	m_Indices[10] = 5;
	m_Indices[11] = 6;

	m_Indices[12] = 0; // yellow top face 
	m_Indices[13] = 4;
	m_Indices[14] = 1;
	m_Indices[15] = 4;
	m_Indices[16] = 5;
	m_Indices[17] = 1;

	m_Indices[18] = 2; // purple bottom face 
	m_Indices[19] = 6;
	m_Indices[20] = 3;
	m_Indices[21] = 6;
	m_Indices[22] = 7;
	m_Indices[23] = 3;

	m_Indices[24] = 6; // blue left face 
	m_Indices[25] = 1;
	m_Indices[26] = 5;
	m_Indices[27] = 6;
	m_Indices[28] = 2;
	m_Indices[29] = 1;

	m_Indices[30] = 0; // green right face 
	m_Indices[31] = 7;
	m_Indices[32] = 4;
	m_Indices[33] = 0;
	m_Indices[34] = 3;
	m_Indices[35] = 7;

	// Call loadTextureCoords() - Lab 2/3
	loadTextureCoords();

	// Assign variables that will be used to store the unique object ID’s that will be used to refer to the two buffers. 

	glGenBuffers = (PFNGLGENBUFFERSARBPROC)wglGetProcAddress("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");

	glGenBuffers(2, &m_VertexBufferObjects[0]);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjects[0]); //Bind the vertex buffer 
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW); //Send the data to OpenGL 

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VertexBufferObjects[1]); //Bind the vertex buffer 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * sizeof(m_Indices), &m_Indices[0], GL_STATIC_DRAW); //Send the data to OpenGL 

	// Lab 2/3
	// Create and Bind VBO for Texture
	//Bind the Texture coordinate array, and set the Texture coordinate pointer to point at it
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjects[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_TextureIndices), &m_TextureIndices[0], GL_STATIC_DRAW); //Send the data to OpenGL

	glBindTexture(GL_TEXTURE_2D, theTexture.getTexture());

	// Lab 2/3
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjects[2]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);

	//Bind the vertex array and set the vertex pointer to point at it 
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjects[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glTranslatef(0.0f, 0.0f, -6.0f);
	glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
}
