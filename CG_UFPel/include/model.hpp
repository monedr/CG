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

	// Create and compile our GLSL program from the shaders
	GLuint programID;

	// Get a handle for our "MVP" uniform
	GLuint MatrixID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;

	// Load the texture
	GLuint Texture;

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID;
	
	mesh malha;

public:
	
	model::model(const char * vertexshader, const char * fragmentshader, const char *texture, const char *textureSampler, mesh outraMalha);
	GLuint model::getProgramID();
	GLuint model::getMatrixID();
	GLuint model::getViewMatrixID();
	GLuint model::getModelMatrixID();
	GLuint model::getTexture();
	GLuint model::getTextureID();
	  mesh model::getMesh();

	~model();
};

#endif
