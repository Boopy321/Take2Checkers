#include <gl_core_4_4.h>
#include "CheckersProject.h"
#include <glm\glm.hpp>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "Assets\Render\Renderer.h"
#include "Assets\Camera\FlyCamera.h"
#include "FBXFile.h"
#include "Assets\Texture2D\Texture2D.h"
#include <vector>
#include "Assets\GpuParticle\GpuParticleEmitter.h"
#include "Gizmos.h"
#include "CheckersPlayer.h"




CheckersProject::CheckersProject()
{
	//Start up Grid
	m_totalcount = 12;
	m_scaleMod = 1.5f;

	//Resize the vectors for Checkers
	m_rows = 8;
	m_cols = 8;
	m_player1 = new CheckersPlayer(); 
	m_player2 = new CheckersPlayer();
	m_tileRed = true;

	SetCheckers();
	
	m_turn = TURN::PLAYER_1;
}


CheckersProject::~CheckersProject()
{

}

void CheckersProject::Draw(FlyCamera &_gameCamera, float a_deltatime)
{
	using glm::vec3;
	using glm::vec4;

	Gizmos::addTransform(glm::mat4(0.1), 100.0f);

	//program = m_render->ReturnProgramSimpleLoad();

	glm::mat4 rotate;
	rotate = glm::rotate(mat4(1.0f), glm::pi<float>() / 4, glm::vec3(0, 1, 0));
	//BROWN UNDERBOARD
	Gizmos::addCylinderFilled(vec3(5.25, -1, 5.25), 10, 0.75, 4, vec4(0.545, 0.270, 0.074, 1), &rotate);
	//SELECTOR RING
	
		if(m_turn == TURN::PLAYER_1)
		{
			Gizmos::addSphere(vec3(m_player1->xpos * m_scaleMod, m_player1->ypos, m_player1->zpos * m_scaleMod), 0.5, 10, 10, glm::vec4(0, 0, 1, 1));
		}
		else if (m_turn == TURN::PLAYER_2)
		{
			Gizmos::addSphere(vec3(m_player2->xpos * m_scaleMod, m_player2->ypos, m_player2->zpos * m_scaleMod), 0.5, 10, 10, glm::vec4(1, 0, 1, 1));
		}


	///Draw the Grid
	for (float c = 0; c <= m_cols- 1; c++) {

		for (float r = 0; r <= m_rows - 1; r++) {
				
			if (m_tileRed == false)
			{
				Gizmos::addCylinderFilled(vec3((r * m_scaleMod), 0, c * m_scaleMod), 1, 0.25, 4, vec4(0, 0, 0, 1), &rotate);
				m_tileRed = true;
			}
			else
			{
				Gizmos::addCylinderFilled(vec3(r * m_scaleMod,0, c *m_scaleMod), 1, 0.25, 4, vec4(1, 0, 0, 1), &rotate);
				m_tileRed = false;
			}
		}
		m_tileRed = !m_tileRed;
	}


	///Draw Tokens 

	for (int c = 0; c <= m_cols - 1; c++)
	{
		for (int r = 0; r <= m_rows - 1; r++)
		{
			if (m_board[c][r] == PIECE::RED || m_board[c][r] == PIECE::REDKING)
			{
				Gizmos::addCylinderFilled(vec3((r * m_scaleMod), 0.5, c * m_scaleMod), 0.5, 0.25, 16, vec4(1,0 , 0, 1), &rotate);
			}
			else if (m_board[c][r] == PIECE::BLACK || m_board[c][r] == PIECE::BLACKKING)
			{
				Gizmos::addCylinderFilled(vec3((r * m_scaleMod),0.5, c * m_scaleMod), 0.5, 0.25, 16, vec4(1 ,1, 1, 1), &rotate);
			}
		}
	}

	m_player1->Update();

	
}

void CheckersProject::Update()
{

	//Checks Current tokens alive 
	//Removes Useless data,
}

void CheckersProject::SetCheckers()
{
	bool placepiece = true;
	int i = 0;
	for (int c = 0; c <= m_cols - 1; c++) 
	{

		for (int r = 0; r <= m_rows - 1 ; r++)
		{
			if (i == m_totalcount)
				break;
			if (placepiece == true)
			{
				m_board[c][r] = PIECE::RED;
				placepiece = false;
				i++;
			}
			else if (i <= m_totalcount )
			{
				placepiece = true;
				m_board[c][r] = PIECE::NONE;
			}
			
		}
		placepiece = !placepiece;
	}

	i = m_totalcount;
	for (int c = m_cols - 1 ; c >=0 ; c--)
	{

		for (int r = m_rows - 1; r >=0; r--)
		{
			if (i == 0)
				break;
			if (placepiece == false)
			{
				m_board[c][r] = PIECE::BLACK;
				placepiece = true;
				i--;
			}
			else if (i >= 0)
			{
				placepiece = false;
				m_board[c][r] = PIECE::NONE;
			}

		}
		placepiece = !placepiece;
	}
}



void CheckersProject::DeleteToken(PIECE state)
{	
//	if (state == PIECE::REMOVERED)
//	{
//		m_redcount = m_redcount - 1;
//		for (int i = 0; i < m_red.size(); i++)
//		{
//			if (m_red[i] == nullptr)// || (m_red[i] == m_red[i + 1] || m_red[i+1] == nullptr))
//			{
//			
//				for (int a = i; a == m_redcount; a--)
//				{
//					m_red[a] = m_red[a + 1];
//				}
//			}
//		}
//		m_red.pop_back();
//	}
//
//	if (state == PIECE::REMOVEBLACK)
//	{
//		m_blackcount = m_blackcount - 1;
//		for (int i = 0; i < m_black.size(); i++)
//		{
//			if (m_black[i] == nullptr)// || (m_red[i] == m_red[i + 1] || m_red[i+1] == nullptr))
//			{
//
//				for (int a = i; a == m_redcount; a--)
//				{
//					m_black[a] = m_black[a + 1];
//				}
//			}
//		}
//		m_black.pop_back();
//	}
//
}

