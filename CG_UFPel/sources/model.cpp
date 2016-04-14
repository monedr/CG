#include "model.hpp"


//programID loads the shader
//texture loads the texture as each obj has it's own
//meshID links the mesh to the model
model::model( GLuint programID, const char * texture,  const char * myTextureSampler, GLuint meshID){

	meshIndex = meshID;
	
	ModelMatrixID = glGetUniformLocation(programID, "M");

	// Load the texture
	//Texture = loadDDS("mesh/uvmap.DDS");
	Texture = loadDDS(texture);

	// Get a handle for our "myTextureSampler" uniform
	TextureID = glGetUniformLocation(programID, myTextureSampler);
	TextureID = glGetUniformLocation(programID, texture);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);

	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(TextureID, 0);

  // matriz para aplicar as tranformações, atualmente com a matriz identidade
	ModelMatrix = glm::mat4(1.0);

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

}

glm::mat4 model::getModelMatrix(){
		return ModelMatrix;
}

GLunint model::getModelMatrixID(){
		return ModelMatrixID;
}

GLunint model::getTexture(){
		return Texture;
}

GLunint model::getTextureID(){
		return TextureID;
}

GLunint model::getMeshIndex(){}

model::~model(){
	   glDeleteTextures(1, &Texture);
}
