#include <gl_core_4_4.h>
#include "CheckersProject.h"
#include "Assets\Grid\Grid.h"
#include "Assets\FBXModel\FBXDrawer\FBXDrawer.h"
#include <glm\glm.hpp>
#include <GLFW\glfw3.h>
#include "Assets\RenderTargets\RenderTarget.h"
#include <glm\glm.hpp>
#include "Assets\Render\Renderer.h"
#include "Assets\Camera\FlyCamera.h"
#include "FBXFile.h"
#include "Assets\Texture2D\Texture2D.h"
#include <vector>
#include "Assets\FBXModel\FBXModel.h"
#include "Assets\FBXModel\FBXDrawer\FBXDrawer.h"
#include "Assets\GpuParticle\GpuParticleEmitter.h"
#include "Assets\Light\Light.h"
#include "Assets\Grid\GridVerts.h"
#include "Gizmos.h"




CheckersProject::CheckersProject(Renderer* a_render, Light* a_light)
{

	m_light = a_light;
	m_render = a_render;
	//Start up Grid
	m_totalcount = 15;
	//Set Up Pieces
	m_modelBlack = new FBXModel("./data/models/Bunny.fbx");
	m_modelRed = new FBXModel("./data/models/Rock1/Rock1.fbx");

	//Resize the vectors for Checkers
	m_black.resize(m_totalcount);
	m_red.resize(m_totalcount);

	m_rows = 8;
	m_cols = 8;
	
	for (int i = 0; i < m_totalcount ; i++)
	{
		m_black[i] = new FBXDrawer();
		m_black[i]->SetModel(m_modelBlack);
		m_red[i] = new FBXDrawer();
		m_red[i]->SetModel(m_modelBlack);
	}

	m_tileRed = true;
	InitGrid();
	SetCheckers();
	
}


CheckersProject::~CheckersProject()
{

}

void CheckersProject::Draw(FlyCamera &_gameCamera, float a_deltatime)
{
	using glm::vec3;
	using glm::vec4;

	Gizmos::addTransform(glm::mat4(0.1), 100.0f);

	unsigned int program;
	program = m_render->ReturnProgramFBX();

	for (int i = 0; i < m_red.size(); i++)
	{
		m_red[i]->Draw(program, m_render, m_light, _gameCamera);
	}

	for (int i = 0; i < m_red.size(); i++)
	{
		m_black[i]->Draw(program, m_render, m_light, _gameCamera);
	}

	//program = m_render->ReturnProgramSimpleLoad();

	glm::mat4 rotate;
	rotate = glm::rotate(mat4(1.0f), glm::pi<float>() / 4, glm::vec3(0, 1, 0));
	Gizmos::addCylinderFilled(vec3(5.25, -1, 5.25), 10, 0.75, 4, vec4(0.545, 0.270, 0.074, 1), &rotate);
	///Draw the Grid
	for (float c = 0; c <= m_cols- 1; c++) {

		for (float r = 0; r <= m_rows - 1; r++) {
				
			if (m_tileRed == false)
			{
				Gizmos::addCylinderFilled(vec3((r * 1.5), 0, c * 1.5), 1, 0.25, 4, vec4(0, 0, 0, 1), &rotate);
				m_tileRed = true;
			}
				
			else
			{
				Gizmos::addCylinderFilled(vec3(r * 1.5, 0, c *1.5), 1, 0.25, 4, vec4(1, 0, 0, 1), &rotate);
				m_tileRed = false;
			}

		}
		m_tileRed = !m_tileRed;
	}
	
	
	
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

			if (placepiece == true)
			{

				m_red[i]->SetRotate(glm::vec3(0, 0, 0));
				m_red[i]->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
				m_red[i]->SetPosition(glm::vec3((float)c, 0, (float)r));
				m_grid[c][r] = PIECE::RED;
				i++;
				placepiece = false;
			}
			else if (i < m_totalcount)
			placepiece = true;

		}
	}
}



void CheckersProject::DeleteToken(PIECE state)
{	
	if (state == PIECE::REMOVERED)
	{
		m_redcount = m_redcount - 1;
		for (int i = 0; i < m_red.size(); i++)
		{
			if (m_red[i] == nullptr)// || (m_red[i] == m_red[i + 1] || m_red[i+1] == nullptr))
			{
			
				for (int a = i; a == m_redcount; a--)
				{
					m_red[a] = m_red[a + 1];
				}
			}
		}
		m_red.pop_back();
	}

	if (state == PIECE::REMOVEBLACK)
	{
		m_blackcount = m_blackcount - 1;
		for (int i = 0; i < m_black.size(); i++)
		{
			if (m_black[i] == nullptr)// || (m_red[i] == m_red[i + 1] || m_red[i+1] == nullptr))
			{

				for (int a = i; a == m_redcount; a--)
				{
					m_black[a] = m_black[a + 1];
				}
			}
		}
		m_black.pop_back();
	}

}

void CheckersProject::InitGrid()
{
	for (int c = 0; c < m_cols; c++)
	{
		for(int r = 0 ; r < m_rows; r++)
		{
			m_grid[c][r] = PIECE::NONE;
		}
	}
}
