#include "model.hpp"
#include <shader.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp> 
#include <mesh.hpp>


model::model(const char * vertexshader, const char * fragmentshader, const char *texture, const char *textureSampler, mesh outraMalha){

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders(vertexshader, fragmentshader);

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");
	ViewMatrixID = glGetUniformLocation(programID, "V");
	ModelMatrixID = glGetUniformLocation(programID, "M");

	// Load the texture
	Texture = loadDDS(texture);

	// Get a handle for our "myTextureSampler" uniform
	TextureID = glGetUniformLocation(programID, textureSampler);

	malha = outraMalha;

}

mesh model::getMesh(){

	return malha;
}

GLuint model::getProgramID(){
	
	return programID;
}

GLuint model::getMatrixID(){
	
	return MatrixID;
}

GLuint model::getViewMatrixID(){

	return ViewMatrixID;
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

model::~model(){

}

