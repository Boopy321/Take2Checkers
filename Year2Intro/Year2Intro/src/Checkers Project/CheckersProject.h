#pragma once
#include <vector>

class FlyCamera;
class CheckersPlayer;
#include "CheckersMovement.h"
#include "glm\glm.hpp"

class CheckersProject
{
public:
	CheckersProject();
	~CheckersProject();

	void Draw(FlyCamera &_gameCamera, float a_deltatime);
	void Update();
	
	void SetCheckers();
	void DeleteToken(PIECE state);

	void GetCurrentBoard(PIECE a_grid[8][8]);
	//static void setTurn(TURN a_whosTurn);
	void DrawPieceInHand(int c, int r,PIECE a_type);
	void DrawSphere(int c, int r);
private:

	PIECE m_board[8][8];
	
	float m_scaleMod;
	
	unsigned int m_blackcount;
	unsigned int m_redcount;
	unsigned int m_totalcount;

	glm::mat4 rotate;
	int m_cols;
	int m_rows;

	TURN m_turn;
	bool m_tileRed; 

};

