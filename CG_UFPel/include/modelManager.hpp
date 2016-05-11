//#pragma once

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
	// Get a handle for our "MVP" uniform
	GLuint MatrixID;
	GLuint ViewMatrixID;
	GLuint programID;
	GLuint LightID;

	// Compute the MVP matrix from keyboard and mouse input
	//computeMatricesFromInputs(nUseMouse, g_nWidth, g_nHeight);
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 MVP;


	std::vector<mesh> meshVector;
	std::vector<model> modelVector;


public:

	modelManager::modelManager(char * vertexshader, char * fragmentshader);
	
	void modelManager::creatModel( char* texture, char* myTextureSampler, mesh mesh);
	void modelManager::loadMesh(char * path);
	void modelManager::calcMVP(model model);
	void modelManager::setMatrixToGPU(model model);
	void modelManager::setLightPosition(char * LightPosition_worldspace);

	GLuint modelManager::getLightID();
	GLuint modelManager::getProgramID();
	GLuint modelManager::getMatrixID();
	GLuint modelManager::getViewMatrixID();
	std::vector<mesh> modelManager::getMeshVector();
	std::vector<model> modelManager::getMOdelVector();
	
	

	~modelManager();
};
