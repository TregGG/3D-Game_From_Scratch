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
		virtual void OnUIRender() override; 

	private:
		glm::vec2 m_PlayerPosition;
	};
}