/*****************************************************************************/
/*!
\file
\author
\par email:
\par DigiPen login:
\par Course: cs260
\par Assignment 4
\date

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/*****************************************************************************/

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