#pragma once
#include <vector>

class FBXModel;
class FBXDrawer;
class Grid;
class Texture2D;
class Light;
class Renderer;
class FlyCamera;

enum PIECE
{
	RED,
	BLACK,
	REDKING,
	BLACKKING,
	REMOVERED,
	REMOVEBLACK,
	NONE,
};

enum STATE
{
	UNKNOWN,
	PLAYER_ONE,
	PLAYER_TWO,
	DRAW,
};

class CheckersProject
{
public:
	CheckersProject(Renderer* a_render, Light* a_light);
	~CheckersProject();

	void Draw(FlyCamera &_gameCamera, float a_deltatime);
	void Update();
	
	void SetCheckers();
	void DeleteToken(PIECE state);
	void InitGrid();
private:

	std::vector<FBXDrawer*> m_red;
	std::vector<FBXDrawer*> m_black;
	
	FBXModel* m_modelBlack;
	FBXModel* m_modelRed;
	Light* m_light;
	Renderer* m_render;
	unsigned int m_grid[8][8];

	unsigned int m_blackcount;
	unsigned int m_redcount;

	unsigned int m_totalcount;

	int m_cols;
	int m_rows;

	bool m_tileRed; 

};

