// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* g_pWindow;
unsigned int g_nWidth = 1024, g_nHeight = 768;

// Include AntTweakBar
#include <AntTweakBar.h>
TwBar *g_pToolBar;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <shader.hpp>
#include <texture.hpp>
#include <controls.hpp>
#include <objloader.hpp>
#include <vboindexer.hpp>
#include <glerror.hpp>

#include <block.hpp>
GLuint g_quad_vertexbuffer;
void drawBlock();
void lBlock();
void tBlock();
void iBlock();
void sBlock();

void WindowSizeCallBack(GLFWwindow *pWindow, int nWidth, int nHeight) {

	g_nWidth = nWidth;
	g_nHeight = nHeight;
	glViewport(0, 0, g_nWidth, g_nHeight);
	TwWindowSize(g_nWidth, g_nHeight);
}

int main(void)
{
	int nUseMouse = 0;

	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	g_pWindow = glfwCreateWindow(g_nWidth, g_nHeight, "CG UFPel", NULL, NULL);
	if (g_pWindow == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(g_pWindow);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	check_gl_error();//OpenGL error from GLEW

					 // Initialize the GUI
	TwInit(TW_OPENGL_CORE, NULL);
	TwWindowSize(g_nWidth, g_nHeight);

	// Set GLFW event callbacks. I removed glfwSetWindowSizeCallback for conciseness
	glfwSetMouseButtonCallback(g_pWindow, (GLFWmousebuttonfun)TwEventMouseButtonGLFW); // - Directly redirect GLFW mouse button events to AntTweakBar
	glfwSetCursorPosCallback(g_pWindow, (GLFWcursorposfun)TwEventMousePosGLFW);          // - Directly redirect GLFW mouse position events to AntTweakBar
	glfwSetScrollCallback(g_pWindow, (GLFWscrollfun)TwEventMouseWheelGLFW);    // - Directly redirect GLFW mouse wheel events to AntTweakBar
	glfwSetKeyCallback(g_pWindow, (GLFWkeyfun)TwEventKeyGLFW);                         // - Directly redirect GLFW key events to AntTweakBar
	glfwSetCharCallback(g_pWindow, (GLFWcharfun)TwEventCharGLFW);                      // - Directly redirect GLFW char events to AntTweakBar
	glfwSetWindowSizeCallback(g_pWindow, WindowSizeCallBack);

	//create the toolbar
	g_pToolBar = TwNewBar("CG UFPel ToolBar");
	// Add 'speed' to 'bar': it is a modifable (RW) variable of type TW_TYPE_DOUBLE. Its key shortcuts are [s] and [S].
	double speed = 0.0;
	TwAddVarRW(g_pToolBar, "speed", TW_TYPE_DOUBLE, &speed, " label='Rot speed' min=0 max=2 step=0.01 keyIncr=s keyDecr=S help='Rotation speed (turns/second)' ");
	// Add 'bgColor' to 'bar': it is a modifable variable of type TW_TYPE_COLOR3F (3 floats color)
	vec3 oColor(0.0f);
	TwAddVarRW(g_pToolBar, "bgColor", TW_TYPE_COLOR3F, &oColor[0], " label='Background color' ");

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(g_pWindow, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetCursorPos(g_pWindow, g_nWidth / 2, g_nHeight / 2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glDisable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("shaders/StandardShading.vertexshader", "shaders/StandardShading.fragmentshader");

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(programID, "M");

	// Load the texture
	GLuint Texture = loadDDS("mesh/uvmap.DDS");

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");


	// Get a handle for our "LightPosition" uniform
	glUseProgram(programID);
	GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	// For speed computation
	double lastTime = glfwGetTime();
	int nbFrames = 0;
	//glCullFace(GL_FRONT_AND_BACK);
	//lBlock();
	//tBlock();
	//iBlock();
	sBlock();

	do {
		check_gl_error();

		//use the control key to free the mouse
		if (glfwGetKey(g_pWindow, GLFW_KEY_LEFT_CONTROL) != GLFW_PRESS)
			nUseMouse = 0;
		else
			nUseMouse = 1;

		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1sec ago
											 // printf and reset
			printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs(nUseMouse, g_nWidth, g_nHeight);
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = 
			glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		// Send our transformation to the currently bound shader,
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

		glm::vec3 lightPos = glm::vec3(4, 4, 4);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);
		
		drawBlock();

		// Draw tweak bars
		TwDraw();

		// Swap buffers
		glfwSwapBuffers(g_pWindow);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(g_pWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(g_pWindow) == 0);

	// Cleanup VBO and shader
	/*glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteBuffers(1, &elementbuffer);*/
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Terminate AntTweakBar and GLFW
	TwTerminate();
	glfwTerminate();

	return 0;
}
void lBlock() {
	// The fullscreen quad's FBO
	static const GLfloat g_quad_vertex_buffer_data[] = {

		-3.0f, -1.0f, 0.0f,//E
		-1.0f, -1.0f, 0.0f,//A
		-3.0f,  1.0f, 0.0f,//F
		-3.0f,  1.0f, 0.0f,//F
		-1.0f, -1.0f, 0.0f,//A
		-1.0f,  1.0f, 0.0f,//C

		-1.0f, -1.0f, 0.0f,//A
		 1.0f, -1.0f, 0.0f,//B
		-1.0f,  1.0f, 0.0f,//C
		-1.0f,  1.0f, 0.0f,//C
		 1.0f, -1.0f, 0.0f,//B
		 1.0f,  1.0f, 0.0f,//D

		 1.0f, -1.0f, 0.0f,//B
		 3.0f, -1.0f, 0.0f,//G
		 1.0f,  1.0f, 0.0f,//D
		 1.0f,  1.0f, 0.0f,//D
		 3.0f, -1.0f, 0.0f,//G
		 3.0f,  1.0f, 0.0f,//H

		 1.0f,  1.0f, 0.0f,//D
		 3.0f,  1.0f, 0.0f,//H
		 1.0f,  3.0f, 0.0f,//I
		 1.0f,  3.0f, 0.0f,//I
		 3.0f,  1.0f, 0.0f,//H
		 3.0f,  3.0f, 0.0f,//J

	};

	glGenBuffers(1, &g_quad_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, g_quad_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);
}
void tBlock() {
	// The fullscreen quad's FBO
	static const GLfloat g_quad_vertex_buffer_data[] = {

		-3.0f, -1.0f, 0.0f,//E
		-1.0f, -1.0f, 0.0f,//A
		-3.0f,  1.0f, 0.0f,//F
		-3.0f,  1.0f, 0.0f,//F
		-1.0f, -1.0f, 0.0f,//A
		-1.0f,  1.0f, 0.0f,//C

		-1.0f, -1.0f, 0.0f,//A
		 1.0f, -1.0f, 0.0f,//B
		-1.0f,  1.0f, 0.0f,//C
		-1.0f,  1.0f, 0.0f,//C
		 1.0f, -1.0f, 0.0f,//B
		 1.0f,  1.0f, 0.0f,//D

		 1.0f, -1.0f, 0.0f,//B
		 3.0f, -1.0f, 0.0f,//G
		 1.0f,  1.0f, 0.0f,//D
		 1.0f,  1.0f, 0.0f,//D
		 3.0f, -1.0f, 0.0f,//G
		 3.0f,  1.0f, 0.0f,//H

		-1.0f,  1.0f, 0.0f,//C
		 1.0f,  1.0f, 0.0f,//D
		-1.0f,  3.0f, 0.0f,//K
		-1.0f,  3.0f, 0.0f,//K
		 1.0f,  1.0f, 0.0f,//D
		 1.0f,  3.0f, 0.0f,//I

	};

	glGenBuffers(1, &g_quad_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, g_quad_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);
}
void iBlock() {
	// The fullscreen quad's FBO
	static const GLfloat g_quad_vertex_buffer_data[] = {

		-3.0f, -1.0f, 0.0f,//E
		-1.0f, -1.0f, 0.0f,//A
		-3.0f,  1.0f, 0.0f,//F
		-3.0f,  1.0f, 0.0f,//F
		-1.0f, -1.0f, 0.0f,//A
		-1.0f,  1.0f, 0.0f,//C

		-1.0f, -1.0f, 0.0f,//A
		 1.0f, -1.0f, 0.0f,//B
		-1.0f,  1.0f, 0.0f,//C
		-1.0f,  1.0f, 0.0f,//C
		 1.0f, -1.0f, 0.0f,//B
		 1.0f,  1.0f, 0.0f,//D

		 1.0f, -1.0f, 0.0f,//B
		 3.0f, -1.0f, 0.0f,//G
		 1.0f,  1.0f, 0.0f,//D
		 1.0f,  1.0f, 0.0f,//D
		 3.0f, -1.0f, 0.0f,//G
		 3.0f,  1.0f, 0.0f,//H

	};

	glGenBuffers(1, &g_quad_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, g_quad_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);
}
void sBlock() {
	// The fullscreen quad's FBO
	static const GLfloat g_quad_vertex_buffer_data[] = {

		-3.0f, -1.0f, 0.0f,//E
		-1.0f, -1.0f, 0.0f,//A
		-3.0f,  1.0f, 0.0f,//F
		-3.0f,  1.0f, 0.0f,//F
		-1.0f, -1.0f, 0.0f,//A
		-1.0f,  1.0f, 0.0f,//C

		-1.0f, -1.0f, 0.0f,//A
		 1.0f, -1.0f, 0.0f,//B
		-1.0f,  1.0f, 0.0f,//C
		-1.0f,  1.0f, 0.0f,//C
		 1.0f, -1.0f, 0.0f,//B
		 1.0f,  1.0f, 0.0f,//D

		-1.0f,  1.0f, 0.0f,//C
		 1.0f,  1.0f, 0.0f,//D
		-1.0f,  3.0f, 0.0f,//K
		-1.0f,  3.0f, 0.0f,//K
		 1.0f,  1.0f, 0.0f,//D
		 1.0f,  3.0f, 0.0f,//I

		 1.0f,  1.0f, 0.0f,//D
		 3.0f,  1.0f, 0.0f,//H
		 1.0f,  3.0f, 0.0f,//I
		 1.0f,  3.0f, 0.0f,//I
		 3.0f,  1.0f, 0.0f,//H
		 3.0f,  3.0f, 0.0f,//J

	};

	glGenBuffers(1, &g_quad_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, g_quad_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);
}

void drawBlock() {

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, g_quad_vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, 24); // 8*3 indices starting at 0 -> 2 triangles

	glDisableVertexAttribArray(0);
}
//tretas