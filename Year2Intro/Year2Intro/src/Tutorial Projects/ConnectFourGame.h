#pragma once

class FlyCamera;
class Game;
class AI;
struct GLFWwindow;

#include <glm\vec3.hpp>

class ConnectFourGame
{
public:

	ConnectFourGame();
	ConnectFourGame(GLFWwindow* a_window);
	~ConnectFourGame();

	void GameLoop(FlyCamera &_gameCamera);
	void Draw(FlyCamera &_gameCamera, float a_deltatime);

private:

	Game* m_game;
	AI* m_ai;
	GLFWwindow* m_window;

	glm::vec3 m_pickPosition;
};

