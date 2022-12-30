#pragma once

#include "RenderCommand.h"

#include "Hazel/Renderer/OrthographicCamera.h"
#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/Material.h"

namespace Hazel {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();
		
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Material>& material);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Material>& material);
	};
	
}

