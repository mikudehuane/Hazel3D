#pragma once

#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Shader.h"
#include "Texture.h"

namespace Hazel {

	class Renderer
	{
	public:
		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);
		
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		inline static Ref<ShaderLibrary> GetShaderLib() { return s_ShaderLibrary; }
		inline static Ref<Texture2D> GetWhiteTexture2D() { return s_WhiteTexture2D; }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;

		static Ref<ShaderLibrary> s_ShaderLibrary;
		static Ref<Texture2D> s_WhiteTexture2D;
	};
	
}

