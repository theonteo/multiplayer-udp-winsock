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
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <cmath>
#include <vector>
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

/******************************************************************************/
/*!
\brief  Parse main entry data
*/
/******************************************************************************/
std::vector<Player> Engine::ParseEntry
(int argc, char** argv)
{
	int count = argc - 1;
	std::vector<Player> playerData;

	for (int i = 1; i <= count; ++i)
	{
		std::string temp = argv[i];
		const auto& divider = temp.find_first_of(":");
		std::string l1{ temp.begin(),temp.begin() + divider };
		std::string l2{ temp.begin() + divider + 1,temp.end() };
		Player p{ l1,l2 };
		playerData.emplace_back(std::move(p));

	}
	return playerData;
}


namespace
{
	Interface interface_game;
	Resource main_editor;
	Window mainWindow;
	Camera camera;
	Lighting lighting;
	NetworkManager network;

	int ac;
	char** av;

}
void Engine::Init(int argc, char** argv)
{
	ac = argc;
	av = argv;
	std::thread loopThread(std::bind(&Engine::EngineLoop, this));
	std::thread networkThread(std::bind(&Engine::NetworkLoop, this));

	loopThread.join();
	networkThread.join();
}

void Engine::EngineLoop()
{
	int argc = ac;
	char** argv = av;


	//store error code
	int errorCode = 0;

	//try catch excepton system
	try
	{
		//store network data to vector
		std::vector<Player> data;

		if (argc != 5)
			throw
			exceptionHandler("Wrong number of arguments ", 1);

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

		DeltaTime::Init();
		Lighting::init();
		Render::Init();
		UIManager::Init();

		GameObjectManager::Create();
		Loop();
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


	//delete all
	Resource::DeleteAllFiles();

	//imgui shutdown
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	}

void Engine::NetworkLoop()
{
	while (!ac)
		network.Init(ParseEntry(ac, av));
	network.Update();
}

void Engine::Loop()
{
	//main loop
	while (!mainWindow.getShouldClose())
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

		//main render pass
		Render::RenderPass(camera.calculateViewMatrix(),
			camera.calculateProjectionMatrix
			((GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight()));

		//ui text render
		UIManager::Render();

		//show show editor
		interface_game.ShowMainUI();
		mainWindow.swapBuffers();
	}
}
