#pragma once
#include <mesh.hpp>

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <shader.hpp>
#include <texture.hpp>

#ifndef MODEL_H
#define MODEL_H

class model
{
	GLuint meshIndex;
	GLuint ModelMatrixID;
	GLuint Texture;
	GLuint TextureID;
	GLuint programID;
public:
	model(const char * vertexshader, const char * fragmentshader, const char * texture);
	void model::clearbuffer();
	~model();
};

#endif
