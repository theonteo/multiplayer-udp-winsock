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

#include "Window.h"
#include "CommonValues.h"


bool Window::triggeredKeyList[1024];
bool Window::releasedKeyList[1024];
bool Window::KeyList[1024];


GLfloat  Window::xChange;
GLfloat  Window::yChange;

glm::vec2 Window::mousePos;

/******************************************************************************/
/*!
\brief  constructor
*/
/******************************************************************************/
Window::Window()
{
	width = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;
	//CameraMove = true;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
/******************************************************************************/
/*!
\brief  constructor
*/
/******************************************************************************/
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	for (size_t i = 0; i < 1024; i++)
		keys[i] = 0;
}

/******************************************************************************/
/*!
\brief  init window
*/
/******************************************************************************/
int Window::Init()
{

	// Initialise GLFW
	if (!glfwInit())
	{
		printf("GLFW initialisation failed!");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	mainWindow = glfwCreateWindow(width, height, "CS260 - A4 Engine", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW window creation failed!");
		glfwTerminate();
		return 1;
	}

	CameraMove = false;

	//Buffer Size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//Set context
	glfwMakeContextCurrent(mainWindow);

	//handle input
	createCallbacks();

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialisation failed!");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// Setup Viewport size 
	glViewport(0, 0, bufferWidth, bufferHeight);
	glfwSetWindowUserPointer(mainWindow, this);
	return 1;
}
/******************************************************************************/
/*!
\brief call backs
*/
/******************************************************************************/
void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
	glfwSetMouseButtonCallback(mainWindow, mouse_button_callback);
}


/******************************************************************************/
/*!
\brief		get key
*/
/******************************************************************************/
bool Window::getKey(size_t index)
{
	return KeyList[index];
}

/******************************************************************************/
/*!
\brief		get key up
*/
/******************************************************************************/
bool Window::getKeyUp(size_t index)
{
	return !KeyList[index];
}

/******************************************************************************/
/*!
\brief		get key triggered
*/
/******************************************************************************/
bool Window::getKeyTriggered(size_t index)
{
	if (KeyList[index])
	{
		if (triggeredKeyList[index] == 0)
		{
			triggeredKeyList[index] = true;
			return true;
		}
	}
	else if (!KeyList[index])
	{
		triggeredKeyList[index] = false;
	}
	return false;
}

/******************************************************************************/
/*!
\brief		get key released
*/
/******************************************************************************/
bool Window::getKeyReleased(size_t index)
{
	if (!KeyList[index])
	{
		if (releasedKeyList[index] == 0)
		{
			releasedKeyList[index] = true;
			return true;
		}
	}
	else if (KeyList[index])
	{
		releasedKeyList[index] = false;
	}
	return false;
}

/******************************************************************************/
/*!
\brief		Get Mouse Position
*/
/******************************************************************************/
glm::vec2 Window::GetMousePos()
{
	return mousePos;
}

/******************************************************************************/
/*!
\brief get x change
*/
/******************************************************************************/
GLfloat Window::getXchange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

/******************************************************************************/
/*!
\brief get y change
*/
/******************************************************************************/
GLfloat Window::getYchange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

/******************************************************************************/
/*!
\brief get main window
*/
/******************************************************************************/
GLFWwindow* Window::getMainWindow()
{
	return	mainWindow;
}

/******************************************************************************/
/*!
\brief  mouse button callback
*/
/******************************************************************************/
void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	(void)window;
	(void)mods;

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		KeyList[GLFW_MOUSE_BUTTON_RIGHT] = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{
		KeyList[GLFW_MOUSE_BUTTON_RIGHT] = false;
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		KeyList[GLFW_MOUSE_BUTTON_LEFT] = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		KeyList[GLFW_MOUSE_BUTTON_LEFT] = false;
	}

	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
	{
		KeyList[GLFW_MOUSE_BUTTON_MIDDLE] = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
	{
		KeyList[GLFW_MOUSE_BUTTON_MIDDLE] = false;
	}
}

/******************************************************************************/
/*!
\brief  handle keys
*/
/******************************************************************************/
void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	(void)mode; (void)code;
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			KeyList[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			KeyList[key] = false;
		}
	}
	if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
	{

		theWindow->CameraMove = !theWindow->CameraMove;
		if (theWindow->CameraMove == true)
		{
			glfwSetInputMode(theWindow->mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else {
			glfwSetInputMode(theWindow->mainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			printf("Pressed:%d", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			printf("Pressed:%d", key);
		}
	}
}

/******************************************************************************/
/*!
\brief handle mouse
*/
/******************************************************************************/
void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (theWindow->CameraMove == true)
	{
		if (theWindow->mouseFirstMoved)
		{
			theWindow->lastX = static_cast<GLfloat>(xPos);
			theWindow->lastY = static_cast<GLfloat>(yPos);
			theWindow->mouseFirstMoved = false;
		}
		theWindow->xChange = static_cast<GLfloat>(xPos) - theWindow->lastX;
		theWindow->yChange = theWindow->lastY - static_cast<GLfloat>(yPos);
		theWindow->lastX = static_cast<GLfloat>(xPos);
		theWindow->lastY = static_cast<GLfloat>(yPos);
	}
	else {
		theWindow->xChange = 0;
		theWindow->yChange = 0;
		theWindow->lastX = static_cast<GLfloat>(xPos);
		theWindow->lastY = static_cast<GLfloat>(yPos);
	}

	theWindow->mousePos = glm::vec2(theWindow->lastX, theWindow->lastY);
}

/******************************************************************************/
/*!
\brief  destructor
*/
/******************************************************************************/
Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}
