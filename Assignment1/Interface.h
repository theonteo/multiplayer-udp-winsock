/*****************************************************************************/
/*!
\file Interface.h

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