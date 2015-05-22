#pragma once
#include <vector>


class Grid;
class Texture2D;
class Light;
class Renderer;
class FlyCamera;
class CheckersPlayer;

enum PIECE
{
	NONE,
	RED,
	BLACK,
	REDKING,
	BLACKKING,
	REMOVERED,
	REMOVEBLACK,
	
};

enum STATE
{
	UNKNOWN,
	PLAYER_ONE,
	PLAYER_TWO,
	DRAW,
};

enum TURN
{
	PLAYER_1,
	PLAYER_2,
	GAMEOVER,
};

class CheckersProject
{
public:
	CheckersProject();
	~CheckersProject();

	void Draw(FlyCamera &_gameCamera, float a_deltatime);
	void Update();
	
	void SetCheckers();
	void DeleteToken(PIECE state);

private:

	PIECE m_board[8][8];
	
	float m_scaleMod;
	Light* m_light;
	Renderer* m_render;

	CheckersPlayer* m_player1;
	CheckersPlayer* m_player2; 
	
	unsigned int m_blackcount;
	unsigned int m_redcount;
	unsigned int m_totalcount;

	int m_cols;
	int m_rows;

	TURN m_turn;
	bool m_tileRed; 

};

