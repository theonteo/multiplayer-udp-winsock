/******************************************************************************/
/*!
\file MathHelper.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

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