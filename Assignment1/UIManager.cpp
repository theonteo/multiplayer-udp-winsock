#include "UIManager.h"
#include "UIText.h"

void UIManager::Init()
{
	//text setup
	TextRender::Init();

}

void UIManager::Render()
{
	TextRender::RenderTextNormal
	(std::string{ "NETWORK.IO" }, 0.5f, 0.9f, 0, 1.2f,
		glm::vec4(1.0f, 0.75f, 0.5f, 1.0f));
}
