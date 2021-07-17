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

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_win32.h>
#include <imconfig.h>

#include <Interface.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <cmath>
#include <vector>

#include <Render.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <Mesh.h>
#include <Shader.h>
#include <Window.h>
#include <Camera.h>
#include <Texture.h>
#include <DirectionalLight.h>
#include <PointLight.h>
#include <SpotLight.h>
#include <Resource.h>
#include <GameObject.h>
#include <Material.h>
#include <Model.h>
#include <GameObjectManager.h>
#include <Skybox.h>
#include <PostProcess.h>
#include <glm.hpp>
#include <imgui.h>

#include "Lighting.h"
namespace
{
	Interface interface_game;
	Resource main_editor;
	Window mainWindow;
	Camera camera;
	Lighting lighting;

	GLfloat deltaTime = 0.0f;
	GLfloat lastTime = 0.0f;

	static glm::vec2 savePos{ 0 };
	static glm::vec3 saveRot{ 0 };
}

/******************************************************************************/
/*!
\brief  Move object
*/
/******************************************************************************/
void MoveObject()
{
	const std::unique_ptr<GameObject>& iter = 
		GameObjectManager::GameObjectList.find(Resource::SelectedGameObjectElement)->second;
	if (Window::getKeyTriggered(GLFW_MOUSE_BUTTON_RIGHT))
	{
		savePos = Window::GetMousePos();
		saveRot = iter->rotation;
	}

	if (Window::getKey(GLFW_MOUSE_BUTTON_RIGHT))
	{
		iter->rotation.y = saveRot.y + (Window::GetMousePos().x - savePos.x);
		iter->rotation.z = saveRot.z + (Window::GetMousePos().y - savePos.y);
	}
}

/******************************************************************************/
/*!
\brief  Main function
*/
/******************************************************************************/
int main()
{
	//set up window
	mainWindow = Window(WINDOW_WIDTH, WINDOW_HEIGHT);
	mainWindow.Init();

	//set up camera
	camera = Camera(glm::vec3(0.6f, 0.0f, 2.1f), 
		glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.25f);
	Resource::camera = &camera;

	//set up imgui
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImFont* pFont = io.Fonts->AddFontFromFileTTF("Fonts/font.ttf", 17.5f);
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(mainWindow.getMainWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 130");
	
	//load everything
	Render::postprocess.LoadPostProcessing();
	main_editor.loadFiles();

	//init
	Lighting::init();
	Render::Init();

	Render::AssignShaders();
	Render::AssignRenderObject();

	if (!ImGui_ImplOpenGL3_Init())
		printf("notloaded");

	// enable backface culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	Resource::SelectedGameObjectElement = GameObjectManager::GameObjectList.find("Main Object")->first;
	Resource::directionalRotation = glm::vec3(180, 0, 0);

	//main loop
	while (!mainWindow.getShouldClose())
	{
		//calculate delta time
		GLfloat now = static_cast<GLfloat>(glfwGetTime());
		deltaTime = now - lastTime;
		lastTime = now;

		//Handle User Input
		glfwPollEvents();

		//calculate camera control
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXchange(), mainWindow.getYchange());

		//move object
		MoveObject();

		//main render pass
		Render::RenderPass(camera.calculateViewMatrix(),
			camera.calculateProjectionMatrix
			((GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight()));

		//show show editor
		interface_game.ShowMainUI();
		mainWindow.swapBuffers();
	}

	//delete all
	Resource::DeleteAllFiles();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return 0;
}

