#include "FBXDrawer.h"
#include "Assets\FBXModel\FBXModel.h"
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include "Assets\Light\Light.h"
#include "Assets\AntTweakBar\AntTweakBar.h"

FBXDrawer::FBXDrawer()
{
	m_worldtransform = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
	m_worldtransform = glm::rotate(m_worldtransform, glm::pi<float>() / 2, glm::vec3(-1, 0, 0));

}
FBXDrawer::FBXDrawer(AntTweakBar* a_bar)
{
	m_worldtransform = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
	m_worldtransform = glm::rotate(m_worldtransform, glm::pi<float>() / 2, glm::vec3(-1, 0, 0));
	
}	

FBXDrawer::~FBXDrawer()
{
}

void FBXDrawer::Draw(unsigned int a_program, Renderer* a_render, Light* a_light, FlyCamera &_gameCamera)
{
	m_model->SetTransform(m_worldtransform);
	m_model->FBXDraw(a_program,a_render,a_light,_gameCamera, m_worldtransform );
}

void FBXDrawer::SetPosition(glm::vec3& a_position)
{
	m_worldtransform[3] = glm::vec4(a_position, 1);
}

void FBXDrawer::SetModel(FBXModel* a_model)
{
	 m_model = a_model;
}

void FBXDrawer::SetScale(glm::vec3 a_scale)
{
	glm::mat4 scale = glm::scale(a_scale);
	m_worldtransform = m_worldtransform * scale;
}

void FBXDrawer::SetRotate(glm::vec3 a_angle)
{
	glm::mat4 rot = glm::rotate(m_worldtransform, glm::pi<float>() / 2, a_angle);
	m_worldtransform = m_worldtransform * rot;
}

