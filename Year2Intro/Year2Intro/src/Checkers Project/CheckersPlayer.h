#pragma once

// Will Not draw. Will only update the pieces that the player uses
struct GLFWwindow;
class CheckersProject;
class CheckersMovement;
#include "CheckersMovement.h"
#include "glm\vec2.hpp"


class CheckersPlayer
{
public:
	CheckersPlayer(CheckersProject* a_drawstate, CheckersMovement* a_gamestate);
	
	~CheckersPlayer();

	bool ValidMove();

	void Update();

	int xpos, ypos, zpos;
private:

	bool m_move;
	bool m_pickedUp;
	bool m_canDrop;
	bool m_flag;
	bool m_possibleDouble;

	float vForward, vRight;
	float moveDir;
	float m_timer;
	PIECE m_piece;

	//Vector Control movement

	glm::vec2 m_oldPos;

	CheckersMovement* m_gamestate;

	CheckersProject* m_drawstate;

	
	GLFWwindow* m_pWindow;
};