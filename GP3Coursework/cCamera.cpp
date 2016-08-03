/*
==========================================================================
ccCamera.h
==========================================================================
*/

#include "cCamera.h"

cCamera::cCamera()
{
	m_viewPort = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	m_cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_ProjectionMatrix = glm::mat4(1.0);
	m_camViewMatrix = glm::mat4(1.0);
	m_angle = 0.0f;
}


cCamera::cCamera(int screenWidth, int screenHeight)
{
	m_viewPort = glm::vec4(0, 0, screenWidth, screenHeight);
	m_cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_ProjectionMatrix = glm::mat4(1.0);
	m_camViewMatrix = glm::mat4(1.0);
	m_angle = 0.0f;
}

cCamera::~cCamera()
{
	
}

void cCamera::setTheViewPort(int x, int y, int width, int height)
{
	m_viewPort = glm::vec4(x, y, width, height);
	glViewport(x, y, width, height);
}

const glm::vec4 cCamera::getTheViewPort()
{
	return m_viewPort;
}

void cCamera::setTheProjectionMatrix(float fov, float aspectRatio, float nearCP, float farCP)
{
	m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearCP, farCP);
}

void cCamera::setTheCameraPos(glm::vec3 pos)
{
	m_cameraPos = pos;
}

glm::vec3 cCamera::getTheCameraPos()
{
	return m_cameraPos;
}

void cCamera::setTheCameraUpVector(glm::vec3 camPosUpVec)
{
	m_cameraUpVector = camPosUpVec;
}

glm::vec3 cCamera::getTheCameraUpVector()
{
	return m_cameraUpVector;
}

void cCamera::setTheCameraLookAt(glm::vec3 camLookAt)
{
	m_cameraLookAt = camLookAt;
}

glm::vec3 cCamera::getTheCameraLookAt()
{
	return m_cameraLookAt;
}

void cCamera::setTheCameraDirection()
{
	m_cameraDirection = glm::normalize(m_cameraPos - m_cameraLookAt);
}

glm::vec3 cCamera::getTheCameraDirection()
{
	return m_cameraDirection;
}

void cCamera::setTheCameraStrafe()
{
	m_cameraStrafe = glm::normalize(glm::cross(m_cameraUpVector, m_cameraDirection));
}

glm::vec3 cCamera::getTheCameraStrafe()
{
	return m_cameraStrafe;
}

void cCamera::setTheCameraAspectRatio(GLfloat width, GLfloat height)
{
	m_AspectRatio = width/height;
}

GLfloat cCamera::getTheCameraAspectRatio()
{
	return m_AspectRatio;
}

glm::mat4 cCamera::getTheProjectionMatrix()
{
	return m_ProjectionMatrix;
}

glm::mat4 cCamera::getTheViewMatrix()
{
	return m_camViewMatrix;
}

void cCamera::setCamViewMatrix()
{
	m_camViewMatrix = glm::lookAt(m_cameraPos, m_cameraLookAt, m_cameraUpVector);
}

glm::mat4 cCamera::getCamViewMatrix()
{
	return m_camViewMatrix;
}

void cCamera::setAngle(GLfloat angle)
{
	m_angle = angle;
}

GLfloat cCamera::getAngle()
{
	return m_angle;
}


void cCamera::update()
{
	glRotatef(m_angle, 0, 1, 0);
	setTheCameraDirection();
	setTheCameraStrafe();
	setTheCameraUpVector(glm::cross(m_cameraDirection, m_cameraStrafe));
	setTheProjectionMatrix(45.0f, getTheCameraAspectRatio(), 0.1f, 10000.0f);
	setCamViewMatrix();
}
