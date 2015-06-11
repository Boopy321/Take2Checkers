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

	m_moveUpRight = glm::vec2(2, 2);
	m_moveDownRight = glm::vec2(-2, 2);
	m_moveUpLeft = glm::vec2(2, -2);
	m_moveDownLeft = glm::vec2(-2, -2);
}


CheckersMovement::~CheckersMovement()
{
}
//is literally its name
bool CheckersMovement::isValidMovement(glm::vec2 a_newPos, PIECE a_type, glm::vec2 a_oldpos)
{
	if (isAbleMove(a_newPos, a_type, a_oldpos))
	{
		m_turn = (m_turn == TURN::PLAYER_1) ? TURN::PLAYER_2 : TURN::PLAYER_1;
		return true;
	}
	//Recursive Function based on new posistion Does not check for a Triple jump
	else if (isAbleJump(a_newPos, a_type, a_oldpos))
		return true;
	else
		return false;
}
//Sets up the game board with the pieces
//For loops to set up each team
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

	m_board[6][6] = PIECE::NONE;
	m_board[3][3] = PIECE::BLACK;
	
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
//What i grabbed in the array
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
			
			return PIECE::REDKING;
		}

		if (m_board[column][row] == PIECE::RED)
		{
	
			return PIECE::RED;
		}

		if (m_board[column][row] == PIECE::BLACKKING)
		{
			return PIECE::NONE;
		}
		if (m_board[column][row] == PIECE::BLACK)
		{
			
			return PIECE::NONE;
		}

	}
	else if (m_turn == TURN::PLAYER_2)
	{
		if (m_board[column][row] == PIECE::REDKING)
		{
			return PIECE::NONE;
		}

		if (m_board[column][row] == PIECE::RED)
		{
			return PIECE::NONE;
		}

		if (m_board[column][row] == PIECE::BLACKKING)
		{
			return PIECE::BLACKKING;
		}
		if (m_board[column][row] == PIECE::BLACK)
		{
			return PIECE::BLACK;
		}
	}

	else
		return PIECE::NONE;
}

bool CheckersMovement::PlacePiece(PIECE a_type, int x, int z,int oldposx,int oldposz)
{
	
	if (isValidMovement(glm::vec2(x,z),a_type,glm::vec2(oldposx, oldposz)))
	{
		m_board[x][z] = a_type;
		ClearSpot(oldposz, oldposx);
		return true;
	}
	else
		return false;

		
}

bool CheckersMovement::isAbleJump(glm::vec2 a_newPos, PIECE a_type, glm::vec2 a_oldPos)
{

	int Distance = ManhattanDistance(a_newPos, a_oldPos);
	bool Diagonal = isDiagonal(a_newPos, a_oldPos, a_type);
	bool Piece = isPieceThere(a_newPos, a_oldPos);

	if (Distance == 4 &&  ///Gets the Distance
		Diagonal &&   //Is the bastard doing a Diagonal move
		Piece)   //Is there as piece in the middle
	{
		return true;
	}
	else
		return false;
}

bool CheckersMovement::isAbleMove(glm::vec2 a_newPos, PIECE a_type, glm::vec2 a_oldpos)
{
	
	if (m_board[(int)a_newPos.x][(int)a_newPos.y] == PIECE::NONE)
	{
		if (ManhattanDistance(a_newPos, a_oldpos) == 2)
		{
			if (isDiagonal(a_newPos,a_oldpos,a_type))
				return true;
			else
				return false;
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
	int xIncrement = (int)newpos.x - (int)oldpos.x;
	int yIncrement = (int)newpos.y - (int)oldpos.y;

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
	int ValueX1 = (int)a_to.x;
	int ValueX2 = (int)a_from.x;
	int ValueY1 = (int)a_to.y;
	int ValueY2 = (int)a_from.y;
	
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

void CheckersMovement::ClearSpot(int a_oldz, int a_oldx)
{
	m_board[a_oldx][a_oldz] = PIECE::NONE;
	m_drawboard->GetCurrentBoard(m_board);
}


//Give it the Jump position and a Random Direcetion to check for another jump
bool CheckersMovement::DoubleJump(glm::vec2 a_newPos, glm::vec2 dir, PIECE a_type)
{
	if (isAbleJump(a_newPos + dir, a_type, a_newPos))
	{
		return true;
	}
	else
		return false;
}

void CheckersMovement::SwitchTurn()
{
	m_turn = (m_turn == TURN::PLAYER_1) ? TURN::PLAYER_2 : TURN::PLAYER_1;
}

//Basically Check all valid moves
void CheckersMovement::LagTime()
{
	for (int c = 0; c < 8; c++)
	{
		for (int r = 0; r < 8; r++)
		{
			if (m_board[c][r] != PIECE::NONE || m_board[c][r] == PIECE::POSSIBLEMOVE)
			{
				continue;
			}
			else
			{
				//Check Valid Moves
				PIECE current = m_board[c][r];
				
				bool possibleMove[4];
				//Before this Check for a KIng
				//Else do that shit

				glm::vec2 pos = glm::vec2(c, r);
				///////This whole statement basically determines if there is any possible moves to make for either type of piece
				switch (current)
				{
				case NONE:
					break;

				case RED:
					possibleMove[0] = isValidMovement(pos, current, pos);
					possibleMove[1] = isValidMovement(pos, current, pos);
					break;

				case BLACK:
					possibleMove[0] = isValidMovement(pos, current, pos);
					possibleMove[1] = isValidMovement(pos, current, pos);
					break;

				case REDKING:
					possibleMove[0] = isValidMovement(pos, current, pos);
					possibleMove[1] = isValidMovement(pos, current, pos);
					possibleMove[2] = isValidMovement(pos, current, pos);
					possibleMove[3] = isValidMovement(pos, current, pos);
					break;

				case BLACKKING:
					possibleMove[0] = isValidMovement(pos, current, pos);
					possibleMove[1] = isValidMovement(pos, current, pos);
					possibleMove[2] = isValidMovement(pos, current, pos);
					possibleMove[3] = isValidMovement(pos, current, pos);
					break;

				case REMOVE_RED:
					break;

				case REMOVE_BLACK:
					break;

				case POSSIBLEMOVE:
					break;

				default:
					break;
				}
				

				

			}




		}
	}
}

