#pragma once

#include "Hazel/Layer.h"
#include "Hazel/Events/MouseEvents.h"
#include "Hazel/Events/ApplicationEvents.h"
#include "Hazel/Events/KeyEvents.h"

namespace Hazel
{
	class HAZEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		static void Begin();  // see Application.cpp (globally runned)
		static void End();
	private:
		float m_Time = 0.0f;
	};

}

