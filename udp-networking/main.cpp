/******************************************************************************/
/*!
\file Main.cpp
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

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

