#include "Walnut/Input/Input.h"
#include "ClientLayer.h"
#include"imgui.h"
#include"imgui_internal.h"
#include "misc/cpp/imgui_stdlib.h"
//temprary draw rect function
namespace Cubed {
	static ImVec2 GlmVec2ToImVec2(glm::vec2 v) {
		return ImVec2(v.x, v.y);
	}
	static void DrawRect(glm::vec2 position, glm::vec2 size, uint32_t color)
	{
		ImDrawList* drawList = ImGui::GetBackgroundDrawList();
		ImVec2 min = ImGui::GetWindowPos() + ImVec2(GlmVec2ToImVec2(position));
		ImVec2 max = min + ImVec2(GlmVec2ToImVec2(size));
		drawList->AddRectFilled(min, max, color);
	}


	void ClientLayer::OnAttach()
	{
	}

	void ClientLayer::OnDetach()
	{
	}

	void ClientLayer::OnUpdate(float ts)
	{
		if (m_Client.GetConnectionStatus() != Walnut::Client::ConnectionStatus::Connected) {
			return; // No Playability for the client not connected to the server
		}

		glm::vec2 dir{ 0.0f,0.0f };
		if (Walnut::Input::IsKeyDown(Walnut::KeyCode::W)) {
			dir.y = -1;
		}else if (Walnut::Input::IsKeyDown(Walnut::KeyCode::S)) {
			dir.y = 1;
		}if (Walnut::Input::IsKeyDown(Walnut::KeyCode::D)) {
			dir.x = 1;
		}else if (Walnut::Input::IsKeyDown(Walnut::KeyCode::A)) {
			dir.x = -1;
		}

		if (glm::length(dir) > 0.0f)
		{
			dir = glm::normalize(dir);
			m_PlayerVelocity = dir * m_PlayerSpeed;
		}
		
		m_PlayerVelocity = glm::mix(m_PlayerVelocity, glm::vec2(00.00f), 5.0f*ts);
		m_PlayerPosition += m_PlayerVelocity * ts;
	}

	void ClientLayer::OnRender()
	{
	}

	void ClientLayer::OnUIRender()
	{
		ImGui::ShowDemoWindow();
		Walnut::Client::ConnectionStatus connectionStatus = m_Client.GetConnectionStatus();
		if (connectionStatus == Walnut::Client::ConnectionStatus::Connected) {
			//Allow Client to Play games
			DrawRect(m_PlayerPosition, m_PlayerSize, m_PlayerColor);
		}
		else {
			//Connect to server prompt
			ImGui::Begin("Connect to Server");
			ImGui::InputText("Enter Server IP",&m_ServerAddress);
			if (ImGui::Button("Connect")) {
				m_Client.ConnectToServer(m_ServerAddress);
			}
			ImGui::End();


		}
	}
}
