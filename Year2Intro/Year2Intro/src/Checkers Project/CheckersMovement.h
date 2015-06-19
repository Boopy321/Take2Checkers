#pragma once

class CheckersProject;
class FlyCamera;
class CheckersPlayer;
class MCTS_Checker;
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
	POSSIBLEMOVE,
	WINNING_MLG_PRO_MATE,
};

//enum AI_STATE
//{
//	RANDOMMOVE = 1,
//	REDTAKEBLACK = -2,
//	BLACKTAKERED = 2,
//	REDTAKEKING = -5,
//	BLACKTAKEKING = 5,
//
//
//};

enum STATE
{
	UNKNOWN,
	PLAYER_ONE,
	PLAYER_TWO,
	GAMEOVER,
};

enum class TURN
{
	PLAYER_1,
	PLAYER_2,
	GAMEOVER,
};



struct Action
{
	glm::ivec2 originalLocation;
	glm::ivec2 newLocation;
	PIECE pieceType;
	void Reset()
	{
		glm::ivec2 originalLocation = glm::ivec2(0, 0);
		glm::ivec2 newLocation = glm::ivec2(0, 0);
		PIECE pieceType = PIECE::NONE;
	}
};

class CheckersMovement
{
public:

	CheckersMovement();
	~CheckersMovement();
	//Iniatiate the board with poo
	void SetCheckers();

	bool PlacePiece(PIECE a_type, int x, int z, int oldposx, int oldposz);
	//CHECKERS RULL FUNCTIONS
#pragma region CheckerRules
	bool isValidMovement(glm::ivec2 a_newPos, PIECE a_type, glm::ivec2 a_oldpos);
	bool isAbleJump(glm::ivec2 a_newPos, PIECE a_type, glm::ivec2 a_oldpos);
	bool isAbleMove(glm::ivec2 a_newPos, PIECE a_type, glm::ivec2 a_oldpos);
	bool isDiagonal(glm::ivec2 a_newpos, glm::ivec2 oldpos, PIECE a_type);
	bool isPieceThere(glm::ivec2 newpos, glm::ivec2 oldpos);
	bool IsPieceNearby(int newposz, int newposx);
	bool IsForwardMovement(glm::ivec2 a_newpos, glm::ivec2 a_oldpos);
	bool IsBackwardMovement(glm::ivec2 a_newpos, glm::ivec2 a_oldpos);
	bool DoubleJump(glm::ivec2 a_newpos , glm::ivec2 dir, PIECE a_type);
#pragma endregion
	//Clone the current game
	CheckersMovement* Clone();
	//Wipes all vectors and clears possible moves
	void Clear();
	//Takes a Position vector and Compares it with the
	//lowest possible and highest possible numbers in the grid
	bool Compare(glm::ivec2 CurValue, glm::ivec2 MinMax);

	STATE CheckersMovement::isGameOver();

	//Call Before using Possible moves
	void ClearPossibleMoves();
	//Sets up all possible moves
	void ShowPossibleMoves();
	//Turn Switching
	void SwitchTurn();
	
	//Performs Action obs
	void performAction(Action* a_action);
	//For if there is a piece that can continue jumping if there is apossible option
	PIECE UpgradeToKing(glm::ivec2 a_pos, PIECE a_type);
	//Gets the Distance between the 2 vectors
	int ManhattanDistance(glm::ivec2 a_to, glm::ivec2 a_from);
	//Wipes the spot at that location
	
	void ClearSpot(int a_oldz, int a_oldx);

	bool ShowCurrentPieceMoves(glm::ivec2 oldpos, PIECE a_type);

	void Update(FlyCamera &_gameCamera, float a_deltatime);
	//Grabs what
	PIECE GrabPiece(int a, int b);

	std::vector<Action> ReturnMoveSet();

	std::vector<Action> m_jumpmoves;
	std::vector<Action> m_normMoves;

	int ReturnWeight();


	bool m_jump;
protected:

	PIECE m_board[8][8];
	TURN m_turn;

	std::vector<glm::ivec2> m_deletemoves;


private:
	
	bool m_valid;
	bool m_localJump;
	bool m_tileRed;
	bool m_delete;

	int m_blackcount;
	int m_redcount;
	int m_totalcount;

	int m_cols;
	int m_rows;

	CheckersPlayer* m_player1;
	MCTS_Checker* m_player2;

	glm::ivec2 m_moveUpRight;
	glm::ivec2 m_moveDownRight;
	glm::ivec2 m_moveUpLeft;
	glm::ivec2 m_moveDownLeft;

	
	//Enum Turn Manager


	//Draw Data of the game.
	CheckersProject* m_drawboard;
	
};

