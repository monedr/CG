#pragma once

#include <model.hpp>
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


class modelManager{

	// matrix settings
	GLuint VertexArrayID;
	// Get a handle for our "MVP" uniform
	GLuint MatrixID;
	GLuint ViewMatrixID;
	// Compute the MVP matrix from keyboard and mouse input
	//computeMatricesFromInputs(nUseMouse, g_nWidth, g_nHeight);
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 MVP;

	std::vector<mesh> meshVector;
	std::std::vector<model> modelVector;

public:
		GLunint model::getProgramID();
	modelManager();
	~modelManager();
};
