/*****************************************************************************/
/*!
\file Exception.h

\author Bryan Choo
\author Kevin Hartono
\author Teo Zheng Yong Theon

\par Course: cs260
\par Assignment 4
\date 1/8/21

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/*****************************************************************************/

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