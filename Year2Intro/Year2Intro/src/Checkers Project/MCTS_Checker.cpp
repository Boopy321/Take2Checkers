#include "MCTS_Checker.h"
#include "CheckersMovement.h"
int MCTS_Checker::makeDecision(CheckersMovement& game)
{
	//1. Get a list of the available actions that could be performed
	
	std::vector<Action> actions;
	game.ShowPossibleMoves();

	actions = game.ReturnMoveSet();

	std::vector<float> actionScores;

	//	2. For each action :
	for each (Action action in actions)
	{
		//a.Set a starting value of 0
		int value = 0;


		//b.For each playout :
		for (int a = 0; a < m_playouts; a++)
		{//		
			//Clone the current game
			m_clone = game.Clone();

			//ii.Perform the action
			m_clone->performAction(&action);
			///////TO WRITE UP YOU LAZY BASTARD
			while (m_clone->getCurrentGameState() == TURN::GAMEOVER)
			{
				std::vector<Action> nextmoves;

				m_clone->ShowPossibleMoves();
				nextmoves = m_clone->ReturnMoveSet();
				int action = rand() % nextmoves.size();

				m_clone->performAction(&nextmoves[action]);

			}
			if (m_clone->getCurrentGameState() == Game::PLAYER_ONE)
				value -= 1;
			else
				value += 1;
		}
		//	iv.Delete the clone
		delete(m_clone);
		// c.Give the action a score based on value / playouts
		float actionscore = (float)value / (float)m_playouts;
		actionScores.push_back(actionscore);

	}
	float bestscore;
	bestscore = -999.0f;
	int bestAction = 1;

	for (int i = 0; i < actionScores.size(); i++)
	{
		if (bestscore < actionScores[i])
		{
			bestscore = actionScores[i];
			bestAction = i;
		}

	}
	return actions[bestAction];
}










