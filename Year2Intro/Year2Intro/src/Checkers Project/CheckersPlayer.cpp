
#include "GLFW\glfw3.h"
#include "Checkers Project\CheckersPlayer.h"
#include "CheckersProject.h"
#include "glm\glm.hpp"

CheckersPlayer::CheckersPlayer()
{
	m_pWindow = glfwGetCurrentContext();
	xpos = 4;
	ypos = 2;
	zpos = 4;
}

CheckersPlayer::~CheckersPlayer()
{

}

void CheckersPlayer::Update()
{
	

	if (glfwGetKey(m_pWindow, GLFW_KEY_UP) == GLFW_PRESS )
	{
		if (zpos != 8)
			zpos += 1;
		m_move = false;
	}

	if (glfwGetKey(m_pWindow, GLFW_KEY_DOWN) == GLFW_PRESS )
	{
		if (zpos != 0)
			zpos -= 1;
		m_move = false;
	}

	if (glfwGetKey(m_pWindow, GLFW_KEY_LEFT) == GLFW_PRESS )
	{
		if (xpos != 0)
			xpos -= 1;
		m_move = false;
	}

	if (glfwGetKey(m_pWindow, GLFW_KEY_RIGHT) == GLFW_PRESS )
	{
		if (xpos != 8)
			xpos += 1;
		m_move = false;
	}

}
