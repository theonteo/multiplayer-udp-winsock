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
#include <imconfig.h>
#include "Interface.h"
#include "Camera.h"
#include "Lighting.h"
#include "Model.h"
#include "Resource.h"
#include "Material.h"
#include "GameObject.h"

/******************************************************************************/
/*!
\brief  show UI
*/
/******************************************************************************/
void Interface::ShowMainUI()
{
	//set up new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();


	static bool opt_fullscreen_persistant = true;
	static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_PassthruCentralNode;
	bool opt_fullscreen = opt_fullscreen_persistant;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;

	if (opt_fullscreen)
	{

		ImGuiStyle& st = ImGui::GetStyle();

		st.FrameBorderSize = 0.0f;
		st.FramePadding = ImVec2(12.0f, 3.0f);
		st.ItemSpacing = ImVec2(8.0f, 5.0f);
		st.WindowBorderSize = 5.0f;
		st.TabBorderSize = 15.0f;
		st.WindowRounding = 15.0f;
		st.ChildRounding = 15.0f;
		st.FrameRounding = 15.0f;
		st.ScrollbarRounding = 15.0f;
		st.GrabRounding = 15.0f;
		st.TabRounding = 15.0f;
		// Setup style
		ImVec4* colors = ImGui::GetStyle().Colors;

		//Set all editor colours
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 0.95f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.21f, 0.21f, 0.21f, 1.0f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.21f, 0.21f, 0.21f, 1.0f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.17f, 0.17f, 0.17f, 1.0f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.0f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.22f, 0.22f, 0.22f, 0.40f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.16f, 0.16f, 0.16f, 0.53f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.17f, 0.17f, 0.17f, 1.0f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.17f, 0.17f, 0.17f, 1.0f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.17f, 0.17f, 0.17f, 1.0f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.0f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.48f, 0.48f, 0.48f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.79f, 0.79f, 0.79f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.48f, 0.47f, 0.47f, 0.91f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.55f, 0.55f, 0.62f);
		colors[ImGuiCol_Button] = ImVec4(0.08f, 0.08f, 0.08f, 0.8f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.67f, 0.67f, 0.68f, 0.33f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.26f, 0.26f, 0.26f, 0.33f);
		colors[ImGuiCol_Header] = ImVec4(0.0f, 0.0f, 0.0f, 0.20f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.20f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.25f, 0.25f, 0.25f, 0.20f);
		colors[ImGuiCol_Separator] = ImVec4(0.0f, 0.0f, 0.0f, 0.2f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.2f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.0f, 0.0f, 0.0f, 0.2f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.87f, 0.87f, 0.87f, 0.53f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.87f, 0.87f, 0.87f, 0.74f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.87f, 0.87f, 0.87f, 0.74f);
		colors[ImGuiCol_Tab] = ImVec4(0.01f, 0.01f, 0.01f, 0.4f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.01f, 0.01f, 0.01f, 0.4f);
		colors[ImGuiCol_TabActive] = ImVec4(0.03f, 0.03f, 0.03f, 0.4f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.01f, 0.01f, 0.01f, 0.4f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.01f, 0.01f, 0.01f, 0.4f);
		colors[ImGuiCol_DockingPreview] = ImVec4(0.38f, 0.48f, 0.60f, 1.00f);
		colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 0.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.68f, 0.68f, 0.68f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.77f, 0.33f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.87f, 0.55f, 0.08f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.47f, 0.60f, 0.76f, 0.47f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(0.58f, 0.58f, 0.58f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::SetNextWindowBgAlpha(0.0f);

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking ;
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

		window_flags |= ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowBgAlpha(0.0f);
	ImGui::Begin("A4 Networking - Engine", dock_open, window_flags);
	ImGui::PopStyleVar(3);

	// Dockspace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
	}

	ImGui::End();

	ImGui::Begin("Inspector", &Inspector_Header);
	if (ImGui::TreeNodeEx("Settings",
		ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_DefaultOpen, "Information", -1))
	{
		GameObject* gameobject_selected = (*Resource::GameObject_List.begin()).second;

		ImGui::Text("Press shift to toggle fly mode");
		ImGui::Separator();

		if (ImGui::Button("Change Model"))
			ImGui::OpenPopup("change_model");
		ImGui::SameLine();
		ImGui::Text("Select a new model");

		if (ImGui::Button("Toggle Normals"))
			Resource::enableNormal = !Resource::enableNormal;
		ImGui::SameLine();
		ImGui::Text("Enable/Disable Normals");

		if (ImGui::Button("Toggle Lighting"))
		{
			Resource::fragmentLighting = !Resource::fragmentLighting;

			if (Resource::fragmentLighting)
			{
				gameobject_selected->shader = (*Resource::Shader_List.find("Shaders\\shader")).second;
			}
			else {
				gameobject_selected->shader = (*Resource::Shader_List.find("Shaders\\shader_vertex")).second;
			}
		}
		ImGui::SameLine();
		ImGui::Text("Switch between vertex/fragment lighting");

		if (ImGui::BeginPopup("change_model"))
		{
			for (const auto& i : Resource::Model_List)
			{
				if (ImGui::MenuItem(i.first.c_str()))
				{
					gameobject_selected->rotation = glm::vec3(0);
					gameobject_selected->Model->ClearModel();
					gameobject_selected->Model = (*Resource::Model_List.find(i.first.c_str())).second;
					gameobject_selected->Model->LoadAssetModel((*Resource::Model_List.find(i.first.c_str())).second->ModelName);
				}
			}
			ImGui::EndPopup();
		}

		ImGui::TreePop();
	}
	ImGui::Separator();
	if (Resource::GameObject_List.size() > 0)
	{
		for (auto& i : Resource::GameObject_List)
		{

			GameObject* gameobject_selected = i.second;

			if (ImGui::TreeNodeEx(i.first.c_str(),
				ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_DefaultOpen, i.first.c_str(), -1))
			{

			
				char buf1[64] = "";
				ImGui::Text("Transform");
				ImGui::Columns(3, NULL, false);
				ImGui::DragFloat("##Translate_x", &gameobject_selected->translate.x, 0.1f);
				ImGui::NextColumn();
				ImGui::DragFloat("##Translate_y", &gameobject_selected->translate.y, 0.1f);
				ImGui::NextColumn();
				ImGui::DragFloat("##Translate_z", &gameobject_selected->translate.z, 0.1f);
				ImGui::Columns(1);
				ImGui::Text("Rotation");
				ImGui::Columns(3, NULL, false);
				ImGui::DragFloat("##Rotation_x", &gameobject_selected->rotation.x, 0.1f);
				ImGui::NextColumn();
				ImGui::DragFloat("##Rotation_y", &gameobject_selected->rotation.y, 0.1f);
				ImGui::NextColumn();
				ImGui::DragFloat("##Rotation_z", &gameobject_selected->rotation.z, 0.1f);
				ImGui::Columns(1);
				ImGui::Text("Scale");
				ImGui::Columns(3, NULL, false);
				ImGui::DragFloat("##Scale_x", &gameobject_selected->scale.x, 0.1f);
				ImGui::NextColumn();
				ImGui::DragFloat("##Scale_y", &gameobject_selected->scale.y, 0.1f);
				ImGui::NextColumn();
				ImGui::DragFloat("##Scale_z", &gameobject_selected->scale.z, 0.1f);
				ImGui::Columns(1);
				ImGui::TreePop();
			}
		}
	}

	for (auto& i : Resource::Light_List)
	{
		if (ImGui::TreeNodeEx(i.first.c_str(), ImGuiTreeNodeFlags_Framed, i.first.c_str(), -1))
		{
			ImGui::Text("Position");
			std::string x = "##Translate_x" + i.first;
			std::string y = "##Translate_y" + i.first;
			std::string z = "##Translate_z" + i.first;


			std::string x_col = "##Col_x" + i.first;
			std::string y_col = "##Col_y" + i.first;
			std::string z_col = "##Col_z" + i.first;
			std::string intensity = "##intensity" + i.first;
			std::string aintensity = "##aintensity" + i.first;
			ImGui::Columns(3, NULL, false);
			ImGui::DragFloat(x.c_str(), &static_cast<PointLight*>(i.second)->position.x, 0.1f);
			ImGui::NextColumn();
			ImGui::DragFloat(y.c_str(), &static_cast<PointLight*>(i.second)->position.y, 0.1f);
			ImGui::NextColumn();
			ImGui::DragFloat(z.c_str(), &static_cast<PointLight*>(i.second)->position.z, 0.1f);
			ImGui::Columns(1);
			ImGui::Text("Colour");
			ImGui::Columns(3, NULL, false);
			ImGui::DragFloat(x_col.c_str(), &static_cast<PointLight*>(i.second)->colour.x, 0.1f);
			ImGui::NextColumn();
			ImGui::DragFloat(y_col.c_str(), &static_cast<PointLight*>(i.second)->colour.y, 0.1f);
			ImGui::NextColumn();
			ImGui::DragFloat(z_col.c_str(), &static_cast<PointLight*>(i.second)->colour.z, 0.1f);
			ImGui::Columns(1);

			ImGui::Text("Light Intensity");

			ImGui::Columns(3, NULL, false);
			ImGui::DragFloat(intensity.c_str(), &static_cast<PointLight*>(i.second)->diffuseIntensity, 0.1f);
			ImGui::Columns(1);
			ImGui::Text("Ambient Intensity");
			ImGui::Columns(3, NULL, false);
			ImGui::DragFloat(aintensity.c_str(), &static_cast<PointLight*>(i.second)->ambientIntensity, 0.1f);
			ImGui::Columns(1);
			ImGui::TreePop();
		}
	}
	if (ImGui::TreeNodeEx("Directional Light", ImGuiTreeNodeFlags_Framed, "Directional Light", -1))
	{
		ImGui::Text("Rotation");
		ImGui::Columns(3, NULL, false);
		ImGui::DragFloat("##Translate_x", &Resource::directionalRotation.x, 0.1f);
		ImGui::NextColumn();
		ImGui::DragFloat("##Translate_y", &Resource::directionalRotation.y, 0.1f);
		ImGui::NextColumn();
		ImGui::DragFloat("##Translate_z", &Resource::directionalRotation.z, 0.1f);
		ImGui::Columns(1);
		
		ImGui::Text("Colour");
		std::string x_col = "##Col_x_dir";
		std::string y_col = "##Col_y_dir";
		std::string z_col = "##Col_z_dir";
		ImGui::Columns(3, NULL, false);
		ImGui::DragFloat(x_col.c_str(), &static_cast<Light*>(&Lighting::mainLight)->colour.x, 0.1f);
		ImGui::NextColumn();
		ImGui::DragFloat(y_col.c_str(), &static_cast<Light*>(&Lighting::mainLight)->colour.y, 0.1f);
		ImGui::NextColumn();
		ImGui::DragFloat(z_col.c_str(), &static_cast<Light*>(&Lighting::mainLight)->colour.z, 0.1f);
		ImGui::Columns(1);
		ImGui::TreePop();


	}
	ImGui::Separator();
	if (ImGui::TreeNodeEx("Camera", ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_DefaultOpen, "Camera", -1))
	{
		ImGui::Text("FOV");
		ImGui::SameLine();
		ImGui::DragFloat("##fov", &Resource::camera->fov, 0.1f);

		ImGui::Text("Near Plane");
		ImGui::SameLine();
		ImGui::DragFloat("##near", &Resource::camera->nearPlane, 0.1f);

		ImGui::Text("Far Plane");
		ImGui::SameLine();
		ImGui::DragFloat("##far", &Resource::camera->farPlane, 0.1f);

		ImGui::Text("Position");
		ImGui::Columns(3, NULL, false);
		ImGui::DragFloat("##Cam_x", &Resource::camera->position.x, 0.1f);
		ImGui::NextColumn();
		ImGui::DragFloat("##Cam_y", &Resource::camera->position.y, 0.1f);
		ImGui::NextColumn();
		ImGui::DragFloat("##Cam_z", &Resource::camera->position.z, 0.1f);
		ImGui::Columns(1);


		ImGui::Text("Rotation");
		ImGui::Columns(2, NULL, false);
		ImGui::DragFloat("##Cam_pitch", &Resource::camera->pitch, 0.1f);
		ImGui::NextColumn();
		ImGui::DragFloat("##Cam_yaw", &Resource::camera->yaw, 0.1f);
		ImGui::Columns(1);
		ImGui::TreePop();
	}

	ImGui::End();


	//render imgui
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

