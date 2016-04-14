#include "model.hpp"



model::model(){
  
  // Create and compile our GLSL program from the shaders
	// LoadShaders("shaders/StandardShading.vertexshader", "shaders/StandardShading.fragmentshader");
	programID = LoadShaders(vertexshader, fragmentshader);


	 ModelMatrixID = glGetUniformLocation(programID, "M");

	// Load the texture
	//Texture = loadDDS("mesh/uvmap.DDS");
	Texture = loadDDS(texture);

	// Get a handle for our "myTextureSampler" uniform
	//TextureID = glGetUniformLocation(programID, "myTextureSampler");
	TextureID = glGetUniformLocation(programID, texture);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(TextureID, 0);

	// Compute the MVP matrix from keyboard and mouse input
	//computeMatricesFromInputs(nUseMouse, g_nWidth, g_nHeight);
	glm::mat4 ProjectionMatrix = getProjectionMatrix();
	glm::mat4 ViewMatrix = getViewMatrix();
	glm::mat4 ModelMatrix = glm::mat4(1.0);


	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform

	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

}


model::~model()
{
}
