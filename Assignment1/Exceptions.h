/******************************************************************************/
/*!
\file Exceptions.h
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
This file contains exception class.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <exception>
#include <string>

//exception handling 
class exceptionHandler :public std::exception
{
	std::string message;
	int errorCode;

public:
	//get code number
	int GetErrorCode() const throw ()
	{
		return errorCode;
	}

	//get message string
	const char* what() const throw ()
	{
		return  message.c_str();
	}

	//set message and error code
	exceptionHandler(const std::string& w, int code)
	{
		message = w;
		errorCode = code;
	}
};
#endif