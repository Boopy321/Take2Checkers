#pragma once

class CheckersProject;
class FlyCamera;
class CheckersPlayer;

#include <glm/vec2.hpp>

enum PIECE
{
	NONE,
	RED,
	BLACK,
	REDKING,
	BLACKKING,
	REMOVERED,
	REMOVEBLACK,
	POSSIBLEMOVE,
};

enum STATE
{
	UNKNOWN,
	PLAYER_ONE,
	PLAYER_TWO,
	DRAW,
};

enum class TURN
{
	PLAYER_1,
	PLAYER_2,
	GAMEOVER,
};

class CheckersMovement
{
public:

	CheckersMovement();
	~CheckersMovement();

	bool isValidMovement(int newposX, int newposZ, PIECE a_type, int oldposX, int oldposZ);
	void SetCheckers();
	bool PlacePiece(PIECE a_type, int x, int z, int oldposx, int oldposz);

	bool isAbleJump(int newposX, int newposZ, PIECE a_type, int oldposX, int oldposZ);
	bool isAbleMove(int newposX, int newposZ, PIECE a_type, int oldposX, int oldposZ);
	bool isDiagonal(glm::vec2 newpos, glm::vec2 oldpos);
	bool isPieceThere(glm::vec2 newpos, glm::vec2 oldpos);


	int ManhattanDistance(glm::vec2 a_to, glm::vec2 a_from);
	void ClearSpot(int a_oldz, int a_oldx);


	void Update(FlyCamera &_gameCamera, float a_deltatime);
	PIECE GrabPiece(int a, int b);
private:
	
	bool m_valid;

	PIECE m_board[8][8];

	unsigned int m_blackcount;
	unsigned int m_redcount;
	unsigned int m_totalcount;

	int m_cols;
	int m_rows;

	CheckersPlayer* m_player1;
	CheckersPlayer* m_player2;
	
	//Vector Control movement
	glm::vec2 m_moveUpRight;
	glm::vec2 m_moveDownRight;
	glm::vec2 m_moveUpLeft;
	glm::vec2 m_moveDownLeft;

	TURN m_turn;
	bool m_tileRed;

	CheckersProject* m_drawboard;
};

