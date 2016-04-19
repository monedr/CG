#include "modelManager.hpp"
#include <shader.hpp>
#include <controls.hpp>


modelManager::modelManager(char * vertexshader, char * fragmentshader)
{
	// Create and compile our GLSL program from the shaders
	// LoadShaders("shaders/StandardShading.vertexshader", "shaders/StandardShading.fragmentshader");
	programID = LoadShaders(vertexshader, fragmentshader);

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");
	ViewMatrixID = glGetUniformLocation(programID, "V");

}

void modelManager::loadMesh(char * path) {

	//carrega a malha no vetor de malhas
	mesh mesh(path);
	meshVector.push_back(mesh);
}
void modelManager::creatModel( char* texture, char* myTextureSampler) {
	model auxModel(programID, texture, myTextureSampler, meshVector.size() - 1);
	modelVector.push_back(auxModel);
}

void modelManager::calcMVP(model model) {

	// Compute the MVP matrix from keyboard and mouse input

	ProjectionMatrix = getProjectionMatrix();
	ViewMatrix = getViewMatrix();
	MVP = ProjectionMatrix * ViewMatrix * model.getModelMatrix();
}

void modelManager::setMatrixToGPU(model model) {
	
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(model.getModelMatrixID(), 1, GL_FALSE, &model.getModelMatrix()[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
}

void modelManager::setLightPosition(char * LightPosition_worldspace) {
	// Get a handle for our "LightPosition" uniform
	glUseProgram(programID);
	LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

}
void modelManager::drawModels(mesh mesh) {

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,        // mode
		mesh.getIndices().size(), // count
		GL_UNSIGNED_SHORT,   // type
		(void*)0             // element array buffer offset
	);
}

GLuint modelManager::getLightID() {
		return LightID;
}

GLuint modelManager::getProgramID(){
		return programID;
}

std::vector<mesh> modelManager::getMeshVector(){
		return meshVector;
}

std::vector<model> modelManager::getMOdelVector(){
		return modelVector;
}

GLuint modelManager::getMatrixID(){
		return MatrixID;
}

GLuint modelManager::getViewMatrixID(){
		return ViewMatrixID;
}

modelManager::~modelManager() {

	glDeleteProgram(programID);

}

