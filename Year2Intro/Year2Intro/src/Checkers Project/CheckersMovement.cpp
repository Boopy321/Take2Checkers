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

	m_moveUpRight = glm::vec2(1, 1);
	m_moveDownRight = glm::vec2(-1, 1);
	m_moveUpLeft = glm::vec2(1, -1);
	m_moveDownLeft = glm::vec2(-1, -1);

}


CheckersMovement::~CheckersMovement()
{
}

bool CheckersMovement::isValidMovement(int newposX, int newposZ, PIECE a_type, int oldposX, int oldposZ)
{
	if (isAbleMove(newposX, newposZ, a_type, oldposX, oldposZ))
	{
		m_turn = (m_turn == TURN::PLAYER_1) ? TURN::PLAYER_2 : TURN::PLAYER_1;
		return true;
	}
	else if (isAbleJump(newposX, newposZ, a_type, oldposX, oldposZ))
	{
		
		m_turn = (m_turn == TURN::PLAYER_1) ? TURN::PLAYER_2 : TURN::PLAYER_1;
		return true;
	}
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

	for (int i = 0; i <= 7; i++)
	{
		if(m_board[0][i] == PIECE::BLACK)
		{
			m_board[0][i] = PIECE::BLACKKING;
			m_drawboard->GetCurrentBoard(m_board);
		}
	}

	for (int i = 7; i>= 0; i--)
	{
		if (m_board[7][i] == PIECE::RED)
		{
			m_board[7][i] = PIECE::REDKING;
			m_drawboard->GetCurrentBoard(m_board);
		}
	}


	
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


		if (m_board[column][row] == PIECE::BLACKKING)
		{
			//SHOW VALID MOVES
			//m_board[column][row] = PIECE::NONE;
			//m_drawboard->GetCurrentBoard(m_board);
			return PIECE::NONE;
		}
		if (m_board[column][row] == PIECE::BLACK)
		{
			//SHOW VALID MOVES
			//m_board[column][row] = PIECE::NONE;
			//m_drawboard->GetCurrentBoard(m_board);
			return PIECE::NONE;
		}

	}
	else if (m_turn == TURN::PLAYER_2)
	{
		if (m_board[column][row] == PIECE::REDKING)
		{
			//SHOW VALID MOVES
			//m_board[column][row] = PIECE::NONE;
			//m_drawboard->GetCurrentBoard(m_board);
			return PIECE::NONE;
		}

		if (m_board[column][row] == PIECE::RED)
		{
			//SHOW VALID MOVES
			//m_board[column][row] = PIECE::NONE;
			//m_drawboard->GetCurrentBoard(m_board);
			return PIECE::NONE;
		}

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

bool CheckersMovement::PlacePiece(PIECE a_type, int x, int z,int oldposx,int oldposz)
{
	//Needs to still be created
	if (isValidMovement(x, z, a_type, oldposx, oldposz))
	{
		m_board[x][z] = a_type;
		ClearSpot(oldposz, oldposx);
		return true;
	}
	else
		return false;

		
}

bool CheckersMovement::isAbleJump(int newposX,int newposZ,PIECE a_type, int oldposX, int oldposZ )
{

 	int Distance = ManhattanDistance(glm::vec2(newposX, newposZ), glm::vec2(oldposX, oldposZ));
	bool Diagonal = isDiagonal(glm::vec2(newposX, newposZ), glm::vec2(oldposX, oldposZ),a_type);
	bool Piece = isPieceThere(glm::vec2(newposX, newposZ), glm::vec2(oldposX, oldposZ));

	if (Distance == 4 &&  ///Gets the Distance
		Diagonal &&   //Is the bastard doing a Diagonal move
		Piece)   //Is there as piece in the middle
	{
		return true;
	}
	else
		return false;
}
bool CheckersMovement::isAbleMove(int newposX,int newposZ,PIECE a_type,int oldposX,int oldposZ)
{
	
	if (m_board[newposX][newposZ] == PIECE::NONE)
	{
		if (ManhattanDistance(glm::vec2(newposX,newposZ),glm::vec2(oldposX,oldposZ)) == 2)
		{
			if (isDiagonal(glm::vec2(newposX, newposZ), glm::vec2(oldposX, oldposZ),a_type))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
		return false;
}

bool CheckersMovement::isDiagonal(glm::vec2 newpos, glm::vec2 oldpos,PIECE a_type)
{
	int xIncrement = newpos.x - oldpos.x;
	int yIncrement = newpos.y - oldpos.y;

	//Check the piece type

	//Black Piece on the diagonal?
	if (a_type == PIECE::BLACKKING || a_type == PIECE::REDKING)
	{
		if (xIncrement == 0 || yIncrement == 0)
		{
			return false;
		}
		else
			return true;
	}
	else
	{
		//Red piece on the diagonal?
		if (a_type == PIECE::RED && xIncrement > 0)
		{
			return true;
		}
		else if (a_type == PIECE::BLACK && xIncrement < 0)
		{
			return true;
		}
		else
			return false;
	}
	
}

bool CheckersMovement::isPieceThere(glm::vec2 newpos, glm::vec2 oldpos)
{
	//Check if there was a piece between them
	int xIncrement = newpos.x - oldpos.x;
	int yIncrement = newpos.y - oldpos.y;
	if ((yIncrement != 2 && xIncrement != 2) && (yIncrement != -2 && xIncrement != -2))
	{
		return false;
	}
	//Temporary allocation for position
	int zpos = (int)newpos.x - xIncrement / 2;
	int xpos = (int)newpos.y - yIncrement / 2;
	
	//If there was no piece then the move is not valid.
	if (m_board[zpos][xpos] == PIECE::NONE)
	{
		return false;
	}
	else
	{
		//Player 1 turn 
		if (m_turn == TURN::PLAYER_1)
		{
			if (m_board[zpos][xpos] == PIECE::BLACKKING)
			{
				m_board[zpos][xpos] = PIECE::NONE;
				return true;
			}
			else if (m_board[zpos][xpos] == PIECE::BLACK)
			{
				m_board[zpos][xpos] = PIECE::NONE;
				return true;
			}
			else 
				return false;
		}
		//Player 2 turn
		else
		{
			if (m_board[zpos][xpos] == PIECE::REDKING)
			{
				m_board[zpos][xpos] = PIECE::NONE;
				return true;
			}
			else if (m_board[zpos][xpos] == PIECE::RED)
			{
				m_board[zpos][xpos] = PIECE::NONE;
				return true;
			}
			else
				return false;
		}
	}
	
}

//Manhattan Distance
int CheckersMovement::ManhattanDistance(glm::vec2 a_to, glm::vec2 a_from)
{
	int ValueX1 = a_to.x;
	int ValueX2 = a_from.x;
	int ValueY1 = a_to.y;
	int ValueY2 = a_from.y;
	
	int ReturnX;
	int ReturnY;
	
	int Distance;

	ReturnX = abs(ValueX1 - ValueX2);
	ReturnY = abs(ValueY1 - ValueY2);

	Distance = (ReturnX + ReturnY);

	if (Distance < 0)
		Distance = -Distance;
	
	return Distance;
}

void CheckersMovement::ClearSpot(int a_oldz , int a_oldx)
{
	m_board[a_oldx][a_oldz] = PIECE::NONE;
	m_drawboard->GetCurrentBoard(m_board);
}

bool CheckersMovement::IsPieceNearby(int newposz, int newposx)
{

}
{

}