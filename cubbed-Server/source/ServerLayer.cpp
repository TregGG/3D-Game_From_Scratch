#include "ServerLayer.h"




namespace Cubed
{
	void Cubed::ServerLayer::OnAttach()
	{
		m_Console.SetMessageSendCallback([this](std::string_view message) {OnConsoleMessageCallback(message);});
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
}
