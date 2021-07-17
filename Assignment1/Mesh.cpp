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

#include "Mesh.h"
#include <glm.hpp>

/******************************************************************************/
/*!
\brief  constructor
*/
/******************************************************************************/
Mesh::Mesh()
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;
}
/******************************************************************************/
/*!
\brief  create mesh
*/
/******************************************************************************/
void Mesh::CreateMesh(GLfloat* vertices, unsigned int* indices,
	unsigned int numOfVertices, unsigned numOfIndices) 
{
	indexCount = numOfIndices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);


	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

	//position
	glVertexAttribPointer
	(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 15, 0);
	glEnableVertexAttribArray(0);

	//reserve - wip
	glVertexAttribPointer
	(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 15, (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);

	//normals
	glVertexAttribPointer
	(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 15, (void*)(sizeof(vertices[0]) * 6));
	glEnableVertexAttribArray(2);

	//tangent - wip
	glVertexAttribPointer
	(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 15, (void*)(sizeof(vertices[0]) * 9));
	glEnableVertexAttribArray(3);

	//bitangent - wip
	glVertexAttribPointer
	(4, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 15, (void*)(sizeof(vertices[0]) * 12));
	glEnableVertexAttribArray(4);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

/******************************************************************************/
/*!
\brief  create normal mesh
*/
/******************************************************************************/
void Mesh::CreateNormalMesh(std::vector<glm::vec3>* vertices)
{


	//set up vbo/bao
	glCreateBuffers(1, &VBO_N);
	glNamedBufferStorage(VBO_N, sizeof(glm::vec3) * vertices->size(),
		vertices->data(), GL_DYNAMIC_STORAGE_BIT);

	glCreateVertexArrays(1, &VAO_N);
	glEnableVertexArrayAttrib(VAO_N, 0);
	glVertexArrayVertexBuffer(VAO_N, 0, VBO_N, 0, sizeof(glm::vec3));
	glVertexArrayAttribFormat(VAO_N, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(VAO_N, 0, 0);
	glBindVertexArray(0);

}

/******************************************************************************/
/*!
\brief render normals
*/
/******************************************************************************/
void Mesh::RenderNormal(int count)
{

	glBindVertexArray(VAO_N);
	glLineWidth(10.f);
	glVertexAttrib3f(1, 0.f, 0.f, 1.f); // blue color for lines
	glDrawArrays(GL_LINES, 0, count * 2);
	glBindVertexArray(0);
}

/******************************************************************************/
/*!
\brief render mesh
*/
/******************************************************************************/
void Mesh::RenderMesh() 
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

/******************************************************************************/
/*!
\brief  clear mesh
*/
/******************************************************************************/
void Mesh::ClearMesh()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}
	if (VBO != 0) 
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}
	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}
	indexCount = 0;
}

/******************************************************************************/
/*!
\brief  destructor
*/
/******************************************************************************/
Mesh::~Mesh()
{
	ClearMesh();
}
