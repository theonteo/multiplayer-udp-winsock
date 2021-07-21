/*****************************************************************************/
/*!
\file
\author
\par email:
\par DigiPen login:
\par Course: cs260
\par Assignment 4
\date

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/*****************************************************************************/

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
		Engine mainEngine;

		mainEngine.Init(argc, argv);
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

