#pragma once

struct GLFWwindow;
class Light;

#include "Assets/Camera/FlyCamera.h"
#include <AntTweakBar.h>
#include "Assets/InputManager/InputManager.h"
#include "Checkers Project\CheckersProject.h"


class AntTweakBar;

//Global space so any project can use AntTweakBar


class Application
{
public:
	Application();
	~Application();
	void run();

protected:

	GLFWwindow* window;
	float previousTime;
	FlyCamera _gameCamera;

private:
	bool startUp();

	void update(float deltatime);
	void draw(float a_deltatime);
	void shutdown();
	
	float m_frameCounter;
	float m_framerate;
	float m_frameElaspedtime;

	int m_wHeight;
	int m_wWidth;

	AntTweakBar* m_bar;

	Light* m_light;

	CheckersProject* CurrentProject;

	InputManager m_keyManager;

	unsigned int m_ProgramID;


	glm::vec4 m_clearColour;
	TURN m_turn;
	Renderer* m_render;
};

