#pragma once
#include"Walnut/Layer.h"
#include"Walnut/Application.h"
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
		glm::vec2 m_PlayerPosition{ 00,50 };
		glm::vec2 m_PlayerVelocity{ 0, 0 };
		float m_PlayerSpeed = 50.0f;
		//Player rect size 
		glm::vec2 m_PlayerSize{ 20 ,20 };
		uint32_t m_PlayerColor{ 0xff0000ff };
	};
} 