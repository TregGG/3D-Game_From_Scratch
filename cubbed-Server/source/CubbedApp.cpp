#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Core/Log.h"
#include <chrono>
#include "ServerLayer.h"
//for the server HEADLESS


Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Cubbed Server";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<Cubed::ServerLayer>();

	return app;
}