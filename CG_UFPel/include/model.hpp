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
	glm::mat4 ModelMatrix;
	GLuint Texture;
	GLuint TextureID;
public:
	//programID loads the shader
	model( GLuint programID, const char * texture);
	glm::mat4 model::getModelMatrix();
	GLunint model::getModelMatrixID();
	GLunint model::getTexture();
	GLunint model::getTextureID();
	GLunint model::getMeshIndex();S
	//void model::clearbuffer();

	~model();
};

#endif
