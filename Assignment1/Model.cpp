/******************************************************************************/
/*!
\file Model.cpp
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
This file contains the definitions of the model class used by the graphics
engine.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

#include "Model.h"
#include <glm.hpp>
#include <fstream>
#include <sstream>
#include <algorithm>

/******************************************************************************/
/*!
\brief  render model
*/
/******************************************************************************/
void Model::RenderModel()
{
	for (int i = 0; i < meshList.size(); i++)
		meshList[i]->RenderMesh();
}

/******************************************************************************/
/*!
\brief render normals
*/
/******************************************************************************/
void Model::RenderNormals()
{
	for (int i = 0; i < meshList.size(); i++)
		meshList[i]->RenderNormal(static_cast<int>(allPos.size()));
}

/******************************************************************************/
/*!
\brief clear model
*/
/******************************************************************************/
void Model::ClearModel()
{
	for (int i = 0; i < meshList.size(); i++)
	{
		if (meshList[i])
		{

			delete meshList[i];
			meshList[i] = nullptr;
		}
	}
	allPos.clear();
	allNormal.clear();
	allTangent.clear();
	allBitangent.clear();

	allNormalPos.clear();
	allIndices.clear();
	allIndicesNormal.clear();
	allVerts.clear();
	meshList.clear();
}

/******************************************************************************/
/*!
\brief  load asset model
*/
/******************************************************************************/
void Model::LoadAssetModel(const std::string& model_name)
{
	std::ifstream ifs{ model_name, std::ios::in };
	if (!ifs)
	{
		std::cout << "ERROR: Unable to open model file: "
			<< model_name << "\n";
		exit(EXIT_FAILURE);
	}
	ifs.seekg(0, std::ios::beg);

	std::string line;
	int line_count = 0;
	int start_line = 0;

	while (getline(ifs, line))
	{

		std::string keyCode;
		std::string fullLine = line;
		std::istringstream line_sstm{ line };
		if (!line_sstm) continue;

		line_sstm >> keyCode;

		if (keyCode == "g")
			start_line = line_count;

		//vertice position
		if (keyCode == "v")
		{
			//vertices
			GLfloat x; GLfloat y; GLfloat z;
			line_sstm >> x;
			line_sstm >> y;
			line_sstm >> z;
			allPos.push_back(glm::vec3(x, y, z));
			continue;
		}
		if (keyCode == "vn")
		{
			//vertices
			GLfloat x; GLfloat y; GLfloat z;
			line_sstm >> x;
			line_sstm >> y;
			line_sstm >> z;
			allImportedNormal.push_back(glm::vec3(x, y, z));
			continue;
		}

		if (keyCode == "f")
		{
			std::string t;
			int slash = 0;
			//form triangle
			for (auto& i : fullLine)
			{
				if (i == '/')
				{
					slash++;
				}
				else if (i == ' ' || i == keyCode[0])
				{
					if (t != "")
					{
						allIndices.push_back(std::stoi(t));
						t.clear();
					}
				}
				else {
					if (slash == 0)
					{
						t += i;
					}
					else {
						allIndicesNormal.push_back(std::stoi(t));
						slash = 0;
					}
				}
			}
			if (t != "")
			{
				allIndices.push_back(std::stoi(t));
				t.clear();
			}
			continue;
		}

		line_count++;
		line.clear();
		keyCode = ' ';

	}

	for (auto& i : allIndices)
		i = i - 1;

	for (auto& i : allIndicesNormal)
		i = i - 1;
	bool check = false;

	while (!check)
	{
		for (auto& i : allIndices)
		{
			if (i == 0)check = true;
		}
		if (!check)
		{
			for (auto& i : allIndices)
			{
				i = i - 1;
			}
		}
	}
	if (allIndicesNormal.size() > 0)
	{
		check = false;
		while (!check)
		{
			for (auto& i : allIndicesNormal)
			{
				if (i == 0)check = true;
			}
			if (!check)
			{
				for (auto& i : allIndicesNormal)
				{
					i = i - 1;
				}
			}
		}
	}
	ReshapeModel();

	Mesh* newMesh = new Mesh();
	mesh = newMesh;

	computeNormals();
	for (size_t i = 0; i < allPos.size(); ++i)
	{
		allVerts.insert(allVerts.end(),
			{
						allPos[i].x,
						allPos[i].y,
						allPos[i].z,
						0,0,0,
						-allNormal[i].x,
						-allNormal[i].y,
						-allNormal[i].z,
						0,0,0,0,0,0
			});
	}




	newMesh->CreateMesh(&allVerts[0], &allIndices[0], 
		static_cast<int>(allVerts.size()), static_cast<int>(allIndices.size()));

	meshList.push_back(newMesh);

}

/******************************************************************************/
/*!
\brief reshape model
*/
/******************************************************************************/
void Model::ReshapeModel()
{
	//set up variables
	glm::vec3 totalVertPos{ 0 };
	glm::vec3 center{ 0 };

	glm::vec3 vertMinX{ allPos[0] };
	glm::vec3 vertMaxX{ allPos[0] };
	glm::vec3 vertMinY{ allPos[0] };
	glm::vec3 vertMaxY{ allPos[0] };
	glm::vec3 vertMinZ{ allPos[0] };
	glm::vec3 vertMaxZ{ allPos[0] };

	//calculate min max of all axis
	for (const auto& i : allPos)
	{
		totalVertPos += i;

		if (i.x < vertMinX.x)vertMinX = i;
		if (i.x > vertMaxX.x)vertMaxX = i;
		if (i.y < vertMinY.y)vertMinY = i;
		if (i.y > vertMaxY.y)vertMaxY = i;
		if (i.z < vertMinZ.z)vertMinZ = i;
		if (i.z > vertMaxZ.z)vertMaxZ = i;
	}
	glm::vec3 unit =
		glm::vec3((vertMaxX.x - vertMinX.x), (vertMaxY.y - vertMinY.y),
			(vertMaxZ.z - vertMinZ.z));

	//calculate new center
	center.x = totalVertPos.x / allPos.size();
	center.y = totalVertPos.y / allPos.size();
	center.z = totalVertPos.z / allPos.size();

	// Offset object to center
	for (auto& i : allPos)
		i -= center;

	// Resize object to (1, 1, 1)
	GLfloat maxUnit = std::max({ unit.x,unit.y,unit.z });
	for (auto& i : allPos)
	{
		i.x /= maxUnit;
		i.y /= maxUnit;
		i.z /= maxUnit;
	}

}

/******************************************************************************/
/*!
\brief  generate normals
*/
/******************************************************************************/
glm::vec3 Model::generateNormals(int index)
{
	glm::vec3 v1 = allPos[allIndices[index * 3]];
	glm::vec3 v2 = allPos[allIndices[index * 3 + 1]];
	glm::vec3 v3 = allPos[allIndices[index * 3 + 2]];
	glm::vec3  N = glm::cross(v2 - v1, v3 - v1);

	float sin_alpha = length(N) / (length(v2 - v1) * length(v3 - v1));
	return normalize(N) * asin(sin_alpha);
}

/******************************************************************************/
/*!
\brief  face contain vertex
*/
/******************************************************************************/
bool Model::FaceContainVertex(int face, int vertex) const
{

	if (allIndices[face * 3] ==(unsigned int) vertex ||
		allIndices[face * 3 + 1] == (unsigned int)vertex ||
		allIndices[face * 3 + 2] == (unsigned int)vertex)
		return true;

	return false;
}

/******************************************************************************/
/*!
\brief  compute normals
*/
/******************************************************************************/
void Model::computeNormals()
{
	allNormal.resize(allPos.size());

	for (int v = 0; v < allPos.size(); ++v)
	{
		glm::vec3 N(0, 0, 0);
		for (int i = 0; i < allIndices.size() / 3; ++i)
		{
			if (FaceContainVertex(i, v))
				N = N + generateNormals(i);
		}
		allNormal[v] = normalize(N);
	}

	for (size_t v = 0; v < allPos.size(); ++v)
	{
		allNormalPos.push_back(allPos[v]);
		allNormalPos.push_back(allPos[v] + (allNormal[v]) * 0.055f);

	}
	mesh->CreateNormalMesh(&allNormalPos);
}


