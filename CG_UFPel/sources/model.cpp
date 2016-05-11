#include "model.hpp"
#include <shader.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp> 
#include <mesh.hpp>

//programID loads the shader
//texture loads the texture as each obj has it's own
//meshID links the mesh to the model

model::model( GLuint programID, const char * texture,  const char * myTextureSampler, mesh mesh){

	malha = mesh;
	ModelMatrixID = glGetUniformLocation(programID, "M");

	// Load the texture
	//Texture = loadDDS("mesh/uvmap.DDS");
	Texture = loadDDS(texture);
	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);

	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(TextureID, 0);
	// Get a handle for our "myTextureSampler" uniform
	TextureID = glGetUniformLocation(programID, myTextureSampler);
	// matriz para aplicar as tranformações, atualmente com a matriz identidade
	ModelMatrix = glm::mat4(1.0);
	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	
}

void model::startTexture() {
	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);

	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(TextureID, 0);
}

void model::setTransformation() {
	// rotação ok
	//ModelMatrix = glm::rotate(glm::mat4(1.0), glm::degrees(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//translação ok
	//ModelMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, 0.0f));
	// escala ok
	//ModelMatrix = glm::scale(2.0f, 2.0f, 2.0f);
	//ModelMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0), glm::degrees(45.0f), glm::vec3(0.0f, 0.0f, 0.0f))*glm::scale(2.0f, 2.0f, 2.0f);
}

void model::drawModels() {

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,        // mode
		malha.getIndices().size(), // count
		GL_UNSIGNED_SHORT,   // type
		(void*)0             // element array buffer offset
	);
}

glm::mat4 model::getModelMatrix(){
		return ModelMatrix;
}

GLuint model::getModelMatrixID(){
		return ModelMatrixID;
}

GLuint model::getTexture(){
		return Texture;
}

GLuint model::getTextureID(){
		return TextureID;
}

GLuint model::getMeshIndex(){
	return meshIndex;
}

model::~model(){
	  glDeleteTextures(1, &Texture);
}

