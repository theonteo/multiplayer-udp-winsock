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

#include "Engine.h"
#include "Exceptions.h"

/******************************************************************************/
/*!
\brief  Main function
*/
/******************************************************************************/
int main(int argc, char** argv)
{
	Engine mainEngine;
	mainEngine.Init(argc,argv);
	mainEngine.Loop();
}

