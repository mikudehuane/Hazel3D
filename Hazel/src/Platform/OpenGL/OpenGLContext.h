#pragma once

#include "Hazel/Renderer/GraphicsContext.h"

struct GLFWwindow;  // TODO: ??? #include <GLFW/glfw3.h>

namespace Hazel {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}
