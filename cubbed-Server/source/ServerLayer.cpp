#include "ServerLayer.h"
#include "Walnut/Core/Log.h"
#include"Walnut/Serialization/BufferStream.h"
#include"ServerPacket.h"


namespace Cubed
{
	static Walnut::Buffer s_ScratchBuffer;
	void Cubed::ServerLayer::OnAttach()
	{
		s_ScratchBuffer.Allocate(10 * 1024 * 1024); // Allocated 10mb


		m_Console.SetMessageSendCallback([this](std::string_view message) {OnConsoleMessageCallback(message);});
		m_Server.SetClientConnectedCallback([this](const Walnut::ClientInfo ClientInfo) {OnClientConnected(ClientInfo);});
		m_Server.SetClientDisconnectedCallback([this](const Walnut::ClientInfo ClientInfo) {OnClientDisconnected(ClientInfo);});
		m_Server.SetDataReceivedCallback([this](const Walnut::ClientInfo ClientInfo, const Walnut::Buffer Buffer) {OnDataReceived(ClientInfo, Buffer);});


		m_Server.Start();
	}

	void Cubed::ServerLayer::OnDetach()
	{
		m_Server.Stop();
	}

	void Cubed::ServerLayer::OnUpdate(float ts)
	{
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(5ms);
	}

	void Cubed::ServerLayer::OnUIRender()
	{
	}
	void ServerLayer::OnConsoleMessageCallback(std::string_view message)
	{
		if (message.starts_with('/')) {
			//	----	Add command logic here	----
			if (message == "/stop") {
				m_Server.Stop();
				exit(0);
			}
			//just for test purposes
			std::cout << "You called the " << message << " command!\n";
	}
	}
	void ServerLayer::OnClientConnected(const Walnut::ClientInfo& clientInfo)
	{
		WL_INFO_TAG("Server", "Client Connected :: ID = {}", clientInfo.ID);
		Walnut::BufferStreamWriter stream(s_ScratchBuffer);
		//we want to give client their ID so that we know which client is which
		stream.WriteRaw(PacketType::ClientConnect);
		stream.WriteRaw(clientInfo.ID);
		m_Server.SendBufferToClient(clientInfo.ID, stream.GetBuffer());
	}
	void ServerLayer::OnClientDisconnected(const Walnut::ClientInfo& clientInfo)
	{
		WL_INFO_TAG("Server", "Client Disconnected :: ID = {}", clientInfo.ID);

	}
	void ServerLayer::OnDataReceived(const Walnut::ClientInfo& clientInfo, const Walnut::Buffer Buffer)
	{
		Walnut::BufferStreamReader stream(Buffer);
		PacketType type;
		stream.ReadRaw(type);
		switch (type) {
		case PacketType::ClientUpdate :
		{
			
			//WL_INFO_TAG("Server", "{}, {} - {}, {} ", pos.x, pos.y, vel.x, vel.y);
			m_PlayerDataMutex.lock();

			PlayerData& playerData = m_PlayerData[clientInfo.ID];

			stream.ReadRaw<glm::vec2>(playerData.Position);
			stream.ReadRaw<glm::vec2>(playerData.Velocity);


			m_PlayerDataMutex.unlock();
			break;
		}
		}
	}
}
