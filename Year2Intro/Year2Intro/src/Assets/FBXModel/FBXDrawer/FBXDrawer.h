#pragma once

#include <glm\glm.hpp>

class FBXModel;
class FlyCamera;
class Renderer;
class Light;
class AntTweakBar;

class FBXDrawer
{
public:

	FBXDrawer();
	FBXDrawer(AntTweakBar* a_bar);
	~FBXDrawer();

	void Draw(unsigned int a_program, Renderer* a_render,Light* a_light, FlyCamera &_gameCamera);
	void SetPosition(glm::vec3& a_position);

	void SetModel(FBXModel* a_model);
	void SetScale(glm::vec3 a_scale);
	void SetRotate( glm::vec3 a_angle);

private:

	FBXModel* m_model;
	glm::mat4 m_worldtransform;
	glm::vec3 m_Rotate;

};


