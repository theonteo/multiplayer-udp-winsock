/******************************************************************************/
/*!
\file Main.cpp
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
This file is the main driver of the application.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

#include <iostream>
#include "Engine.h"
#include "Exceptions.h"

/******************************************************************************/
/*!
\brief  Main function
*/
/******************************************************************************/
int main(int argc, char** argv)
{
	//store error code
	int errorCode = 0;

	//try catch exception system
	try
	{
		if (argc != 5)
		{
			throw exceptionHandler("Wrong number of arguments ", 1);
		}

		Engine mainEngine;

		mainEngine.Init(argv);
		mainEngine.Loop();
	}
	catch (exceptionHandler& e)
	{
#ifdef PRINTDEBUG
		std::cerr << "Exception caught : " << e.what()
			<< " Error Code : " << e.GetErrorCode() <<
			" - Exiting " << std::endl;
#else
		std::cout << "An error has occured - exiting" << std::endl;
#endif

		//set error code
		errorCode = e.GetErrorCode();
}
	catch (...)
	{
#ifdef PRINTDEBUG
		std::cerr << "Unknown Exception caught! - Exiting "
			<< std::endl;
#else
		std::cerr << "Unknown Error encountered! - Exiting "
			<< std::endl;
#endif
	}
	std::cout << "Server exit" << std::endl;

}

