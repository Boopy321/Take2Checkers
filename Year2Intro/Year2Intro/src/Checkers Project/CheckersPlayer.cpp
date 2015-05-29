
#include "GLFW\glfw3.h"
#include "Checkers Project\CheckersPlayer.h"
#include "CheckersProject.h"

#include "glm\glm.hpp"

CheckersPlayer::CheckersPlayer(CheckersProject* a_drawstate,CheckersMovement* a_gamestate)
{
	m_pWindow = glfwGetCurrentContext();
	xpos = 4;
	ypos = 2;
	zpos = 4;

	m_oldPos = glm::vec2(0, 0);
	
	m_move = true;
	m_timer = 1;
	
	m_piece == PIECE::NONE;
	
	
	m_pickedUp = false;
	m_drawstate = a_drawstate;
	m_gamestate = a_gamestate;

}

CheckersPlayer::~CheckersPlayer()
{

}

void CheckersPlayer::Update()
{
	

	if (glfwGetKey(m_pWindow, GLFW_KEY_UP) == GLFW_PRESS && m_move == true)
	{
		if (zpos != 0)
			zpos -= 1;
		m_move = false;
	}

	if (glfwGetKey(m_pWindow, GLFW_KEY_DOWN) == GLFW_PRESS && m_move == true)
	{
		if (zpos != 7)
			zpos += 1;
		m_move = false;
	}

	if (glfwGetKey(m_pWindow, GLFW_KEY_LEFT) == GLFW_PRESS && m_move == true)
	{
		if (xpos != 0)
			xpos -= 1;
		m_move = false;
	}

	if (glfwGetKey(m_pWindow, GLFW_KEY_RIGHT) == GLFW_PRESS && m_move == true)
	{
		if (xpos != 7)
			xpos += 1;
		m_move = false;
	}


	if (glfwGetKey(m_pWindow, GLFW_KEY_ENTER) == GLFW_PRESS && m_move == true)
	{
		//THIS WILL CALL A SELECT OR PICK UP PIECE

		
	}
	
	if (glfwGetKey(m_pWindow, GLFW_KEY_SPACE) == GLFW_PRESS && m_move == true)
	{
		//pick up or place piece
		m_move = false;
		m_pickedUp = !m_pickedUp;
	}

	if (m_timer <= 0)
	{
		m_move = true;
		m_timer = 1;
	}

	if (m_pickedUp == true && m_piece == PIECE::NONE)
	{
		m_piece = m_gamestate->GrabPiece(zpos, xpos);
		
		if (m_piece != PIECE::NONE)
		{
			m_oldPos = glm::vec2(zpos, xpos);
			
		}
		else
			m_pickedUp = false;
		
	}
	

	if (m_pickedUp == true)
	{
		m_drawstate->DrawPieceInHand(xpos, zpos, m_piece);
	}
	//If you have a piece in your hand
	if (m_piece != PIECE::NONE)
	{
		//If they have dropped the token
		if (m_pickedUp == false)
		{
			//If the action is valid
			if (m_gamestate->PlacePiece(m_piece, zpos, xpos))
			{
				if (zpos == m_oldPos.x && xpos == m_oldPos.y)
				{
					///DONT DELETE THE OLD SPACE if its the same spot
				}
				else
				{
					m_piece = PIECE::NONE;
					m_gamestate->PlacePiece(m_piece, m_oldPos.x, m_oldPos.y);
				}
			}
			else
					m_pickedUp == true;
		}
	}
	
	m_drawstate->DrawSphere(xpos, zpos);
	m_timer -= 0.1f;
}
