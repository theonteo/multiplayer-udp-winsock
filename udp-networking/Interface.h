/******************************************************************************/
/*!
\file Interface.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

#ifndef INTERFACE_H
#define INTERFACE_H

class Interface
{
	bool* dock_open;
	bool Inspector_Header;
	bool showUI{ true };

public:
	bool GetShowUI() const;
	void ToggleShowUI();
	void ShowMainUI();
};
#endif