#pragma once

#include "Walnut/Layer.h"
#include "HeadlessConsole.h"
#include "Walnut/Networking/Server.h"
#include <glm/glm.hpp>

namespace Cubed {

	class ServerLayer : public Walnut::Layer
	{
	public:
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(float ts) override;
		virtual void OnUIRender() override;
	private:
		void OnConsoleMessageCallback(std::string_view message);

		void OnClientConnected(const Walnut::ClientInfo& clientInfo);
		void OnClientDisconnected(const Walnut::ClientInfo& clientInfo);
		void OnDataReceived(const Walnut::ClientInfo& clientInfo, const Walnut::Buffer Buffer);
	private:
		int m_port = 8192;
		HeadlessConsole m_Console;
		Walnut::Server m_Server{ m_port };
	};

}