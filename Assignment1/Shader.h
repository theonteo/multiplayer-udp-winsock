/******************************************************************************/
/*!
\file Shader.h
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
This file contains the declarations of the shader class used by the graphics
engine.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

#ifndef SHADER_H
#define SHADER_H
#include <CommonValues.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <DirectionalLight.h>
#include <PointLight.h>
#include <SpotLight.h>

#include <GL\glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	std::string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetDiffuseLocation();
	GLuint GetViewLocation();
	GLuint GetAmbientIntensityLocation();
	GLuint GetAmbientColourLocation();
	GLuint GetDiffuseIntensityLocation();
	GLuint GetDirectionLocation();
	GLuint GetColourLocation();
	GLuint GetSpecularIntensityLocation();
	GLuint GetShininessLocation();
	GLuint GetEyePositionLocation();

	void SetDirectionalLight(DirectionalLight* dLight);
	void SetPointLight(PointLight* pLight,unsigned int lightCount);
	void SetSpotLight(SpotLight* sLight, unsigned int lightCount);
	void SetTexture(GLuint textureUnit);
	void SetTextureNormal(GLuint textureUnit);
	void SetTextureCubeMap(GLuint textureUnit);
	void SetDirectionalShadowMap(GLuint textureUnit);
	void SetDirectionalLighttransform(glm::mat4 lTransform);
	void SetScreenTexture(GLuint textureUnit);
	void UseShader();
	void ClearShader();

	~Shader();

	std::string shaderName;
	GLuint shaderID;

private:

	int pointLightCount;
	int spotLightCount;
	GLuint uniformProjection, uniformModel,uniformView,
		uniformEyePosition,uniformSpecularIntensity,
		uniformShininess,uniformDirectionalLightTransform,
		uniformDirectionalShadowMap,uniformTexture;
	GLuint uniformTextureNormal;
	GLuint uniformTextureSpecular;
	GLuint uniformTextureCubeMap;
	GLuint uniformScreenTexture;

	GLuint uniformColour;


	struct {
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformDirection;


	}uniformDirectionalLight;

	GLuint uniformPointLightCount;
	GLuint uniformSpotLightCount;
	struct {
		GLuint uniformExponent;
		GLuint uniformLinear;
		GLuint uniformConstant;
		GLuint uniformPosition;
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;
		GLuint uniformDirection;

	}uniformPointLight[MAX_POINT_LIGHTS];

	struct {
		GLuint uniformExponent;
		GLuint uniformLinear;
		GLuint uniformConstant;
		GLuint uniformPosition;
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformDirection;
		GLuint uniformEdge;


	}uniformSpotLight[MAX_SPOT_LIGHTS];

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

#endif
