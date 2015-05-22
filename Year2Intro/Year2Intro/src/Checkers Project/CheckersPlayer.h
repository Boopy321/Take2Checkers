#pragma once

// Will Not draw. Will only update the pieces that the player uses
struct GLFWwindow;

class CheckersPlayer
{
public:
	CheckersPlayer();
	~CheckersPlayer();

	bool ValidMove();

	void Update();

	float xpos, ypos, zpos;
private:

	bool m_move;
	float vForward, vRight;
	float moveDir;
	
	GLFWwindow* m_pWindow;
};