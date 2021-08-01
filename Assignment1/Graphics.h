
#pragma once

#include <glm.hpp>
#include "GL/glew.h"

namespace Graphics
{
	enum class ClearMode
	{
		BIT_DEPTH,
		BIT_COLOR,
		BIT_COLORDEPTH
	};

	/******************************************************************************/
	/*!
	\brief   generate vertex array
	*/
	/******************************************************************************/
	inline void GenVertexArray(GLuint& meshvaoID, GLuint& meshvboID, const float* temp, GLuint size)
	{
		glGenVertexArrays(1, &meshvaoID);
		glGenBuffers(1, &meshvboID);
		glBindVertexArray(meshvaoID);
		glBindBuffer(GL_ARRAY_BUFFER, meshvboID);
		glBufferData(GL_ARRAY_BUFFER, size, temp, GL_STATIC_DRAW);
	}

	/******************************************************************************/
	/*!
	\brief   generate vertex array dynamic
	*/
	/******************************************************************************/
	inline void GenVertexArrayDynamic(GLuint& meshvaoID, GLuint& meshvboID, const float* temp, GLuint size)
	{
		glGenVertexArrays(1, &meshvaoID);
		glGenBuffers(1, &meshvboID);
		glBindVertexArray(meshvaoID);
		glBindBuffer(GL_ARRAY_BUFFER, meshvboID);
		glBufferData(GL_ARRAY_BUFFER, size, temp, GL_DYNAMIC_DRAW);
	}

	/******************************************************************************/
	/*!
	\brief   bind vertex sub buffer
	*/
	/******************************************************************************/
	inline void BindVertexSubBuffer(GLuint& ID, const float* temp, GLuint size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, temp);
	}

	/******************************************************************************/
	/*!
	\brief   bind verte sub buffer with offset
	*/
	/******************************************************************************/
	inline void BindVertexSubBuffer(GLuint& ID, const float* temp, GLuint size, GLuint offset)
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, temp);
	}

	/******************************************************************************/
	/*!
	\brief   set active texture
	*/
	/******************************************************************************/
	inline void ActiveTexture(const GLuint& ID)
	{
		glActiveTexture(GL_TEXTURE0 + ID);
	}

	/******************************************************************************/
	/*!
	\brief   enable vertex array attribute
	*/
	/******************************************************************************/
	inline void EnableVertexArrayAttribute(const GLuint& ID, const GLuint& width, const GLuint& size, void* pointer)
	{
		glEnableVertexAttribArray(ID);
		glVertexAttribPointer(ID, width, GL_FLOAT, GL_FALSE, size, pointer);
	}

	/******************************************************************************/
	/*!
	\brief   draw triangles array
	*/
	/******************************************************************************/
	inline void DrawTrianglesArray(const GLuint& meshID, const GLuint& indicesSize)
	{
		glBindVertexArray(meshID);
		glDrawArrays(GL_TRIANGLES, 0, indicesSize);
	}

	/******************************************************************************/
	/*!
	\brief   delete vertex array
	*/
	/******************************************************************************/
	inline void DeleteVertexArray(const GLuint& num)
	{
		glDeleteVertexArrays(1, &num);
	}

	/******************************************************************************/
	/*!
	\brief   bind texture
	*/
	/******************************************************************************/
	inline void BindTexture(const GLuint& TextureID)
	{
		glBindTexture(GL_TEXTURE_2D, TextureID);
	}

	/******************************************************************************/
	/*!
	\brief   use frame buffer texture
	*/
	/******************************************************************************/
	inline void UseFrameBufferTexture(const GLuint& _bufferTextureID)
	{
		glBindTexture(GL_TEXTURE_2D, _bufferTextureID);
	}

	/******************************************************************************/
	/*!
	\brief   delete frame buffer
	*/
	/******************************************************************************/
	inline void DeleteFrameBuffer(const GLuint& num)
	{
		glDeleteBuffers(1, &num);
	}

	/******************************************************************************/
	/*!
	\brief   use frame buffer
	*/
	/******************************************************************************/
	inline void UseFrameBuffer(const GLuint& num)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, num);
	}



	/******************************************************************************/
	/*!
	\brief   render buffer storage
	*/
	/******************************************************************************/
	inline void RenderBufferStorage(GLuint& BufferID,
		const GLuint& width, const GLuint& height, const GLuint& component,
		const GLuint& attachment)

	{
		glRenderbufferStorage(GL_RENDERBUFFER, component, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, BufferID);
	}


	/******************************************************************************/
	/*!
	\brief   create render buffer
	*/
	/******************************************************************************/
	inline void CreateRenderBuffer(GLuint& BufferID)
	{
		glGenRenderbuffers(1, &BufferID);
		glBindRenderbuffer(GL_RENDERBUFFER, BufferID);
	}

	/******************************************************************************/
	/*!
	\brief   create frame buffer
	*/
	/******************************************************************************/
	inline void CreateFrameBuffer(GLuint& BufferID)
	{
		glGenFramebuffers(1, &BufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, BufferID);
	}



	/******************************************************************************/
	/*!
	\brief   send texture
	*/
	/******************************************************************************/
	inline void SendTexture(GLuint texID, int activeTex, GLint texLoc)
	{
		glActiveTexture(GL_TEXTURE0 + activeTex);
		glBindTexture(GL_TEXTURE_2D, texID);
		glUniform1i(texLoc, activeTex);
	}

	/******************************************************************************/
	/*!
	\brief   send cubemap
	*/
	/******************************************************************************/
	inline void SendCubeMap(GLuint texID, GLuint activeTex, GLint texLoc)
	{
		glActiveTexture(GL_TEXTURE0 + activeTex);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
		glUniform1i(texLoc, activeTex);
	}

	/******************************************************************************/
	/*!
	\brief   send texture
	*/
	/******************************************************************************/
	inline void SendTexture(GLuint texID, GLuint activeTex)
	{
		glActiveTexture(GL_TEXTURE0 + activeTex);
		glBindTexture(GL_TEXTURE_2D, texID);
	}

	/******************************************************************************/
	/*!
	\brief   send cubemap
	*/
	/******************************************************************************/
	inline void SendCubeMap(GLuint texID, GLuint activeTex)
	{
		glActiveTexture(GL_TEXTURE0 + activeTex);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
	}

	/******************************************************************************/
	/*!
	\brief   clear viewport
	*/
	/******************************************************************************/
	inline void ClearViewport(ClearMode mode)
	{
		if (mode == ClearMode::BIT_COLOR)
			glClear(GL_COLOR_BUFFER_BIT);
		if (mode == ClearMode::BIT_COLORDEPTH)
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (mode == ClearMode::BIT_DEPTH)
			glClear(GL_DEPTH_BUFFER_BIT);
	}

	/******************************************************************************/
	/*!
	\brief   set viewport
	*/
	/******************************************************************************/
	inline void Viewport(const size_t& width, const size_t& height, ClearMode mode)
	{
		glViewport(0, 0, static_cast<GLuint>(width), static_cast<GLuint>(height));

		if (mode == ClearMode::BIT_COLOR)
			glClear(GL_COLOR_BUFFER_BIT);
		if (mode == ClearMode::BIT_COLORDEPTH)
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (mode == ClearMode::BIT_DEPTH)
			glClear(GL_DEPTH_BUFFER_BIT);
	}



	/******************************************************************************/
	/*!
	\brief   set if back face rendering is enabled
	*/
	/******************************************************************************/
	inline void EnableBackFace(bool enabled)
	{
		if (enabled)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}
	}

	/******************************************************************************/
	/*!
	\brief   set if transparency is enabled
	*/
	/******************************************************************************/
	inline void EnableTransparency(bool enabled)
	{
		if (enabled)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//glDisable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_BLEND);
			//	glEnable(GL_DEPTH_TEST);
			glBlendFunc(GL_ONE, GL_ZERO);
		}
	}

	/******************************************************************************/
	/*!
	\brief   set if color blend is enabled
	*/
	/******************************************************************************/
	inline void EnableColorBlend(bool enabled)
	{
		if (enabled)
		{
			glEnable(GL_BLEND);
			glBlendEquation(GL_FUNC_ADD);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDisable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
			glBlendFunc(GL_ONE, GL_ZERO);
		}
	}

	/******************************************************************************/
	/*!
	\brief   set uniform int
	*/
	/******************************************************************************/
	inline void UniformInt(GLint location, const GLint& i)
	{

		glUniform1i(location, i);
	}

	/******************************************************************************/
	/*!
	\brief   set uniform bool
	*/
	/******************************************************************************/
	inline void UniformBool(GLint location, bool b)
	{
		glUniform1i(location, b);
	}

	/******************************************************************************/
	/*!
	\brief   set uniform float
	*/
	/******************************************************************************/
	inline void UniformFloat(GLint location, const GLfloat& f)
	{
	
		glUniform1f(location, f);
	}
	/******************************************************************************/
	/*!
	\brief   set uniform vec2
	*/
	/******************************************************************************/
	inline void UniformVec2(GLint location, const glm::vec2& vec)
	{
		
		glUniform2f(location, vec.x, vec.y);
	}

	/******************************************************************************/
	/*!
	\brief   set uniform vec3
	*/
	/******************************************************************************/
	inline void UniformVec3(GLint location, const glm::vec3& vec)
	{
	
		glUniform3f(location, vec.x, vec.y, vec.z);
	}

	/******************************************************************************/
	/*!
	\brief   set uniform vec4
	*/
	/******************************************************************************/
	inline void UniformVec4(GLint location, const glm::vec4& vec)
	{
	
		glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
	}

	/******************************************************************************/
	/*!
	\brief   set uniform mat4
	*/
	/******************************************************************************/
	inline void UniformMat4(GLint location, const glm::mat4& mat)
	{

		
		glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<const float*>(&mat));
	}

	/******************************************************************************/
	/*!
	\brief   set uniform mat3
	*/
	/******************************************************************************/
	inline void UniformMat3(GLint location, const glm::mat3& mat)
	{
		
		glUniformMatrix3fv(location, 1, GL_FALSE, reinterpret_cast<const float*>(&mat));
	}
}
