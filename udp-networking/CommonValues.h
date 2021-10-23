/******************************************************************************/
/*!
\file CommonValues.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

#ifndef COMMONVALUES_H
#define COMMONVALUES_H

constexpr int START_PLAYER = 4;
constexpr int MAX_PLAYER = 4;
constexpr int MAX_PEER = MAX_PLAYER - 1;

constexpr int MAX_FOOD = 250;

constexpr int MAX_POINT_LIGHTS = 4;
constexpr int MAX_SPOT_LIGHTS = 3;

constexpr int WINDOW_WIDTH = 1366;
constexpr int WINDOW_HEIGHT = 768;

#endif