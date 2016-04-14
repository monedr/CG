#include "modelManager.hpp"



modelManager::modelManager(const char * vertexshader, const char * fragmentshader, const char * texture, const char * myTextureSampler, const char * objPath )
{
	meshVector.push_back(objPath);
	modelVector.push_back(programID, texture, myTextureSampler, meshVector.size());

	// Create and compile our GLSL program from the shaders
	// LoadShaders("shaders/StandardShading.vertexshader", "shaders/StandardShading.fragmentshader");
	programID = LoadShaders(vertexshader, fragmentshader);

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");
	ViewMatrixID = glGetUniformLocation(programID, "V");

	// Compute the MVP matrix from keyboard and mouse input
	//computeMatricesFromInputs(nUseMouse, g_nWidth, g_nHeight);
	ProjectionMatrix = getProjectionMatrix();
	ViewMatrix = getViewMatrix();

	MVP = ProjectionMatrix * ViewMatrix * modelVector.ModelMatrix;
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
	*/
	
}

GLuint modelManager::getProgramID(){
		return programID;
}
modelManager::~modelManager() {

	glDeleteProgram(programID);

}

