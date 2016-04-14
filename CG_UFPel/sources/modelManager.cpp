#include "modelManager.hpp"



modelMenager::modelMenager()
{
	// matrix settings
	GLuint VertexArrayID;

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID, "V");

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	glDeleteVertexArrays(1, &VertexArrayID);
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

}


modelMenager::~modelMenager()
{
}
