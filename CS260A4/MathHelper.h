/******************************************************************************/
/*!
\file MathHelper.h
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
This file contains the declarations of the Math Helper class.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/
#pragma once
namespace MathHelper
{
	/******************************************************************************/
	/*!
	\brief     float Clamp(float _t, float _min, float _max)
				 caps a number _t between the range _min and _max
	*/
	/******************************************************************************/
	inline float Clamp(float _t, float _min, float _max)
	{
		if (_t > _max) return _max;
		if (_t < _min) return _min;

		return _t;
	}
	/******************************************************************************/
	/*!
	\brief     lerp
				 travels between points "from" to point "to"
				 Using interpolant which is from 0 to 1
				 e.g. 0.5 is midway

	*/
	/******************************************************************************/
	inline float Lerp(float from, float to, float interpolant)
	{
		return from + (to - from) * Clamp(interpolant, 0, 1);
	}
	inline glm::vec3 Vec3Lerp
	(const glm::vec3& from, const glm::vec3& to, float interpolant)
	{
		float x = Lerp(from.x, to.x, interpolant);
		float y = Lerp(from.y, to.y, interpolant);
		float z = Lerp(from.z, to.z, interpolant);

		return { x,y,z };
	}
	inline glm::vec2 Vec2Lerp
	(const glm::vec2& from, const glm::vec2& to, float interpolant)
	{
		float x = Lerp(from.x, to.x, interpolant);
		float y = Lerp(from.y, to.y, interpolant);

		return { x,y };
	}
}