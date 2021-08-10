/******************************************************************************/
/*!
\file Mesh.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\par email: c.choo\@digipen.edu
\par email: kevin.hartono\@digipen.edu
\par email: zhengyongtheon.teo\@digipen.edu

\par DigiPen login: c.choo
\par DigiPen login: kevin.hartono
\par DigiPen login: zhengyongtheon.teo

\par Course: CS260-A
\par Assignment 4
\date 01/08/2021
\brief
This file contains the declarations of the mesh class used by the graphics
engine.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
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