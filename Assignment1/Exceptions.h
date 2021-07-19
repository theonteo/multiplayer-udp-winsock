/*****************************************************************************/
/*!
\file Exceptions.h
\author Teo Zheng Yong Theon
\par email: zhengyongtheon.teo\@digipen.edu
\par DigiPen login: zhengyongtheon.teo
\par Course: CS260
\par Assignment #3
\date 15/07/2021
\brief
This file contains exceptions handling
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