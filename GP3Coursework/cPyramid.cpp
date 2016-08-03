/*
==================================================================================
cPyramid.cpp
==================================================================================
*/

#include "cPyramid.h"


cPyramid::cPyramid()
{
	setRotAngle(0.0f);
}

void cPyramid::render(float rotAngle)
{
	//glRotatef(rotAngle, 0.0f, 1.0f, 0.0f); 
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
}

void cPyramid::initialise(cTexture theTexture)
{
	m_Top = glm::vec3(0.0f, 1.0f, 0.0f);
	m_frontBottomLeft = glm::vec3(-1.0f, -1.0f, 1.0f);
	m_frontBottomRight = glm::vec3(1.0f, -1.0f, 1.0f);

	m_backBottomRight = glm::vec3(1.0f, -1.0f, -1.0f); 
	m_backBottomLeft = glm::vec3(-1.0f, -1.0f, -1.0f);

	//Push back vertices that make up a Pyramid 
	// Base
	m_vertices.push_back(m_frontBottomLeft);	// 0
	m_vertices.push_back(m_backBottomLeft);		// 1
	m_vertices.push_back(m_backBottomRight);	// 2
	m_vertices.push_back(m_frontBottomRight);	// 3

	m_vertices.push_back(m_Top);				// 4



	m_Indices[0] = 0; // red front face front base
	m_Indices[1] = 3;
	m_Indices[2] = 2;
	m_Indices[3] = 0;
	m_Indices[4] = 1;
	m_Indices[5] = 2;

	m_Indices[6] = 0; // orange back face front
	m_Indices[7] = 3;
	m_Indices[8] = 4;

	m_Indices[9] = 0; // yellow top face left
	m_Indices[10] = 1;
	m_Indices[11] = 4;

	m_Indices[12] = 3;  // purple bottom face right
	m_Indices[13] = 2;
	m_Indices[14] = 4;

	m_Indices[15] = 1; // blue left face back
	m_Indices[16] = 2;
	m_Indices[17] = 4;


	// Create Colour list 
	cColours theColour;

	for (int Colour = 0; Colour < 7; Colour++)
	{
		m_colourList.push_back(theColour.getColour(static_cast<cColours::colours>(Colour)));
	}

	// Assign variables that will be used to store the unique object ID’s that will be used to refer to the two buffers. 

	glGenBuffers = (PFNGLGENBUFFERSARBPROC)wglGetProcAddress("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glGenBuffers(2, &m_VertexBufferObjects[0]);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjects[0]); //Bind the vertex buffer 
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW); //Send the data to OpenGL 

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VertexBufferObjects[1]); //Bind the vertex buffer 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * sizeof(m_Indices), &m_Indices[0], GL_STATIC_DRAW); //Send the data to OpenGL 

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjects[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * m_colourList.size(), &m_colourList[0], GL_STATIC_DRAW); //Send the data to OpenGL 

	//Bind the colour array, and set the color pointer to point at it 
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjects[2]);
	glColorPointer(3, GL_FLOAT, 0, 0);

	//Bind the vertex array and set the vertex pointer to point at it 
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjects[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glTranslatef(0.0f, 0.0f, -6.0f);
	glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
}
