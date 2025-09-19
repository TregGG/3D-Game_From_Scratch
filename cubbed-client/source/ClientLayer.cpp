#include "ClientLayer.h"
#include"imgui.h"
#include"imgui_internal.h"
//temprary draw rect function
static void DrawRect(float x, float y, float width, float height, uint32_t color)
{
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	ImVec2 min = ImGui::GetWindowPos() + ImVec2(x, y);
	ImVec2 max = min + ImVec2(width, height);
	drawList->AddRectFilled(min, max, color);
}


void Cubed::ClientLayer::OnAttach()
{
}

void Cubed::ClientLayer::OnDetach()
{
}

void Cubed::ClientLayer::OnUpdate(float ts)
{

}

void Cubed::ClientLayer::OnRender()
{
}

void Cubed::ClientLayer::OnUIRender()
{
	ImGui::ShowDemoWindow();
}
