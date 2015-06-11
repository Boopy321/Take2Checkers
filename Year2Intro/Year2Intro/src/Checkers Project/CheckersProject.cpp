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
	m_scaleMod = 1.5f;



	m_tileRed = true;

	m_rows = 8;
	m_cols = 8;
	
	rotate = glm::rotate(mat4(1.0f), glm::pi<float>() / 4, glm::vec3(0, 1, 0));
	
}


CheckersProject::~CheckersProject()
{

}

void CheckersProject::Draw(FlyCamera &_gameCamera, float a_deltatime)
{
	using glm::vec3;
	using glm::vec4;

	//BROWN UNDERBOARD
	Gizmos::addCylinderFilled(vec3(5.25, -1, 5.25), 10, 0.75, 4, vec4(0.545, 0.270, 0.074, 1), &rotate);

	///Draw the Grid
	for (float c = 0; c <= m_cols- 1; c++)
	{
		for (float r = 0; r <= m_rows - 1; r++)
		{	
			if (m_tileRed == false)
			{
				Gizmos::addCylinderFilled(vec3((r * m_scaleMod), 0, c * m_scaleMod), 1, 0.25, 4, vec4(0, 0, 0, 1), &rotate);
				m_tileRed = true;
			}
			else if (m_tileRed == true)
			{
				Gizmos::addCylinderFilled(vec3(r * m_scaleMod,0, c *m_scaleMod), 1, 0.25, 4, vec4(1, 0, 0, 1), &rotate);
				m_tileRed = false;
			}
			
			//if (m_board[(int)c][(int)r] == PIECE::POSSIBLEMOVE)
			//{
			//	Gizmos::addCylinderFilled(vec3(r * m_scaleMod, 0, c *m_scaleMod), 1, 0.25, 4, vec4(0, 1, 0, 1), &rotate);
			//}
		}
		m_tileRed = !m_tileRed;
	}


	///Draw Tokens 

	for (int c = 0; c <= m_cols - 1; c++)
	{
		for (int r = 0; r <= m_rows - 1; r++)
		{
			if (m_board[c][r] == PIECE::RED)
			{
				Gizmos::addCylinderFilled(vec3((r * m_scaleMod), 0.5, c * m_scaleMod), 0.5, 0.25, 16, vec4(1,0 , 0, 1), &rotate);
			}
			else if (m_board[c][r] == PIECE::REDKING)
			{
				Gizmos::addCylinderFilled(vec3((r * m_scaleMod), 0.5, c * m_scaleMod), 0.75, 0.55, 16, vec4(1, 0, 1, 1), &rotate);
			}
			else if (m_board[c][r] == PIECE::BLACK)
			{
				Gizmos::addCylinderFilled(vec3((r * m_scaleMod),0.5, c * m_scaleMod), 0.5, 0.25, 16, vec4(0 ,0, 0, 1), &rotate);
			}
			else if (m_board[c][r] == PIECE::BLACKKING)
			{
				Gizmos::addCylinderFilled(vec3((r * m_scaleMod), 0.5, c * m_scaleMod), 0.75, 0.55, 16, vec4(0, 0, 0, 1), &rotate);
			}
			else if (m_board[c][r] == PIECE::POSSIBLEMOVE)
			{
				Gizmos::addCylinderFilled(vec3((r * m_scaleMod), 0.5, c * m_scaleMod), 0.5, 0.25, 16, vec4(0, 1, 0, 1), &rotate);
			}
		}
	}

}

void CheckersProject::Update()
{

	//Checks Current tokens alive 
	//Removes Useless data,
}

void CheckersProject::GetCurrentBoard(PIECE a_grid[8][8])
{
	
	for (int c = 0; c <= m_cols - 1; c++)
	{
		for (int r = 0; r <= m_rows - 1; r++)
		{
			m_board[c][r] = a_grid[c][r];
		}
	}
}

void CheckersProject::DrawPieceInHand(int x, int z, PIECE a_type)
{
	if (a_type == PIECE::RED)
	{
		Gizmos::addCylinderFilled(vec3((x * m_scaleMod), 4, z * m_scaleMod), 0.5, 0.25, 16, vec4(0, 1, 0, 1), &rotate);
	}
	else if (a_type == PIECE::REDKING)
	{
		Gizmos::addCylinderFilled(vec3((x * m_scaleMod), 4, z * m_scaleMod), 0.5, 0.25, 16, vec4(1, 1, 0, 1), &rotate);
	}
	else if (a_type == PIECE::BLACK || a_type == PIECE::BLACKKING)
	{
		Gizmos::addCylinderFilled(vec3((x * m_scaleMod), 4, z * m_scaleMod), 0.5, 0.25, 16, vec4(0, 1, 0, 1), &rotate);
	}
	
}

void CheckersProject::DrawSphere(int c, int r)
{
	
	Gizmos::addSphere(vec3(c* m_scaleMod, 1, r * m_scaleMod), 0.5, 10, 10, glm::vec4(0, 0, 1, 1));
}
//To make for Projected moves
//void CheckersProject::ProjectMove(int z,int x, Type)
