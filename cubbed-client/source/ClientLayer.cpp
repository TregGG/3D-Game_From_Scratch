#include "Walnut/Input/Input.h"
#include "ClientLayer.h"
#include"imgui.h"
#include"Walnut/ImGui/ImGuiTheme.h"
#include"imgui_internal.h"
#include "misc/cpp/imgui_stdlib.h"
#include"Walnut/Serialization/BufferStream.h"
#include"ServerPacket.h"
//temprary draw rect function
namespace Cubed {
	static Walnut::Buffer s_ScratchBuffer;

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
		s_ScratchBuffer.Allocate(10 * 1024 * 1024); // Allocated 10mb Towards the buffer

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

		Walnut::BufferStreamWriter stream(s_ScratchBuffer);
		stream.WriteRaw(PacketType::ClientUpdate);
		stream.WriteRaw<glm::vec2>(m_PlayerPosition);
		stream.WriteRaw<glm::vec2>(m_PlayerVelocity);
		m_Client.SendBuffer(stream.GetBuffer());


		
	}

	void ClientLayer::OnRender()
	{
		m_Client.SetDataReceivedCallback([this](const Walnut::Buffer buffer) {OnDataReceived(buffer);});
		
		
	}

	void ClientLayer::OnUIRender()
	{
		ImGui::ShowDemoWindow();
		Walnut::Client::ConnectionStatus connectionStatus = m_Client.GetConnectionStatus();
		if (connectionStatus == Walnut::Client::ConnectionStatus::Connected) {
			//Allow Client to Play games
			DrawRect(m_PlayerPosition, m_PlayerSize, m_PlayerColor);
			
			m_PlayerDataMutex.lock();

			std::map<uint32_t, PlayerData> playerData = m_PlayerData;

			m_PlayerDataMutex.unlock();

			for (const auto& [id, data] : playerData) {
				if (id == m_PlayerID)
					continue;
				DrawRect(data.Position, m_PlayerSize, 0xff00ff00);

			}
		
		}
		else {


			//Connect to server prompt

			bool readOnly = connectionStatus != Walnut::Client::ConnectionStatus::Disconnected;

			ImGui::Begin("Connect to Server");

		/*	if (readOnly) {
				ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
			}*/

			ImGui::InputText("Enter Server IP", &m_ServerAddress);
			if(connectionStatus==Walnut::Client::ConnectionStatus::FailedToConnect){
				ImGui::TextColored(ImColor(Walnut::UI::Colors::Theme::invalidPrefab), "Failed to connect. ");
			} else if (connectionStatus == Walnut::Client::ConnectionStatus::Connecting) {
				ImGui::TextColored(ImColor(Walnut::UI::Colors::Theme::textDarker), "Connecting..... ");

			}
			if (ImGui::Button("Connect")) {
				
				
					m_Client.ConnectToServer(m_ServerAddress);
				
			}
			/*if (readOnly) {
				ImGui::PopItemFlag();
			}*/
			ImGui::End();


		}
	}
	void ClientLayer::OnDataReceived(const Walnut::Buffer buffer)
	{
		Walnut::BufferStreamReader stream(buffer);

		PacketType type;
		stream.ReadRaw(type);
		switch (type)
		{
		case PacketType::ClientConnect:
			uint32_t idFromServer;
			stream.ReadRaw<uint32_t>(idFromServer);
			WL_INFO("Server Connected");
			WL_INFO("ID = {}", idFromServer);
			m_PlayerID = idFromServer;
			break;
		case PacketType::ClientUpdate:
			//list of other Clients
			m_PlayerDataMutex.lock();
			stream.ReadMap(m_PlayerData);
			m_PlayerDataMutex.unlock();
			break;
		}
	}
}
