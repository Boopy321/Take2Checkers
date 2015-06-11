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
	REMOVE_RED,
	REMOVE_BLACK,
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
	//Iniatiate the board
	void SetCheckers();

	bool PlacePiece(PIECE a_type, int x, int z, int oldposx, int oldposz);
	
	bool isValidMovement(glm::vec2 a_newPos, PIECE a_type, glm::vec2 a_oldpos);
	bool isAbleJump(glm::vec2 a_newPos, PIECE a_type, glm::vec2 a_oldpos);
	bool isAbleMove(glm::vec2 a_newPos, PIECE a_type, glm::vec2 a_oldpos);
	bool isDiagonal(glm::vec2 a_newpos, glm::vec2 oldpos, PIECE a_type);
	bool isPieceThere(glm::vec2 newpos, glm::vec2 oldpos);
	bool IsPieceNearby(int newposz, int newposx);
	bool DoubleJump(glm::vec2 a_newpos , glm::vec2 dir, PIECE a_type);
	//Instead of Auto Changing

	void LagTime();
	void SwitchTurn();
	

	int ManhattanDistance(glm::vec2 a_to, glm::vec2 a_from);

	void ClearSpot(int a_oldz, int a_oldx);

	void Update(FlyCamera &_gameCamera, float a_deltatime);

	PIECE GrabPiece(int a, int b);
private:
	
	bool m_valid;

	PIECE m_board[8][8];

	int m_blackcount;
	int m_redcount;
	int m_totalcount;

	int m_cols;
	int m_rows;

	CheckersPlayer* m_player1;
	CheckersPlayer* m_player2;

	glm::vec2 m_moveUpRight;
	glm::vec2 m_moveDownRight;
	glm::vec2 m_moveUpLeft;
	glm::vec2 m_moveDownLeft;

	
	//Enum Turn Manager
	TURN m_turn;

	bool m_tileRed;
	//Draw Data of the game.
	CheckersProject* m_drawboard;
};

