#pragma once

class CheckersProject;
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

	bool isValidMovement();
	void SetCheckers();
	bool PlacePiece(PIECE a_type, int x, int z);


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
	
	TURN m_turn;
	bool m_tileRed;

	CheckersProject* m_drawboard;
};

