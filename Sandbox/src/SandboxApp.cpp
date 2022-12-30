#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "Sandbox3D.h"

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		//PushLayer(Hazel::CreateRef<Sandbox3D>());
		PushLayer(Hazel::CreateRef<Sandbox2D>());
	}

	~Sandbox()
	{
	}

};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}