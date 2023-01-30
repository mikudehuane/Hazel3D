#pragma once

#include "RenderCommand.h"

#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Light.h"
#include "Mesh.h"

namespace Hazel {

	class Renderer
	{
	public:
		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);
		
		static void BeginScene(
			const Camera& camera,
			// lighting
			const Ref<DirectionalLight>& directionalLight = nullptr,
			const std::vector<Ref<PointLight>>& pointLights = {},
			const Ref<SpotLight>& spotLight = nullptr
		);
		static void EndScene();

		static void Submit(
			const Ref<Mesh>& mesh,
			const glm::mat4& modelTransform = glm::mat4(1.0f)
		);
		// submit a light source to draw
		static void Submit(
			const Ref<VertexArray>& vertexArray, 
			const Ref<Light>& light,
			const glm::mat4& modelTransform = glm::mat4(1.0f)
		);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		inline static Ref<ShaderLibrary> GetShaderLib() { return s_ShaderLibrary; }
	private:
		static void DrawVertexArray(const Ref<VertexArray>& vertexArray);
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;

		static Ref<ShaderLibrary> s_ShaderLibrary;
	};
	
}

