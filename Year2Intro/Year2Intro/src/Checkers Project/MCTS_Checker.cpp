#include "MCTS_Checker.h"
#include "CheckersMovement.h"
#include "Assets\Timer\Timer.h"

typedef std::chrono::duration<double> seconds;

Action MCTS_Checker::makeDecision(CheckersMovement& game)
{
	//1. Get a list of the available actions that could be performed
	
	std::vector<Action> actions;
	game.ShowPossibleMoves();

	actions = game.ReturnMoveSet();


	if (actions.size() == 0)
	{
		Action temp;
		temp.newLocation = glm::ivec2(0, 0);
		temp.originalLocation = glm::ivec2(0, 0);
		temp.pieceType = PIECE::WINNING_MLG_PRO_MATE;

		return temp;

	}

	Timer timer(true);

	std::vector<float> actionScores;
	if (actions.size() == 1)
	{
		return actions[0];
	}
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
			while (m_clone->isGameOver() == STATE::UNKNOWN && timer.Elapsed() > seconds(1.0))
			{
				std::vector<Action> nextmoves;

				m_clone->ShowPossibleMoves();
				nextmoves = m_clone->ReturnMoveSet();
				int action = rand() % nextmoves.size();

				m_clone->performAction(&nextmoves[action]);

			}
			if (m_clone->isGameOver() == STATE::PLAYER_ONE)
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










