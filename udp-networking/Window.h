/******************************************************************************/
/*!
\file Window.cpp
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>

class Input;
class Window
{
	friend Input;
	GLFWwindow* mainWindow;
	bool CameraMove;
	static glm::vec2 mousePos;

	GLint width, height;
	GLint bufferWidth, bufferHeight;

	bool keys[1024];

	GLfloat lastX;
	GLfloat lastY;
	static GLfloat xChange;
	static GLfloat yChange;
	bool mouseFirstMoved;

public:

	Window();
	~Window();
	Window(GLint windowWidth, GLint windowHeight);

	int Init();

	
	static glm::vec2 GetMousePos();
	static bool getKeyTriggered(size_t index);
	static bool getKeyReleased(size_t index);
	static bool getKeyUp(size_t index);
	static bool getKey(size_t index);

	GLint getBufferWidth() { return bufferWidth; }
	GLint getBufferHeight() { return bufferHeight; }
	static GLfloat getXchange();
	static GLfloat getYchange();
	GLFWwindow* getMainWindow();
	bool* getsKeys() { return keys; }
	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }
	void swapBuffers() { glfwSwapBuffers(mainWindow); }

private:
	static bool triggeredKeyList[1024];
	static bool releasedKeyList[1024];
	static bool KeyList[1024];
	void createCallbacks();
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};

#endif