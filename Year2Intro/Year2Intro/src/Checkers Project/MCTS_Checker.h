#pragma once
#include "CheckersMovement.h"
class MCTS_Checker
{
public:
	MCTS_Checker(int playouts) :
		m_playouts(playouts) {
	}
	virtual ~MCTS_Checker() {}
	virtual int makeDecision(const CheckersMovement& game);
private:
	int m_playouts;	CheckersMovement* m_clone;
	CheckersMovement* curGame;
};

//class AI {
//public:
//
//	AI() {}
//	virtual ~AI() {}
//
//	// makes a decision for the current game
//	virtual int	makeDecision(const CheckersMovement& game) = 0;
//};
//
//// an A.I. opponent that chooses purely random actions to perform
//class RandomAI : public AI {
//public:
//
//	RandomAI() {}
//	virtual ~RandomAI() {}
//
//	// randomly choose an action to perform
//	virtual int	makeDecision(const CheckersMovement& game) {
//		std::vector<int> actions;
//		CheckersMovement.getValidActions(actions);
//		if (actions.size() > 0)
//			return actions[rand() % actions.size()];
//		else
//			return -1;
//	}
//};