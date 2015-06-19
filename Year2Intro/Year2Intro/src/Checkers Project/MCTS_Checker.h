#pragma once
#include "CheckersMovement.h"
class MCTS_Checker
{
public:
	MCTS_Checker(int playouts) :
		m_playouts(playouts) {
	}
	virtual ~MCTS_Checker() {}
	virtual Action makeDecision(CheckersMovement& game);
private:
	int m_playouts;	CheckersMovement* m_clone;
	CheckersMovement* curGame;
};
