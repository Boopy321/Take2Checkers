#include <gl_core_4_4.h>
#include "ConnectFourGame.h"
#include "Assets\AI\AIBase.h"
#include "Assets\AI\ConnectFour.h"
#include "Assets\Camera\FlyCamera.h"
#include <Gizmos.h>
#include "Assets\AI\MCTS.h"

ConnectFourGame::ConnectFourGame(GLFWwindow* a_window)
{
	m_game = new ConnectFour();
	m_ai = new MCTS(1000);
	m_window = a_window;
	
}

ConnectFourGame::~ConnectFourGame()
{
	Game* m_game;
	AI* m_ai;
}

void ConnectFourGame::Draw(FlyCamera &_gameCamera, float a_deltatime)
{
	m_game->draw();
	Gizmos::draw(_gameCamera.getProjectionView());
}
void ConnectFourGame::GameLoop(FlyCamera &_gameCamera)
{
	static bool moveMade = false;
	// if the game isn't over...
	if (m_game->getCurrentGameState() == Game::UNKNOWN) {
		// if it is the user's turn (player 1)
		if (m_game->getCurrentPlayer() == Game::PLAYER_ONE) {
			// if the mouse button is down...
			if (glfwGetMouseButton(m_window, 0) == GLFW_PRESS) {
				// if the mouse JUST went down then make a choice
				if (moveMade == false) {
					moveMade = true;
					// get the mouse position within the game grid
					double x = 0, y = 0;
					glfwGetCursorPos(m_window, &x, &y);
					m_pickPosition = _gameCamera.pickAgainstPlane(
						(float)x, (float)y, glm::vec4(0, 1, 0, 0));
					// determine which column was chosen
					int column = (int)((m_pickPosition.z +
						ConnectFour::COLUMNS) / 2);
					// if we clicked in the area for a
					// valid column then perform that action
					if (m_game->isActionValid(column))
						m_game->performAction(column);
				}
			}
			else
				moveMade = false;
		}
		else {
			// it is the opponent's turn (player 2)
			// use the A.I. to make a decision
			m_game->performAction(m_ai->makeDecision(*m_game));
		}
	}
}
