#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"


#include "ClientLayer.h"

//client side app 
// 
// 
// /////--------BOTTOM COMMENTED OUT PART IS DEPRECATED AND NOW IN ClientLayer.h/cpp-------------------------------\\\\\
//class ExampleLayer : public Walnut::Layer
//{
//public:
//	virtual void OnUIRender() override
//	{
//		ImGui::Begin("Hello");
//		ImGui::Button("Button");
//		ImGui::End();
//
//		ImGui::ShowDemoWindow();
//		DrawRect(50, 80, 120, 80, 0xff0000ff);
//
//		UI_DrawAboutModal();
//	}
//
//	void UI_DrawAboutModal()
//	{
//		if (!m_AboutModalOpen)
//			return;
//
//		ImGui::OpenPopup("About");
//		m_AboutModalOpen = ImGui::BeginPopupModal("About", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
//		if (m_AboutModalOpen)
//		{
//			auto image = Walnut::Application::Get().GetApplicationIcon();
//			ImGui::Image(image->GetDescriptorSet(), { 48, 48 });
//
//			ImGui::SameLine();
//			Walnut::UI::ShiftCursorX(20.0f);
//
//			ImGui::BeginGroup();
//			ImGui::Text("Walnut application framework");
//			ImGui::Text("by Studio Cherno.");
//			ImGui::EndGroup();
//
//			if (Walnut::UI::ButtonCentered("Close"))
//			{
//				m_AboutModalOpen = false;
//				ImGui::CloseCurrentPopup();
//			}
//
//			ImGui::EndPopup();
//		}
//	}
//
//	void ShowAboutModal()
//	{
//		m_AboutModalOpen = true;
//	}
//private:
//	bool m_AboutModalOpen = false;
//};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Walnut Client";
	spec.CustomTitlebar = true;
	spec.UseDockspace = false;

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<Cubed::ClientLayer>();
	
	return app;
}