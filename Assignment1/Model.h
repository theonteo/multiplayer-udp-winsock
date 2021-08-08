/******************************************************************************/
/*!
\file Model.h
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
This file contains the declarations of the model class used by the graphics
engine.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>

#include <Mesh.h>
#include <Texture.h>
#include <glm.hpp>


class Model
{
public:
	std::string ModelName;
	void LoadAssetModel(const std::string& text);
	void RenderModel();
	void RenderNormals();
	void ClearModel();
	void ReshapeModel();

	Model() = default;

private:
	Mesh* mesh;
	glm::vec3 generateNormals(int index);

	void computeNormals();
	bool FaceContainVertex(int face,int vertex) const;

	std::vector<glm::vec3> allPos;
	std::vector<glm::vec3> allNormal;
	std::vector<glm::vec3> allImportedNormal;
	std::vector<glm::vec3> allTangent;
	std::vector<glm::vec3> allBitangent;


	std::vector<glm::vec3> allNormalPos;
	std::vector<unsigned int> allIndices;
	std::vector<unsigned int> allIndicesNormal;
	std::vector<GLfloat> allVerts;
	std::vector<Mesh*> meshList;
};

#endif