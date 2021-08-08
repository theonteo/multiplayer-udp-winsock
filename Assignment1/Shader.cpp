/******************************************************************************/
/*!
\file Shader.cpp
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
This file contains the definitions of the shader class used by the graphics
engine.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

#include "Shader.h"

Shader::Shader()
{
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;

	pointLightCount = 0;
	spotLightCount = 0;
}

/******************************************************************************/
/*!
\brief  create from string
*/
/******************************************************************************/
void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode)
{
	CompileShader(vertexCode, fragmentCode);
}

/******************************************************************************/
/*!
\brief  create file
*/
/******************************************************************************/
void Shader::CreateFromFiles
(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexString = ReadFile(vertexLocation);
	std::string fragmentString = ReadFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	CompileShader(vertexCode, fragmentCode);
}

/******************************************************************************/
/*!
\brief read file
*/
/******************************************************************************/
std::string Shader::ReadFile(const char* fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open())
	{
		printf("Failed to read %s! File doesn't exist.", fileLocation);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}
/******************************************************************************/
/*!
\brief  compile shader
*/
/******************************************************************************/
void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();

	if (!shaderID)
	{
		printf("Error creating shader program!\n");
		return;
	}

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformView = glGetUniformLocation(shaderID, "view");

	uniformDirectionalLight.uniformColour =
		glGetUniformLocation(shaderID, "directionalLight.base.colour");
	uniformDirectionalLight.uniformAmbientIntensity =
		glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
	uniformDirectionalLight.uniformDirection = 
		glGetUniformLocation(shaderID, "directionalLight.direction");
	uniformDirectionalLight.uniformDiffuseIntensity =
		glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");

	uniformColour = glGetUniformLocation(shaderID, "diffuseColour");
	uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
	uniformShininess = glGetUniformLocation(shaderID, "material.shininess");
	uniformEyePosition = glGetUniformLocation(shaderID, "eyePosition");

	uniformPointLightCount = glGetUniformLocation(shaderID, "pointLightCount");

	for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		char locBuff[100] = { '\0' };

		snprintf(locBuff, (int)sizeof(locBuff), "pointLights[%d].base.colour", (int)i);
		uniformPointLight[i].uniformColour = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, (int)sizeof(locBuff), "pointLights[%d].base.ambientIntensity", (int)i);
		uniformPointLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, (int)sizeof(locBuff), "pointLights[%d].base.diffuseIntensity", (int)i);
		uniformPointLight[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, (int)sizeof(locBuff), "pointLights[%d].position", (int)i);
		uniformPointLight[i].uniformPosition = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, (int)sizeof(locBuff), "pointLights[%d].constant", (int)i);
		uniformPointLight[i].uniformConstant = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, (int)sizeof(locBuff), "pointLights[%d].linear", (int)i);
		uniformPointLight[i].uniformLinear = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, (int)sizeof(locBuff), "pointLights[%d].exponent", (int)i);
		uniformPointLight[i].uniformExponent = glGetUniformLocation(shaderID, locBuff);
	}

	uniformSpotLightCount = glGetUniformLocation(shaderID, "spotLightCount");

	for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
		char locBuff[100] = { '\0' };

		snprintf(locBuff, (int)sizeof(locBuff), "spotLights[%d].base.base.colour", (int)i);
		uniformSpotLight[i].uniformColour = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, (int)sizeof(locBuff), "spotLights[%d].base.base.ambientIntensity", (int)i);
		uniformSpotLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, (int)sizeof(locBuff), "spotLights[%d].base.base.diffuseIntensity", (int)i);
		uniformSpotLight[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, (int)sizeof(locBuff), "spotLights[%d].base.position", (int)i);
		uniformSpotLight[i].uniformPosition = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, (int)sizeof(locBuff), "spotLights[%d].base.constant", (int)i);
		uniformSpotLight[i].uniformConstant = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, (int)sizeof(locBuff), "spotLights[%d].base.linear", (int)i);
		uniformSpotLight[i].uniformLinear = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, (int)sizeof(locBuff), "spotLights[%d].base.exponent", (int)i);
		uniformSpotLight[i].uniformExponent = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, (int)sizeof(locBuff), "spotLights[%d].direction", (int)i);
		uniformSpotLight[i].uniformDirection = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, (int)sizeof(locBuff), "spotLights[%d].edge", (int)i);
		uniformSpotLight[i].uniformEdge = glGetUniformLocation(shaderID, locBuff);
	}

	uniformDirectionalLightTransform = glGetUniformLocation(shaderID, "directionalLightTransform");
	uniformTexture = glGetUniformLocation(shaderID, "theTexture");

	uniformTextureNormal = glGetUniformLocation(shaderID, "theTextureNormal");
	uniformTextureSpecular = glGetUniformLocation(shaderID, "theTextureSpecular");
	uniformTextureCubeMap = glGetUniformLocation(shaderID, "theTextureCubeMap");
	uniformScreenTexture= glGetUniformLocation(shaderID, "screenTexture");
	uniformDirectionalShadowMap = glGetUniformLocation(shaderID, "directionalShadowMap");
}

/******************************************************************************/
/*!
\brief  get projection location
*/
/******************************************************************************/
GLuint Shader::GetProjectionLocation()
{
	return uniformProjection;
}
/******************************************************************************/
/*!
\brief  get model location
*/
/******************************************************************************/
GLuint Shader::GetModelLocation()
{
	return uniformModel;
}

GLuint Shader::GetDiffuseLocation()
{
	return uniformTexture;
}

/******************************************************************************/
/*!
\brief  get view location
*/
/******************************************************************************/
GLuint Shader::GetViewLocation()
{
	return uniformView;
}

/******************************************************************************/
/*!
\brief  get ambient colour location
*/
/******************************************************************************/
GLuint Shader::GetAmbientColourLocation()
{
	return uniformDirectionalLight.uniformColour;
}

/******************************************************************************/
/*!
\brief  get ambient intensity location
*/
/******************************************************************************/
GLuint Shader::GetAmbientIntensityLocation()
{
	return uniformDirectionalLight.uniformAmbientIntensity;
}

/******************************************************************************/
/*!
\brief  get diffuse intensity location
*/
/******************************************************************************/
GLuint Shader::GetDiffuseIntensityLocation()
{
	return uniformDirectionalLight.uniformDiffuseIntensity;
}

/******************************************************************************/
/*!
\brief  get direction location
*/
/******************************************************************************/
GLuint Shader::GetDirectionLocation()
{
	return uniformDirectionalLight.uniformDirection;
}
/******************************************************************************/
/*!
\brief  get colour location
*/
/******************************************************************************/
GLuint Shader::GetColourLocation()
{
	return uniformColour;
}

/******************************************************************************/
/*!
\brief  get specular intensity location
*/
/******************************************************************************/
GLuint Shader::GetSpecularIntensityLocation()
{
	return uniformSpecularIntensity;
}

/******************************************************************************/
/*!
\brief  get shininess location
*/
/******************************************************************************/
GLuint Shader::GetShininessLocation()
{
	return uniformShininess;
}

/******************************************************************************/
/*!
\brief  get eye position location
*/
/******************************************************************************/
GLuint Shader::GetEyePositionLocation()
{
	return uniformEyePosition;
}

/******************************************************************************/
/*!
\brief  set directional light
*/
/******************************************************************************/
void Shader::SetDirectionalLight(DirectionalLight * dLight)
{
	dLight->UseLight(uniformDirectionalLight.uniformAmbientIntensity,
		uniformDirectionalLight.uniformColour,
		uniformDirectionalLight.uniformDiffuseIntensity,
		uniformDirectionalLight.uniformDirection);
}
/******************************************************************************/
/*!
\brief  set point light
*/
/******************************************************************************/
void Shader::SetPointLight(PointLight * pLight, unsigned int lightCount)
{
	if (lightCount > MAX_POINT_LIGHTS) lightCount = MAX_POINT_LIGHTS;

	glUniform1i(uniformPointLightCount, lightCount);

	for (size_t i = 0; i < lightCount; i++)
	{
		pLight[i].UseLight
		(uniformPointLight[i].uniformAmbientIntensity, uniformPointLight[i].uniformColour,
			uniformPointLight[i].uniformDiffuseIntensity, uniformPointLight[i].uniformPosition,
			uniformPointLight[i].uniformConstant, 
			uniformPointLight[i].uniformLinear, uniformPointLight[i].uniformExponent);
	}
}
/******************************************************************************/
/*!
\brief  set spot light
*/
/******************************************************************************/
void Shader::SetSpotLight(SpotLight * sLight, unsigned int lightCount)
{
	if (lightCount > MAX_SPOT_LIGHTS) lightCount = MAX_SPOT_LIGHTS;

	glUniform1i(uniformSpotLightCount, lightCount);

	for (size_t i = 0; i < lightCount; i++)
	{
		sLight[i].UseLight
		(uniformSpotLight[i].uniformAmbientIntensity, uniformSpotLight[i].uniformColour,
			uniformSpotLight[i].uniformDiffuseIntensity, uniformSpotLight[i].uniformPosition,
			uniformSpotLight[i].uniformDirection,
			uniformSpotLight[i].uniformConstant, uniformSpotLight[i].uniformLinear,
			uniformSpotLight[i].uniformExponent,
			uniformSpotLight[i].uniformEdge);
	}
}

/******************************************************************************/
/*!
\brief  set texture
*/
/******************************************************************************/
void Shader::SetTexture(GLuint textureUnit)
{
	glUniform1i(uniformTexture, textureUnit);
}

/******************************************************************************/
/*!
\brief  set normal
*/
/******************************************************************************/
void Shader::SetTextureNormal(GLuint textureUnit)
{
	glUniform1i(uniformTextureNormal, textureUnit);
}

/******************************************************************************/
/*!
\brief  set texture cubemap
*/
/******************************************************************************/
void Shader::SetTextureCubeMap(GLuint textureUnit)
{
	glUniform1i(uniformTextureCubeMap, textureUnit);
}

/******************************************************************************/
/*!
\brief  set directional shadow map
*/
/******************************************************************************/
void Shader::SetDirectionalShadowMap(GLuint textureUnit)
{
	glUniform1i(uniformDirectionalShadowMap, textureUnit);
}
/******************************************************************************/
/*!
\brief  set light transform
*/
/******************************************************************************/
void Shader::SetDirectionalLighttransform(glm::mat4 lTransform)
{
	glUniformMatrix4fv
	(uniformDirectionalLightTransform, 1,
		GL_FALSE, glm::value_ptr(lTransform));
}

/******************************************************************************/
/*!
\brief  set screen texture
*/
/******************************************************************************/
void Shader::SetScreenTexture(GLuint textureUnit)
{
	glUniform1i(uniformScreenTexture, textureUnit);
}

/******************************************************************************/
/*!
\brief  use shader
*/
/******************************************************************************/
void Shader::UseShader()
{
	glUseProgram(shaderID);

}

/******************************************************************************/
/*!
\brief clear shader
*/
/******************************************************************************/
void Shader::ClearShader()
{
	if (shaderID != 0)
	{
		glDeleteProgram(shaderID);
		shaderID = 0;
	}

	uniformModel = 0;
	uniformProjection = 0;
}

/******************************************************************************/
/*!
\brief add shader
*/
/******************************************************************************/
void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = static_cast<int>(strlen(shaderCode));

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

/******************************************************************************/
/*!
\brief  destructor
*/
/******************************************************************************/
Shader::~Shader()
{
	ClearShader();
}
