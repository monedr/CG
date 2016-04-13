#pragma once

#ifndef MESH_H
#define MESH_H

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>




// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include <shader.hpp>
#include <texture.hpp>
#include <controls.hpp>
#include <objloader.hpp>
#include <vboindexer.hpp>
#include <glerror.hpp>

class mesh
{
	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	
	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;
	
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint elementbuffer;

public:

	GLuint getVertexbuffer();
	GLuint getUvbuffer();
	GLuint getNormalbuffer();
	GLuint getElementbuffer();

	mesh();
	mesh(const char * path);
	~mesh();
};

#endif