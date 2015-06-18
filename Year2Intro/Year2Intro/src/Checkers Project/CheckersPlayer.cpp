//poo
#include "GLFW\glfw3.h"
#include "Checkers Project\CheckersPlayer.h"
#include "CheckersProject.h"

#include "glm\glm.hpp"
#include <iostream>

CheckersPlayer::CheckersPlayer(CheckersProject* a_drawstate,CheckersMovement* a_gamestate)
{
	m_pWindow = glfwGetCurrentContext();
	xpos = 4;
	ypos = 2;
	zpos = 4;
	m_canDrop = true;
	m_oldPos = glm::vec2(0, 0);
	
	m_move = true;
	m_timer = 1;
	
	m_piece = PIECE::NONE;
	
	
	m_pickedUp = false;
	m_drawstate = a_drawstate;
	m_gamestate = a_gamestate;
	m_action = new Action();
}

CheckersPlayer::~CheckersPlayer()
{

}

void CheckersPlayer::Update()
{
	

	if (glfwGetKey(m_pWindow, GLFW_KEY_DOWN) == GLFW_PRESS && m_move == true)
	{
		if (zpos != 0)
			zpos -= 1;
		m_move = false;
	}

	if (glfwGetKey(m_pWindow, GLFW_KEY_UP) == GLFW_PRESS && m_move == true)
	{
		if (zpos != 7)
			zpos += 1;
		m_move = false;
	}

	if (glfwGetKey(m_pWindow, GLFW_KEY_RIGHT) == GLFW_PRESS && m_move == true)
	{
		if (xpos != 0)
			xpos -= 1;
		m_move = false;
	}

	if (glfwGetKey(m_pWindow, GLFW_KEY_LEFT) == GLFW_PRESS && m_move == true)
	{
		if (xpos != 7)
			xpos += 1;
		m_move = false;
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
		m_timer = 1.5f;
	}

	std::cout << zpos <<","<< xpos<< std::endl;

	
	//Grabs the piece if there is a piece at the spot
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
	
	//Pick ups thg
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
		m_action->newLocation = glm::ivec2(zpos, xpos);
		m_action->originalLocation = m_oldPos;
		m_action->pieceType = m_piece;
		//PERFORM THAT ACTION
		m_gamestate->performAction(m_action);
		m_piece = PIECE::NONE;
		
		}
	}
	
	m_drawstate->DrawSphere(xpos, zpos);
	m_timer -= 0.1f;
}


