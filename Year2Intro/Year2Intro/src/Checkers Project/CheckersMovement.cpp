#include "CheckersMovement.h"
#include "CheckersProject.h"
#include "Assets\Camera\FlyCamera.h"
#include "CheckersPlayer.h"

CheckersMovement::CheckersMovement()
{
	m_totalcount = 12;


	//Resize the vectors for Checkers
	m_rows = 8;
	m_cols = 8;

	m_drawboard = new CheckersProject();
	SetCheckers();


	m_player1 = new CheckersPlayer(m_drawboard,this);
	m_player2 = new CheckersPlayer(m_drawboard,this);

	m_turn = TURN::PLAYER_1;
}


CheckersMovement::~CheckersMovement()
{
}

bool CheckersMovement::isValidMovement()
{
	//Maybe each player data




	//Check through the grid. Find each state of each spot of the grid
	return true;
}

void CheckersMovement::SetCheckers()
{
	bool placepiece = true;
	int i = 0;
	for (int c = 0; c <= m_cols - 1; c++)
	{

		for (int r = 0; r <= m_rows - 1; r++)
		{
			if (i == m_totalcount)
				break;
			if (placepiece == true)
			{
				m_board[c][r] = PIECE::RED;
				placepiece = false;
				i++;
			}
			else if (i <= m_totalcount)
			{
				placepiece = true;
				m_board[c][r] = PIECE::NONE;
			}

		}
		placepiece = !placepiece;
	}

	i = m_totalcount;
	for (int c = m_cols - 1; c >= 0; c--)
	{

		for (int r = m_rows - 1; r >= 0; r--)
		{
			if (i == 0)
				break;
			if (placepiece == false)
			{
				m_board[c][r] = PIECE::BLACK;
				placepiece = true;
				i--;
			}
			else if (i >= 0)
			{
				placepiece = false;
				m_board[c][r] = PIECE::NONE;
			}

		}
		placepiece = !placepiece;
	}

	m_drawboard->GetCurrentBoard(m_board);
}

void CheckersMovement::Update(FlyCamera &_gameCamera, float a_deltatime)
{
	m_drawboard->Draw(_gameCamera, a_deltatime);
	if (m_turn == TURN::PLAYER_1)
		m_player1->Update();
	else
		m_player2->Update();
	
}
///WHAT piece in the array did you grab
PIECE CheckersMovement::GrabPiece(int column, int row)
{
	if (m_board[column][row] == PIECE::NONE)
	{
		return PIECE::NONE;
	}
	else if (m_turn == TURN::PLAYER_1)
	{
		if (m_board[column][row] == PIECE::REDKING)
		{
			//SHOW VALID MOVES
			//m_board[column][row] = PIECE::NONE;
			//m_drawboard->GetCurrentBoard(m_board);
			return PIECE::REDKING;
		}

		if (m_board[column][row] == PIECE::RED)
		{
			//SHOW VALID MOVES
			//m_board[column][row] = PIECE::NONE;
			//m_drawboard->GetCurrentBoard(m_board);
			return PIECE::RED;
		}
	}
	else if (m_turn == TURN::PLAYER_2)
	{
		if (m_board[column][row] == PIECE::BLACKKING)
		{
			//SHOW VALID MOVES
			//m_board[column][row] = PIECE::NONE;
			//m_drawboard->GetCurrentBoard(m_board);
			return PIECE::BLACKKING;
		}
		if (m_board[column][row] == PIECE::BLACK)
		{
			//SHOW VALID MOVES
			//m_board[column][row] = PIECE::NONE;
			//m_drawboard->GetCurrentBoard(m_board);
			return PIECE::BLACK;
		}
	}
	 
}

bool CheckersMovement::PlacePiece(PIECE a_type, int x, int z)
{
	//Needs to still be created
	if (isValidMovement())//PIECE a_type, int x, int z);
	{
		m_board[x][z] = a_type;
		m_drawboard->GetCurrentBoard(m_board);
		return true;
	}
	else
	{
		return false;
	}

		
}