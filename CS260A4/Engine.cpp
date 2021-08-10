/******************************************************************************/
/*!
\file Engine.cpp
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
This file contains the definitions of the Engine class used asd the main driver
of the Game Engine.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

#include "Engine.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_win32.h>
#include <imconfig.h>
#include <DeltaTime.h>
#include <Interface.h>

#include <thread>
#include <functional>
#include <Player.h>

#include <GL/glew.h>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <map>
#include <UIManager.h>
#include <NetworkManager.h>
#include <Game.h>
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
#include <Lighting.h>
#include "Exceptions.h"
#include <GLFW/glfw3.h>

void Engine::Init(char** argv)
{
	network.Init(argv);
	srand(369420);

	GameObjectManager::Create();
	Game::Init(&network);

	std::thread loopThread(std::bind(&Engine::EngineLoop, this));
	std::thread networkThread(std::bind(&Engine::NetworkLoop, this));

	network.ConnectToPeers();

	loopThread.join();
	networkThread.join();
}

void Engine::EngineLoop()
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
	//ImFont* pFont = io.Fonts->AddFontFromFileTTF("Fonts/font.ttf", 17.5f);
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(mainWindow.getMainWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 130");

	//load everything
	Render::postprocess.LoadPostProcessing();
	main_editor.loadFiles();

	DeltaTime::Init();
	Lighting::init();
	Render::Init();
	ui.Init();
	Loop();

	//imgui shutdown
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Engine::NetworkLoop()
{
	network.Receive();
}

void Engine::Loop()
{
	//main loop
	while (!network.GetShutDownStatus() && !mainWindow.getShouldClose())
	{
		//calculate delta time
		DeltaTime::CalculateDeltaTime();

		//Handle User Input
		glfwPollEvents();

		//calculate camera control
		camera.keyControl(mainWindow.getsKeys(), DeltaTime::GetDeltaTime());
		camera.mouseControl(mainWindow.getXchange(), mainWindow.getYchange());

		//main game update
		Game::Update();

		//send any information to other clients if needed
		network.Send();

		//main render pass
		Render::RenderPass(camera.calculateViewMatrix(),
			camera.calculateProjectionMatrix
			((GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight()));

		//ui text render
		ui.Render(network.GetPlayerData());

		//show show editor
		if (Window::getKeyReleased(GLFW_KEY_I))
			interface_game.ToggleShowUI();
		if (interface_game.GetShowUI())
			interface_game.ShowMainUI();
		mainWindow.swapBuffers();
	}

	network.ShutDown();
}

NetworkManager* Engine::GetNetworkManager()
{
	return &network;
}
