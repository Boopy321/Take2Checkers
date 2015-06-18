#include "CheckersMovement.h"
#include "CheckersProject.h"
#include "Assets\Camera\FlyCamera.h"
#include "CheckersPlayer.h"
#include <vector>
//Game Tagged function are required outside the class
//Utility are not required outside of the class



CheckersMovement::CheckersMovement()
{
	m_totalcount = 12;


	//Resize the vectors for Checkers
	m_rows = 8;
	m_cols = 8;

	m_drawboard = new CheckersProject();
	
	m_player1 = new CheckersPlayer(m_drawboard,this);
	m_player2 = new CheckersPlayer(m_drawboard,this);

	m_jump = false;
	m_delete = false;

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
//Utility
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

	ShowPossibleMoves();
	m_drawboard->GetCurrentBoard(m_board);

}
//GAME
void CheckersMovement::Update(FlyCamera &_gameCamera, float a_deltatime)
{
	m_drawboard->Draw(_gameCamera, a_deltatime);
	if (m_turn == TURN::PLAYER_1)
		m_player1->Update();
	else
		m_player2->Update();
	//Upgrade to a King?
	for (int i = 0; i <= 7; i++)
	{
		if (m_board[0][i] == PIECE::BLACK)
		{
			m_board[0][i] = PIECE::BLACKKING;
			m_drawboard->GetCurrentBoard(m_board);
		}
	}
	//Upgrade to a king?
	for (int i = 7; i >= 0; i--)
	{
		if (m_board[7][i] == PIECE::RED)
		{
			m_board[7][i] = PIECE::REDKING;
			m_drawboard->GetCurrentBoard(m_board);
		}
	}
	if (m_turn == TURN::GAMEOVER)
	{
		//END GAME HERE!!!!!!!!!!!!!
	}
	

}
//Game
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
		return PIECE::NONE;

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
		return PIECE::NONE;
	}
	else
		return PIECE::NONE;
}
//Game
bool CheckersMovement::PlacePiece(PIECE a_type, int x, int z,int oldposx,int oldposz)
{

	m_delete = true;

	glm::ivec2 possibleoption = glm::ivec2(x, z);

	//If ther is a possible 
	if (m_jump == true)
	{
		for (unsigned int i = 0; i <= m_jumpmoves.size() - 1; ++i)
		{ 
			if (m_jumpmoves[i].newLocation == possibleoption && isValidMovement(glm::ivec2(x, z), a_type, glm::ivec2(oldposx, oldposz)) == true)
			{
				m_board[x][z] = a_type;
				ClearSpot(oldposz, oldposx);
				return true;
			}
		}
		m_delete = false;
 		return false;
	}

	if (isValidMovement(glm::ivec2(x,z),a_type,glm::ivec2(oldposx, oldposz)))
	{
		m_board[x][z] = a_type;
		ClearSpot(oldposz, oldposx);
		return true;
	}
	else
		return false;
}

//Game
void CheckersMovement::ClearSpot(int a_oldz, int a_oldx)
{
	if (m_board[a_oldx][a_oldz] == PIECE::RED || m_board[a_oldx][a_oldz] == PIECE::REDKING)
	{
		m_redcount -= 1;
	}

	if (m_board[a_oldx][a_oldz] == PIECE::BLACK || m_board[a_oldx][a_oldz] == PIECE::BLACKKING)
	{
		m_blackcount -= 1;
	}

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
//Game
void CheckersMovement::SwitchTurn()
{
	m_jump = false;
	//Clear Possible moves 
	Clear();
	m_turn = (m_turn == TURN::PLAYER_1) ? TURN::PLAYER_2 : TURN::PLAYER_1;
	if (m_turn == TURN::PLAYER_2)
	{
		ClearPossibleMoves();
	}
	ShowPossibleMoves();
	m_drawboard->GetCurrentBoard(m_board);
	
}

//Game Called
void CheckersMovement::ShowPossibleMoves()
{
	int index;
	glm::ivec2 compare = glm::ivec2(0, 8);
	Action action;
#pragma region Player1


	if (m_turn == TURN::PLAYER_1)
	{
		//Column Interation 
		for (int c = 0; c < 8; c++)
		{
			for (int r = 0; r < 8; r++)
			{
				
				index = 0;
				glm::ivec2 temp;
				temp = glm::ivec2(9, 9);
				//////////////////////////////
				if (!m_deletemoves.empty())
				{ 
					temp = m_deletemoves[0];
				}
				if (m_board[c][r] == PIECE::NONE || m_board[c][r] == PIECE::BLACK || m_board[c][r] == PIECE::BLACKKING || temp == glm::ivec2(c, r))
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
					if (isValidMovement(movePosUpRight + m_moveUpRight, current, pos) && Compare(movePosUpRight + m_moveUpRight, compare))
					{
						m_jump = true;

						action.newLocation = movePosUpRight + m_moveUpRight;
						action.originalLocation = glm::ivec2(c, r);
						action.pieceType = current;
						m_jumpmoves.push_back(action);

					
						index++;
					}

					if (isValidMovement(movePosUpLeft + m_moveUpLeft, current, pos) && Compare(movePosUpLeft + m_moveUpLeft, compare))
					{
						m_jump = true;

						action.newLocation = movePosUpLeft + m_moveUpLeft;
						action.originalLocation = glm::ivec2(c, r);
						action.pieceType = current;
						m_jumpmoves.push_back(action);

						
						index++;
					}
					break;

				case REDKING:
					//Possible Jump check
					possibleMoveUpRight = isValidMovement(movePosUpRight, current, pos);
					possibleMoveUpleft = isValidMovement(movePosUpLeft, current, pos);
					possibleMoveDownLeft = isValidMovement(movePosDownLeft, current, pos);
					possibleMoveDownRight = isValidMovement(movePosDownRight, current, pos);

					//Checks for Possible jumps 
					if (isValidMovement(movePosUpRight + m_moveUpRight, current, pos) && Compare(movePosUpRight + m_moveUpRight, compare))
					{
						m_jump = true;

						action.newLocation = movePosUpRight + m_moveUpRight;
						action.originalLocation = glm::ivec2(c, r);
						action.pieceType = current;
						m_jumpmoves.push_back(action);

						index++;
					}

					if (isValidMovement(movePosUpLeft + m_moveUpLeft, current, pos) && Compare(movePosUpLeft + m_moveUpLeft, compare))
					{
						m_jump = true;

						action.newLocation = movePosUpLeft + m_moveUpLeft;
						action.originalLocation = glm::ivec2(c, r);
						action.pieceType = current;
						m_jumpmoves.push_back(action);

						
						index++;
					}
					if (isValidMovement(movePosDownRight + m_moveDownRight, current, pos) && Compare(movePosDownRight + m_moveDownRight, compare))
					{
						m_jump = true;

						action.newLocation = movePosDownRight + m_moveDownRight;
						action.originalLocation = glm::ivec2(c, r);
						action.pieceType = current;
						m_jumpmoves.push_back(action);

						index++;
					}

					if (isValidMovement(movePosDownLeft + m_moveDownLeft, current, pos) && Compare(movePosDownLeft + m_moveDownLeft, compare))
					{
						m_jump = true;

						action.newLocation = movePosDownLeft + m_moveDownLeft;
						action.originalLocation = glm::ivec2(c, r);
						action.pieceType = current;
						m_jumpmoves.push_back(action);

						index++;
					}
					break;

				default:
					break;
				}

				//Shows all possible moves
				//For each possible option from the case
				if (m_jump == false)
				{
					if (possibleMoveUpRight == true && Compare(movePosUpRight, compare))
					{
						m_board[movePosUpRight.x][movePosUpRight.y] = PIECE::POSSIBLEMOVE;

						action.newLocation = movePosUpRight;
						action.originalLocation = glm::ivec2(c, r);
						action.pieceType = current;
						m_normMoves.push_back(action);

						possibleMoveUpRight = false;
					}

					if (possibleMoveUpleft == true && Compare(movePosUpLeft, compare))
					{
						m_board[movePosUpLeft.x][movePosUpLeft.y] = PIECE::POSSIBLEMOVE;

						action.newLocation = movePosUpLeft;
						action.originalLocation = glm::ivec2(c, r);
						action.pieceType = current;
						m_normMoves.push_back(action);
						
						possibleMoveUpRight = false;
					}

					if (possibleMoveDownRight == true && Compare(movePosDownRight, compare))
					{
						m_board[movePosDownRight.x][movePosDownRight.y] = PIECE::POSSIBLEMOVE;

						action.newLocation = movePosUpLeft;
						action.originalLocation = glm::ivec2(c, r);
						action.pieceType = current;
						m_normMoves.push_back(action);

						possibleMoveUpRight = false;
					}

					if (possibleMoveDownLeft == true && Compare(movePosDownLeft, compare))
					{
						m_board[movePosDownLeft.x][movePosDownLeft.y] = PIECE::POSSIBLEMOVE;
						
						action.newLocation = movePosUpLeft;
						action.originalLocation = glm::ivec2(c, r);
						action.pieceType = current;
						m_normMoves.push_back(action);

						possibleMoveUpRight = false;
					}
				}
				else
					ClearPossibleMoves();

			}
		}

		///Draw Possible jump option
		for (unsigned int i = 0; i < m_jumpmoves.size(); ++i)
		{
			glm::ivec2 jumps = m_jumpmoves[i].newLocation;
			if (Compare(jumps, compare))
			{
				m_board[jumps.x][jumps.y] = PIECE::POSSIBLEMOVE;
			}
		}
		//Give the draw state the current data board
		m_drawboard->GetCurrentBoard(m_board);
	}
#pragma endregion
	//For the Army of Black/
#pragma region Player2

	else if (m_turn == TURN::PLAYER_2)
	{
		for (int c = 0; c < 8; c++)
		{
			for (int r = 0; r < 8; r++)
			{
				index = 0;
				glm::ivec2 temp;
				//////////////////////////////
				if (!m_deletemoves.empty())
				{
					temp = m_deletemoves[0];
				}
				if (m_board[c][r] == PIECE::NONE || m_board[c][r] == PIECE::RED || m_board[c][r] == PIECE::REDKING || temp == glm::ivec2(c, r))
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

				glm::ivec2 movePosUpRight = pos + m_moveUpRight;
				glm::ivec2 movePosUpLeft = pos + m_moveUpLeft;
				glm::ivec2 movePosDownRight = pos + m_moveDownRight;
				glm::ivec2 movePosDownLeft = pos + m_moveDownLeft;

				switch (current)
				{
					case BLACK://Starts from row 0


						possibleMoveUpRight = isValidMovement(movePosUpRight, current, pos);
						possibleMoveUpleft = isValidMovement(movePosUpLeft, current, pos);

						//Checks for Possible jumps
						if (isValidMovement(movePosDownRight + m_moveDownRight, current, pos) && Compare(movePosDownRight + m_moveDownRight, compare))
						{
							m_jump = true;

							action.newLocation = movePosDownRight + m_moveDownRight;
							action.originalLocation = glm::ivec2(c, r);
							action.pieceType = current;
							m_jumpmoves.push_back(action);

							
							index++;
						}

						if (isValidMovement(movePosDownLeft + m_moveDownLeft, current, pos) && Compare(movePosDownLeft + m_moveDownLeft, compare))
						{
							m_jump = true;

							action.newLocation = movePosDownLeft + m_moveDownLeft;
							action.originalLocation = glm::ivec2(c, r);
							action.pieceType = current;
							m_jumpmoves.push_back(action);

						
							index++;
						}
						break;

					case BLACKKING:
						//Possible Jump check
						possibleMoveUpRight = isValidMovement(movePosUpRight, current, pos);
						possibleMoveUpleft = isValidMovement(movePosUpLeft, current, pos);
						possibleMoveDownLeft = isValidMovement(movePosDownLeft, current, pos);
						possibleMoveDownRight = isValidMovement(movePosDownRight, current, pos);

						//Checks for Possible jumps 
						if (isValidMovement(movePosUpRight + m_moveUpRight, current, pos) && Compare(movePosUpRight + m_moveUpRight, compare))
						{
							m_jump = true;

							action.newLocation = movePosUpRight + m_moveUpRight;
							action.originalLocation = glm::ivec2(c, r);
							action.pieceType = current;
							m_jumpmoves.push_back(action);

							index++;
						}

						if (isValidMovement(movePosUpLeft + m_moveUpLeft, current, pos) && Compare(movePosUpLeft + m_moveUpLeft, compare))
						{
							m_jump = true;

							action.newLocation = movePosUpLeft + m_moveUpLeft;
							action.originalLocation = glm::ivec2(c, r);
							action.pieceType = current;
							m_jumpmoves.push_back(action);

							
							index++;
						}
						if (isValidMovement(movePosDownRight + m_moveDownRight, current, pos) && Compare(movePosDownRight + m_moveDownRight, compare))
						{
							m_jump = true;

							action.newLocation = movePosDownRight + m_moveDownRight;
							action.originalLocation = glm::ivec2(c, r);
							action.pieceType = current;
							m_jumpmoves.push_back(action);

							
							index++;
						}

						if (isValidMovement(movePosDownLeft + m_moveDownLeft, current, pos) && Compare(movePosDownLeft + m_moveDownLeft, compare))
						{
							m_jump = true;

							action.newLocation = movePosDownLeft + m_moveDownLeft;
							action.originalLocation = glm::ivec2(c, r);
							action.pieceType = current;
							m_jumpmoves.push_back(action);

						
							index++;
						}
						break;

					default:
						break;
				}//Switch End
			}//For End
		}//For loop
	}//if end
#pragma endregion
}
#pragma region Utility

//Utility
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
//Utility
//Forward 
bool CheckersMovement::IsForwardMovement(glm::ivec2 a_newpos, glm::ivec2 a_oldpos)
{
	return (a_newpos.x - a_oldpos.x) > 0;
}
//used within the Detecting possible moves so it does not delete the freckon piece;
bool CheckersMovement::ShowCurrentPieceMoves(glm::ivec2 oldpos, PIECE a_type)
{
	ClearPossibleMoves();
	glm::ivec2 compare = glm::ivec2(0, 8);
	glm::ivec2 movePosUpRight = oldpos + m_moveUpRight + m_moveUpRight;
	glm::ivec2 movePosUpLeft = oldpos + m_moveUpLeft + m_moveUpLeft;
	glm::ivec2 movePosDownRight = oldpos + m_moveDownRight + m_moveDownRight;
	glm::ivec2 movePosDownLeft = oldpos + m_moveDownLeft + m_moveDownLeft;

	Action action;

	m_localJump = false;
	m_delete = false;
	if (m_turn == TURN::PLAYER_1)
#pragma region Red
	switch (a_type)
	{
		case RED://TEAM REDDDD!!!!!!

			//Checks for Possible jumps
			if (isValidMovement(movePosUpRight, a_type, oldpos) && Compare(movePosUpRight, compare))
			{
				m_localJump = true;
				action.newLocation = movePosUpRight;
				action.originalLocation = oldpos;
				action.pieceType = a_type;
				m_jumpmoves.push_back(action);

				m_board[movePosUpRight.x][movePosUpRight.y] = PIECE::POSSIBLEMOVE;
			}

			if (isValidMovement(movePosUpLeft, a_type, oldpos) && Compare(movePosUpLeft, compare))
			{
				m_localJump = true;
				action.newLocation = movePosUpLeft;
				action.originalLocation = oldpos;
				action.pieceType = a_type;
				m_jumpmoves.push_back(action);
				m_board[movePosUpLeft.x][movePosUpLeft.y] = PIECE::POSSIBLEMOVE;
			}
			break;

		case REDKING:
			//Possible Jump check

			//Checks for Possible jumps 
			if (isValidMovement(movePosUpRight, a_type, oldpos) && Compare(movePosUpRight, compare))
			{
				m_localJump = true;
				action.newLocation = movePosUpRight;
				action.originalLocation = oldpos;
				action.pieceType = a_type;
				m_jumpmoves.push_back(action);
				m_board[movePosUpRight.x][movePosUpRight.y] = PIECE::POSSIBLEMOVE;
			}

			if (isValidMovement(movePosUpLeft, a_type, oldpos) && Compare(movePosUpLeft, compare))
			{
				m_localJump = true;
				action.newLocation = movePosUpLeft;
				action.originalLocation = oldpos;
				action.pieceType = a_type;
				m_jumpmoves.push_back(action);
	
				m_board[movePosUpLeft.x][movePosUpLeft.y] = PIECE::POSSIBLEMOVE;
			}

			if (isValidMovement(movePosDownRight, a_type, oldpos) && Compare(movePosDownRight, compare))
			{
				m_localJump = true;
				action.newLocation = movePosDownRight;
				action.originalLocation = oldpos;
				action.pieceType = a_type;
				m_jumpmoves.push_back(action);
			
				m_board[movePosDownRight.x][movePosDownRight.y] = PIECE::POSSIBLEMOVE;
			}

			if (isValidMovement(movePosDownLeft, a_type, oldpos) && Compare(movePosDownLeft, compare))
			{
				m_localJump = true;
				action.newLocation = movePosDownLeft;
				action.originalLocation = oldpos;
				action.pieceType = a_type;
				m_jumpmoves.push_back(action);
		
				m_board[movePosDownLeft.x][movePosDownLeft.y] = PIECE::POSSIBLEMOVE;
			}
			break;

		default:
			break;
	}
#pragma endregion

#pragma region Black
	////// CXomplete ! 
	//Double black jumps work 
	else
	{
		switch (a_type)
		{
			case BLACK:

				if (isValidMovement(movePosDownLeft, a_type, oldpos) && Compare(movePosDownLeft, compare))
				{
					m_localJump = true;
					action.newLocation = movePosDownLeft;
					action.originalLocation = oldpos;
					action.pieceType = a_type;
					m_jumpmoves.push_back(action);
				}

				if (isValidMovement(movePosDownRight, a_type, oldpos) && Compare(movePosDownRight, compare))
				{
					m_localJump = true;
					action.newLocation = movePosDownRight;
					action.originalLocation = oldpos;
					action.pieceType = a_type;
					m_jumpmoves.push_back(action);
					
				}
				break;

			case BLACKKING:

				if (isValidMovement(movePosUpRight, a_type, oldpos) && Compare(movePosUpRight, compare))
				{
					m_localJump = true;
					action.newLocation = movePosUpRight;
					action.originalLocation = oldpos;
					action.pieceType = a_type;
					m_jumpmoves.push_back(action);
					
				}

				if (isValidMovement(movePosUpLeft, a_type, oldpos) && Compare(movePosUpLeft, compare))
				{
					m_localJump = true;
					action.newLocation = movePosUpLeft;
					action.originalLocation = oldpos;
					action.pieceType = a_type;
					m_jumpmoves.push_back(action);
				
				}

				if (isValidMovement(movePosDownRight, a_type, oldpos) && Compare(movePosDownRight, compare))
				{
					m_localJump = true;
					action.newLocation = movePosDownRight;
					action.originalLocation = oldpos;
					action.pieceType = a_type;
					m_jumpmoves.push_back(action);
					
				}

				if (isValidMovement(movePosDownLeft, a_type, oldpos) && Compare(movePosDownLeft, compare))
				{
					m_localJump = true;
					action.newLocation = movePosDownLeft;
					action.originalLocation = oldpos;
					action.pieceType = a_type;
					m_jumpmoves.push_back(action);
				}
				break;
			default:
				break;
		}
	}

#pragma endregion

	m_drawboard->GetCurrentBoard(m_board);
	return m_localJump;
}
//Utility
void CheckersMovement::Clear()
{
	m_delete = false;

	while (!m_normMoves.empty())
	{
		m_normMoves.pop_back();
	}

	while (!m_jumpmoves.empty())
	{
		m_jumpmoves.pop_back();
	}

	for (unsigned int i = 0; i < m_deletemoves.size(); ++i)
	{
		m_board[m_deletemoves[i].x][m_deletemoves[i].y] = PIECE::NONE;
		m_drawboard->GetCurrentBoard(m_board);
		m_deletemoves.pop_back();
	}
	ClearPossibleMoves();
}
//Utility
bool CheckersMovement::IsBackwardMovement(glm::ivec2 a_newpos, glm::ivec2 a_oldpos)
{
	return (a_newpos.x - a_oldpos.x) < 0;
}
//Utility
bool CheckersMovement::isAbleJump(glm::ivec2 a_newPos, PIECE a_type, glm::ivec2 a_oldPos)
{

	bool Forward;

	int Distance = ManhattanDistance(a_newPos, a_oldPos);
	bool Diagonal = isDiagonal(a_newPos, a_oldPos, a_type);
	if (m_turn == TURN::PLAYER_1)
		Forward = IsForwardMovement(a_newPos, a_oldPos) || a_type == PIECE::REDKING;
	else
		Forward = IsBackwardMovement(a_newPos, a_oldPos) || a_type == PIECE::BLACKKING;

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
//Utility
bool CheckersMovement::isAbleMove(glm::ivec2 a_newPos, PIECE a_type, glm::ivec2 a_oldpos)
{
	bool Forward = false;

	int Distance = ManhattanDistance(a_newPos, a_oldpos);
	bool Diagonal = isDiagonal(a_newPos, a_oldpos, a_type);

	if (m_turn == TURN::PLAYER_1)
		Forward = IsForwardMovement(a_newPos, a_oldpos) || a_type == PIECE::REDKING;
	else
		Forward = IsBackwardMovement(a_newPos, a_oldpos) || a_type == PIECE::BLACKKING;

	if (m_board[a_newPos.x][a_newPos.y] == PIECE::NONE || m_board[a_newPos.x][a_newPos.y] == PIECE::POSSIBLEMOVE)
	{
		if (Distance == 2 &&  ///Gets the Distance
			Diagonal &&
			Forward)   //Is there as piece in the middle
		{
			return true;
		}
		else
			return false;
	}
	else return false;
}
//Utility
bool CheckersMovement::isDiagonal(glm::ivec2 newpos, glm::ivec2 oldpos, PIECE a_type)
{
	int xIncrement = abs(newpos.x - oldpos.x);
	int yIncrement = abs(newpos.y - oldpos.y);

	return (xIncrement == yIncrement);
}
//Utility
bool CheckersMovement::isPieceThere(glm::ivec2 newpos, glm::ivec2 oldpos){
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
				if (m_delete == false)
				{
					return true;
				}
				else
					m_deletemoves.push_back(glm::ivec2(zpos, xpos));
				return true;

			}
			else if (m_board[zpos][xpos] == PIECE::BLACK)
			{
				if (m_delete == false)
				{
					return true;
				}
				else
					m_deletemoves.push_back(glm::ivec2(zpos, xpos));
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
				if (m_delete == false)
				{
					return true;
				}
				else
					m_deletemoves.push_back(glm::ivec2(zpos, xpos));
				return true;
			}
			else if (m_board[zpos][xpos] == PIECE::RED)
			{
				if (m_delete == false)
				{
					return true;
				}
				else
					m_deletemoves.push_back(glm::ivec2(zpos, xpos));
				return true;
			}
			else
				return false;
		}
	}
	return false;

}

#pragma endregion

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
//Main Function that Calls all Utility Designed to prove for a valid movement
bool CheckersMovement::isValidMovement(glm::ivec2 a_newPos, PIECE a_type, glm::ivec2 a_oldpos)
{
	if (m_turn == TURN::PLAYER_1)
	{
		if (m_board[a_newPos.x][a_newPos.y] == NONE || m_board[a_newPos.x][a_newPos.y] == POSSIBLEMOVE)
		{
			//Recursive Function based on new posistion Does not check for a Triple jump but poops
			if (isAbleJump(a_newPos, a_type, a_oldpos))
				return true;

			else if (isAbleMove(a_newPos, a_type, a_oldpos))
			{
				return true;
			}
			else
				return false;
		}
		return false;
	}
	else
	{
		if (m_board[a_newPos.x][a_newPos.y] == NONE || m_board[a_newPos.x][a_newPos.y] == POSSIBLEMOVE)
		{
			//Recursive Function based on new posistion Does not check for a Triple jump but poops
			if (isAbleJump(a_newPos, a_type, a_oldpos))
				return true;

			else if (isAbleMove(a_newPos, a_type, a_oldpos))
			{
				return true;
			}
			else
				return false;
		}
		return false;
	}

}
//Utility
//Compares your current vector with the Vector Detailed Below
//Minimun Value you want to compare with
//Maximum Value you want to compare with
bool CheckersMovement::Compare(glm::ivec2 a_curValue, glm::ivec2 a_MinMax)
{
	if ((a_curValue.x >= a_MinMax.x && a_curValue.x < a_MinMax.y)
		&& (a_curValue.y >= a_MinMax.x && a_curValue.y < a_MinMax.y))
	{
		return true;
	}
	else
		//Value out of bounds
		return false;
}
//PlayerCalled
PIECE CheckersMovement::UpgradeToKing(glm::ivec2 a_Pos, PIECE a_type)
{
	//Check the Posistion
	//Upgrade to a King?
	if (a_Pos.x == 0)
	{
		if (m_board[a_Pos.x][a_Pos.y] == PIECE::BLACK)
		{
			m_board[a_Pos.x][a_Pos.y] = PIECE::BLACKKING;
			m_drawboard->GetCurrentBoard(m_board);
			return PIECE::BLACKKING;
		}
	}
	else if (a_Pos.x == 7)
	{
		if (m_board[a_Pos.x][a_Pos.y] == PIECE::RED)
		{
			m_board[a_Pos.x][a_Pos.y] = PIECE::REDKING;
			m_drawboard->GetCurrentBoard(m_board);
			return PIECE::REDKING;
		}
	}
	else
		return a_type;
	
}
//Game
CheckersMovement* CheckersMovement::Clone ()
{
	CheckersMovement* clone = new CheckersMovement();//Recreate each value

	for (int c = 0; c < 8; ++c)
	{
		for (int r = 0; r < 8; ++r)
		{
			clone->m_board[c][r] = m_board[c][r];
		}
	}

	clone->m_turn = m_turn;

	return clone;
}

//Need the AI to perform ACTION
//MY ACTIONS INVOLVE

void CheckersMovement::performAction(Action* a_action)
{
	//Places that action down
	if (PlacePiece(a_action->pieceType, a_action->newLocation.x, a_action->newLocation.y, a_action->originalLocation.x, a_action->originalLocation.y) == true)
	{
		//Upgrade king if possible
		a_action->pieceType = UpgradeToKing(a_action->newLocation, a_action->pieceType);
		//
		Clear();
		if (ShowCurrentPieceMoves(a_action->newLocation, a_action->pieceType) && m_jump == true)
		{
			a_action->originalLocation = a_action->newLocation;
		}
		else
		{
			a_action->Reset();
			SwitchTurn();
		}
	}

}

//GAME OVER
bool CheckersMovement::isGameOver()
{
	if (m_redcount == 0)
	{
		m_turn == TURN::GAMEOVER;
		return true;
	}
	else if (m_blackcount == 0)
	{
		m_turn == TURN::GAMEOVER;
		return true;
	}
	else
		return false;
}

std::vector<Action> CheckersMovement::ReturnMoveSet()
{
	if (!m_jumpmoves.empty())
	{
		return m_normMoves;
	}
	else
		return m_jumpmoves;
}