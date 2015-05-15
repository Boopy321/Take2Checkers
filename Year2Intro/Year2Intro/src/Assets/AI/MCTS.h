#pragma once

#include "AIBase.h"
#include "ConnectFour.h"

class MCTS : public AI
{
public:
	MCTS(int playouts) :
		m_playouts(playouts) {
	}
	virtual ~MCTS() {}
	virtual int makeDecision(const Game& game);
private:
	int m_playouts;	Game* m_clone;
	Game* curGame;
};

