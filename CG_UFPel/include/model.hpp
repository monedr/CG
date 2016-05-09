#pragma once
#include <mesh.hpp>

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>


// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <shader.hpp>
#include <texture.hpp>
#include <controls.hpp>

#ifndef MODEL_H
#define MODEL_H

class model
{
	GLuint meshIndex;
	GLuint ModelMatrixID;
	glm::mat4 ModelMatrix;
	GLuint Texture;
	GLuint TextureID;
	mesh mesh;

public:
	//programID loads the shader
	model::model(GLuint programID, const char * texture, const char * myTextureSampler, mesh malha);

	void model::startTexture();
	void model::setTransformation();
	void model::drawModels();

	glm::mat4 model::getModelMatrix();
	GLuint model::getModelMatrixID();
	GLuint model::getTexture();
	GLuint model::getTextureID();
	GLuint model::getMeshIndex();
	//void model::clearbuffer();
	model::model();
	~model();
};

#endif
