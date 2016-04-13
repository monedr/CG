// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <shader.hpp>
#include <texture.hpp>
#include <controls.hpp>
#include <objloader.hpp>
#include <vboindexer.hpp>
#include <glerror.hpp>

Class meshClass{

	// Read our .obj file
std::vector<glm::vec3> vertices;
std::vector<glm::vec2> uvs;
std::vector<glm::vec3> normals;
bool res = loadOBJ("mesh/suzanne.obj", vertices, uvs, normals);

std::vector<unsigned short> indices;
std::vector<glm::vec3> indexed_vertices;
std::vector<glm::vec2> indexed_uvs;
std::vector<glm::vec3> indexed_normals;
indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);

}