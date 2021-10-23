/******************************************************************************/
/*!
\file Mesh.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

#ifndef MESH_H
#define MESH_H

#include<GL\glew.h>
#include <vector>
#include <glm.hpp>
class Mesh
{
public:
	Mesh();

	void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned numOfIndices);
	void CreateNormalMesh(std::vector<glm::vec3>* vertices);
	void RenderMesh();
	void RenderNormal(int count);
	void ClearMesh();

	~Mesh();

private:

	GLuint VBO, VAO, IBO;
	GLuint VBO_N, VAO_N, IBO_N;
	GLsizei indexCount;

};

#endif