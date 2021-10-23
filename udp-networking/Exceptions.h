/******************************************************************************/
/*!
\file Exceptions.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

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