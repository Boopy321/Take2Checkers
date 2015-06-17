#include "MCTS.h"
#include <list>
#include "AIBase.h"





int MCTS::makeDecision(const Game& game)
{
	//1. Get a list of the available actions that could be performed
	std::vector<int> actions;
	game.getValidActions(actions);

	std::vector<float> actionScores;

	//	2. For each action :
	for each (int action in actions)
	{
		//a.Set a starting value of 0
		int value = 0;


		//b.For each playout :
		for (int a = 0; a < m_playouts; a++)
		{//		
			//Clone the current game
			m_clone = game.clone();

			//ii.Perform the action
			m_clone->performAction(action);

			while (m_clone->getCurrentGameState() == Game::UNKNOWN)
			{
				std::vector<int> nextmoves;
				
				m_clone->getValidActions(nextmoves);

				int action = rand() % nextmoves.size();

				m_clone->performAction(action);
				
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


	







