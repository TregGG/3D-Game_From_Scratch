#pragma once
#include"Walnut/Layer.h"
#include"Walnut/Application.h"
#include "Walnut/Networking/Client.h"

#include <glm/glm.hpp>



namespace Cubed {
	class ClientLayer : public Walnut::Layer
	{
	public:


		virtual void OnAttach()  override;
		virtual void OnDetach()  override;
		virtual void OnUpdate(float ts) override;
		virtual void OnRender() override;
		virtual void OnUIRender()override;
	private:
		static void OnDataReceived(const Walnut::Buffer buffer);
	private:
		glm::vec2 m_PlayerPosition{ 00,50 };
		glm::vec2 m_PlayerVelocity{ 0, 0 };
		float m_PlayerSpeed = 100.0f;
		//Player rect size 
		glm::vec2 m_PlayerSize{ 50 ,50};
		uint32_t m_PlayerColor{ 0xff0000ff };
		uint32_t m_PlayerID;

		//server-client
		Walnut::Client m_Client;
		std::string m_ServerAddress;
		
	};
} 