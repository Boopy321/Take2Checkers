#include "gl_core_4_4.h"
#include "GLFW\glfw3.h"
#include <glm\glm.hpp>
#include "Grid.h"
#include "Assets\Texture2D\Texture2D.h"
#include "GridVerts.h"

enum Cell
{
	EMPTY,
	RED,
	BLACK,
};


Grid::Grid(unsigned int a_rows, unsigned int a_columns, unsigned int a_gap)
{
	InitGrid(a_rows, a_columns);
}


Grid::~Grid()
{
}

void Grid::InitGrid(unsigned int a_rows, unsigned int a_columns)
{
	m_verts.resize((a_rows * a_columns) * (a_rows * a_columns));
	m_grid = a_rows * a_columns;
	m_indexData = new unsigned int[(m_grid - 1)*(m_grid - 1) * 6];

		int count = 0;

		//rows
		for (int rows = 0; rows < m_grid; rows++)
		{
			//cols
			for (int cols = 0; cols < m_grid; cols++)
			{
				m_verts[rows * m_grid + cols].Position = glm::vec4(((float)cols - (m_grid / 2)), 0, (((float)rows - (m_grid / 2))), 1);
				m_verts[rows * m_grid + cols].Normal = glm::vec3(0, 1, 0);
				//Tex Coords
				m_verts[rows * m_grid + cols].UV = glm::vec2(((float)cols / (float)m_grid), ((float)rows / (float)m_grid));
				count++;
				m_verts[rows * m_grid + cols].Active = false;
			}
		}
		////Index Values
		unsigned int index = 0;
		for (unsigned int row = 0; row < m_grid - 1; row++)
		{
			for (unsigned int col = 0; col < m_grid - 1; col++)
			{
				int currVert = row * m_grid + col;
				//Triangle 
				m_indexData[index++] = currVert;
				m_indexData[index++] = currVert + m_grid;
				m_indexData[index++] = currVert + m_grid + 1;

				//Triangle 2
				m_indexData[index++] = currVert;
				m_indexData[index++] = currVert + m_grid + 1;
				m_indexData[index++] = currVert + 1;
			}
		}
		//Places the data into the buffers
		CreateOpenGlBuffers(m_verts, m_indexData);
}


void Grid::CreateOpenGlBuffers(std::vector<gridVerts> a_pVertex, unsigned int* a_indexData)
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(gridVerts)* a_pVertex.size(), //Array vector size. Shit ,
		a_pVertex.data(), GL_DYNAMIC_DRAW);

	//Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
		sizeof(gridVerts), 0);
	//Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(gridVerts), (void*)offsetof(gridVerts, Normal));
	//UV
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(gridVerts), (void*)offsetof(gridVerts, UV));

	//Indics
	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* ((m_grid - 1)*(m_grid - 1) * 6),
		a_indexData, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

//INIT WITH Shader SimpleTextureBoard
void Grid::Draw(unsigned int &m_program)
{
	glUseProgram(m_program);
	
	
	glBindVertexArray(m_vao);
	unsigned int indexCount = ((m_grid - 1) * (m_grid - 1)) * 6;

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}



