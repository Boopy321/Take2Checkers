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
	
	m_player1 = new CheckersPlayer(m_drawboard,this);
	m_player2 = new CheckersPlayer(m_drawboard,this);

	m_turn = TURN::PLAYER_1;
	//Up on the Y Axis
	m_moveUpRight = glm::ivec2(1, -1);
	m_moveUpLeft = glm::ivec2(1, 1);
	//Down on the Y Axis
	m_moveDownRight = glm::ivec2(-1, -1);
	m_moveDownLeft = glm::ivec2(-1, 1);

	SetCheckers();
}


CheckersMovement::~CheckersMovement()
{
}
//is literally its name
bool CheckersMovement::isValidMovement(glm::ivec2 a_newPos, PIECE a_type, glm::ivec2 a_oldpos)
{

	//Recursive Function based on new posistion Does not check for a Triple jump
	if (isAbleJump(a_newPos, a_type, a_oldpos))
		return true;

	else if (isAbleMove(a_newPos, a_type, a_oldpos))
	{
		return true;
	}
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

	//m_board[6][6] = PIECE::NONE;
	//m_board[3][3] = PIECE::BLACK;
	
	ShowPossibleMoves();
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
	if (m_board[column][row] == PIECE::NONE || m_board[column][row] == PIECE::POSSIBLEMOVE)
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
	
	if (isValidMovement(glm::ivec2(x,z),a_type,glm::ivec2(oldposx, oldposz)))
	{
		m_board[x][z] = a_type;
		ClearSpot(oldposz, oldposx);
		return true;
	}
	else
		return false;
}

bool CheckersMovement::isAbleJump(glm::ivec2 a_newPos, PIECE a_type, glm::ivec2 a_oldPos)
{

	int Distance = ManhattanDistance(a_newPos, a_oldPos);
	bool Diagonal = isDiagonal(a_newPos, a_oldPos, a_type);
	bool Forward = IsForwardMovement(a_newPos, a_oldPos) || a_type == PIECE::REDKING;
	bool Piece = isPieceThere(a_newPos, a_oldPos);

	//if King
	//Run it without forward


	if (Distance == 4 &&  ///Gets the Distance
		Diagonal && 
		Forward &&//Is the bastard doing a Diagonal move
		Piece)   //Is there as piece in the middle
	{
		return true;
	}
	else
		return false;
}

bool CheckersMovement::isAbleMove(glm::ivec2 a_newPos, PIECE a_type, glm::ivec2 a_oldpos)
{
	
	if (m_board[a_newPos.x][a_newPos.y] == PIECE::NONE)
	{
		if (ManhattanDistance(a_newPos, a_oldpos) == 2)
		{
			if (isDiagonal(a_newPos,a_oldpos,a_type))
				return true;
			else
				return false;
		}
	}
	//else if (m_board[a_newPos.x][a_newPos.y] == PIECE::POSSIBLEMOVE)
	//{
	//	if (ManhattanDistance(a_newPos, a_oldpos) == 2)
	//	{
	//		if (isDiagonal(a_newPos, a_oldpos, a_type))
	//			return true;
	//		else
	//			return false;
	//	}
	//}
	else
		return false;
}

bool CheckersMovement::isDiagonal(glm::ivec2 newpos, glm::ivec2 oldpos,PIECE a_type)
{
	int xIncrement = abs(newpos.x - oldpos.x);
	int yIncrement = abs(newpos.y - oldpos.y);

	return (xIncrement == yIncrement);
}

bool CheckersMovement::isPieceThere(glm::ivec2 newpos, glm::ivec2 oldpos)
{
	//Check if there was a piece between them
	int xIncrement = newpos.x - oldpos.x;
	int yIncrement = newpos.y - oldpos.y;

	if ((yIncrement != 2 && xIncrement != 2) && (yIncrement != -2 && xIncrement != -2))
	{
		return false;
	}
	//Temporary allocation for position
	int zpos = newpos.x - xIncrement / 2;
	int xpos = newpos.y - yIncrement / 2;
	
	//If there was no piece then the move is not valid.
	if (m_board[zpos][xpos] == PIECE::NONE || m_board[zpos][xpos] == PIECE::POSSIBLEMOVE)
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
				//m_board[zpos][xpos] = PIECE::NONE;
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
int CheckersMovement::ManhattanDistance(glm::ivec2 a_to, glm::ivec2 a_from)
{
	
	int ValueX1 = a_to.x;
	int ValueX2 = a_from.x;
	int ValueY1 = a_to.y;
	int ValueY2 = a_from.y;
	
	int ReturnX;
	int ReturnY;

	ReturnX = abs(ValueX1 - ValueX2);
	ReturnY = abs(ValueY1 - ValueY2);

	return ReturnX + ReturnY;
}

void CheckersMovement::ClearSpot(int a_oldz, int a_oldx)
{
	m_board[a_oldx][a_oldz] = PIECE::NONE;
	m_drawboard->GetCurrentBoard(m_board);
}


//Give it the Jump position and a Random Direcetion to check for another jump
bool CheckersMovement::DoubleJump(glm::ivec2 a_newPos, glm::ivec2 dir, PIECE a_type)
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
	//Clear Possible moves 
	memset(m_jumps, 0, sizeof(m_jumps));
	ClearPossibleMoves();
	ShowPossibleMoves();
	m_turn = (m_turn == TURN::PLAYER_1) ? TURN::PLAYER_2 : TURN::PLAYER_1;
	
}

//Basically Check all valid moves
void CheckersMovement::ShowPossibleMoves()
{
	int index;
	if (m_turn == TURN::PLAYER_1)
	{
		//Column Interation 
		for (int c = 0; c < 8; c++)
		{
			for (int r = 0; r < 8; r++)
			{
				index = 0;
				//////////////////////////////
				if (m_board[c][r] == PIECE::NONE || m_board[c][r] == PIECE::BLACK || m_board[c][r] == PIECE::BLACKKING)
				{
					continue;
				}
				////
				//Check Valid Moves
				PIECE current = m_board[c][r];

				bool possibleMoveUpRight = false,
					 possibleMoveUpleft = false,
					 possibleMoveDownRight = false,
					 possibleMoveDownLeft = false;
				//Before this Check for a KIng
				//Else do that shit

				glm::ivec2 pos = glm::ivec2(c, r);

				glm::ivec2 compare = glm::ivec2(0, 8);

				glm::ivec2 movePosUpRight = pos + m_moveUpRight;
				glm::ivec2 movePosUpLeft = pos + m_moveUpLeft;
				glm::ivec2 movePosDownRight = pos + m_moveDownRight;
				glm::ivec2 movePosDownLeft = pos + m_moveDownLeft;

				switch (current)
				{
					case RED://Starts from row 0
						possibleMoveUpRight = isValidMovement(movePosUpRight, current, pos);
						possibleMoveUpleft = isValidMovement(movePosUpLeft, current, pos);
						//Checks for Possible jumps
						if (isValidMovement(movePosUpRight + m_moveUpRight, current, pos))
						{
							m_jumps[index] = true;
								index++;
						}

						if (isValidMovement(movePosUpLeft + m_moveUpLeft, current, pos))
						{
							m_jumps[index] = true;
							index++;
						}
						break;

					case REDKING:

						//Possible Move check
						possibleMoveUpRight = isValidMovement(movePosUpRight, current, pos);
						possibleMoveUpleft = isValidMovement(movePosUpLeft, current, pos);
						possibleMoveDownRight = isValidMovement(movePosDownRight, current, pos);
						possibleMoveDownLeft = isValidMovement(movePosDownLeft, current, pos);

						//Possible Jump check
						//Checks for Possible jumps 
						if (isValidMovement(movePosUpRight + m_moveUpRight, current, pos))
						{
							m_jumps[index] = true;
							index++;
						}

						if (isValidMovement(movePosUpLeft + m_moveUpLeft, current, pos))
						{
							m_jumps[index] = true;
							index++;
						}

						if (isValidMovement(movePosDownRight + m_moveDownRight, current, pos))
						{
							m_jumps[index] = true;
							index++;
						}

						if (isValidMovement(movePosDownLeft + m_moveDownLeft, current, pos))
						{
							m_jumps[index] = true;
							index++;
						}
						break;
					
					default:
						break;
				}
				

				//Shows all possible moves
				//For each possible option from the case
				if (possibleMoveUpRight == true && Compare(movePosUpRight, compare))
				{
					m_board[movePosUpRight.x][movePosUpRight.y] = PIECE::POSSIBLEMOVE;
					possibleMoveUpRight = false;
				}
				if (possibleMoveUpleft == true && Compare(movePosUpLeft, compare))
				{
					m_board[movePosUpLeft.x][movePosUpLeft.y] = PIECE::POSSIBLEMOVE;
					possibleMoveUpRight = false;
				}
				if (possibleMoveDownRight == true && Compare(movePosDownRight, compare))
				{
					m_board[movePosDownRight.x][movePosDownRight.y] = PIECE::POSSIBLEMOVE;
					possibleMoveUpRight = false;
				}
				if (possibleMoveDownLeft == true && Compare(movePosDownLeft, compare))
				{
					m_board[movePosDownLeft.x][movePosDownLeft.y] = PIECE::POSSIBLEMOVE;
					possibleMoveUpRight = false;
				}
			}
		}
		m_drawboard->GetCurrentBoard(m_board);
	}
}
//Compares your current vector with the Vector Detailed Below
//Minimun Value you want to compare with
//Maximum Value you want to compare with
bool CheckersMovement::Compare(glm::ivec2 a_curValue, glm::ivec2 a_MinMax)
{
	if ((a_curValue.x > a_MinMax.x && a_curValue.x < a_MinMax.y)
		&& (a_curValue.y > a_MinMax.x && a_curValue.y < a_MinMax.y))
	{
		return true;
	}
	else
		//Value out of bounds
		return false;
}

//Gets the list of options for the AI
void CheckersMovement::GetListOfMoves()
{

}

//Maybe for AI
void CheckersMovement::MakeMove()
{

}
//Clears the moves :P
void CheckersMovement::ClearPossibleMoves()
{
	for (int c = 0; c < 8; ++c)
	{
		for (int r = 0; r < 8; ++r)
		{
			//Resets the piece for safe keepings
			if (m_board[c][r] == PIECE::POSSIBLEMOVE)
			{
				m_board[c][r] = PIECE::NONE;
			}
		}
	}
}
//Forward 
bool CheckersMovement::IsForwardMovement(glm::ivec2 a_newpos, glm::ivec2 a_oldpos)
{
	return (a_newpos.y - a_oldpos.y) > 0;
}