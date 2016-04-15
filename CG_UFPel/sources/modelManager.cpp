#include "modelManager.hpp"



modelManager::modelManager(const char * vertexshader, const char * fragmentshader, const char * texture, const char * myTextureSampler, const char * objPath )
{
	//carrega a malha no vetor de malhas
	mesh auxMesh(objPath);
	meshVector.push_back(auxMesh);

	// Create and compile our GLSL program from the shaders
	// LoadShaders("shaders/StandardShading.vertexshader", "shaders/StandardShading.fragmentshader");
	programID = LoadShaders(vertexshader, fragmentshader);

	//cria um modelo o associa a uma malha e o insere no vetor de modelos
	model auxModel(programID, texture, myTextureSampler, meshVector.size() - 1);
	modelVector.push_back(auxModel);

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");
	ViewMatrixID = glGetUniformLocation(programID, "V");

	// Compute the MVP matrix from keyboard and mouse input
	//computeMatricesFromInputs(nUseMouse, g_nWidth, g_nHeight);
	ProjectionMatrix = getProjectionMatrix();
	ViewMatrix = getViewMatrix();
	ModelMatrix = modelVector[0].getModelMatrix();
	MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
	
	
}

GLuint modelManager::getProgramID(){
		return programID;
}

//void modelManager::

void modelManager::drawModels() {
	GLuint m;
	m = modelVector[0].getMeshIndex();
	//std::vector<unsigned short> indices;
	printf("tamanho de indices: % d\n", meshVector[m].getIndices().size());
	//meshVector[m].getIndices().size()indices.size()
	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,        // mode
		meshVector[m].getIndices().size(), // count
		GL_UNSIGNED_SHORT,   // type
		(void*)0             // element array buffer offset
	);

}
modelManager::modelManager(){}
modelManager::~modelManager() {

	glDeleteProgram(programID);

}

