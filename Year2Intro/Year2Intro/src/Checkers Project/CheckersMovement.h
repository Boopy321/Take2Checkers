#pragma once

class CheckersProject;
class FlyCamera;
class CheckersPlayer;
#include <vector>
#include <glm/vec2.hpp>
#include <list>
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
	//CHECKERS RULL FUNCTIONS
	bool isValidMovement(glm::ivec2 a_newPos, PIECE a_type, glm::ivec2 a_oldpos);
	bool isAbleJump(glm::ivec2 a_newPos, PIECE a_type, glm::ivec2 a_oldpos);
	bool isAbleMove(glm::ivec2 a_newPos, PIECE a_type, glm::ivec2 a_oldpos);
	bool isDiagonal(glm::ivec2 a_newpos, glm::ivec2 oldpos, PIECE a_type);
	bool isPieceThere(glm::ivec2 newpos, glm::ivec2 oldpos);
	bool IsPieceNearby(int newposz, int newposx);
	bool IsForwardMovement(glm::ivec2 a_newpos, glm::ivec2 a_oldpos);
	bool DoubleJump(glm::ivec2 a_newpos , glm::ivec2 dir, PIECE a_type);
	//Instead of Auto Changing

	//Takes a Position vector and Compares it with the
	//lowest possible and highest possible numbers in the grid
	bool Compare(glm::ivec2 CurValue, glm::ivec2 MinMax);

	void GetListOfMoves();
	//Ai Movement
	void MakeMove();
	//Call Before using Possible moves
	void ClearPossibleMoves();
	//Sets up all possible moves
	void ShowPossibleMoves();
	//Turn Switching
	void SwitchTurn();
	
	//Gets the Distance between the 2 vectors
	int ManhattanDistance(glm::ivec2 a_to, glm::ivec2 a_from);
	//Wipes the spot at that location
	
	void ClearSpot(int a_oldz, int a_oldx);

	bool CheckersMovement::ShowCurrentPieceMoves(glm::ivec2 oldpos, PIECE a_type);

	void Update(FlyCamera &_gameCamera, float a_deltatime);
	//Grabs what
	PIECE GrabPiece(int a, int b);
private:
	
	bool m_valid;
	bool m_jump;
	bool m_localJump;
	bool m_tileRed;
	bool m_delete;
	PIECE m_board[8][8];

	int m_blackcount;
	int m_redcount;
	int m_totalcount;

	int m_cols;
	int m_rows;

	CheckersPlayer* m_player1;
	CheckersPlayer* m_player2;

	glm::ivec2 m_moveUpRight;
	glm::ivec2 m_moveDownRight;
	glm::ivec2 m_moveUpLeft;
	glm::ivec2 m_moveDownLeft;

	std::vector<glm::ivec2> m_deletemoves;
	std::vector<glm::ivec2> m_posJumps;
	std::vector<glm::ivec2> m_posMoves;
	//Enum Turn Manager
	TURN m_turn;

	//Draw Data of the game.
	CheckersProject* m_drawboard;
};

