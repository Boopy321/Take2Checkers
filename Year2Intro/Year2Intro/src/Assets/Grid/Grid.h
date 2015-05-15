#pragma once
#include <vector>
struct gridVerts;
class Texture2D;

class Grid
{
public:
	//Rows,Cols and the space between each point
	Grid(unsigned int a_rows, unsigned int a_columns,unsigned int a_gap);
	~Grid();

	void InitGrid(unsigned int a_rows, unsigned int a_columns);
	void CreateOpenGlBuffers(std::vector<gridVerts> a_pVertex, unsigned int* a_indexData);
	void Draw(unsigned int &m_program);

private:

	std::vector<gridVerts> m_verts;
	unsigned int m_grid;
	unsigned int m_ibo, m_vbo, m_vao;
	unsigned int* m_indexData;
};

