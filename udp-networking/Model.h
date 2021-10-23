/******************************************************************************/
/*!
\file Model.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

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