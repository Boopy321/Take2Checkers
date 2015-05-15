#pragma once

#include <glm/glm.hpp>

struct Vertex
{
	glm::vec4 position;
	glm::vec4 tangent;
	glm::vec3 normal;
	glm::vec2 uv;
	glm::vec4 colour;
};

