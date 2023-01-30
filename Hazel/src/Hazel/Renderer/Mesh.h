#pragma once

#include "Hazel/Core/Core.h"
#include "Hazel/Renderer/Vertex.h"
#include "Hazel/Renderer/Texture.h"
#include "Hazel/Renderer/VertexArray.h"
#include "Hazel/Renderer/Material.h"
#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Renderer/Shader.h"

namespace Hazel {

	class Mesh
	{
	public:
		// TODO(islander): pass right values to move, avoid copying
		Mesh(
			const std::vector<Vertex>& vertices,
			const std::vector<uint32_t>& indices,
			const Ref<Material>& material
		):
			m_Vertices(vertices), m_Indices(indices), m_Material(material)
		{
			SetupMesh();
		}

		inline Ref<Material> GetMaterial() { return m_Material; }
		inline Ref<VertexArray> GetVertexArray() { return m_VertexArray; }
	private:
		void SetupMesh();
	private:
		std::vector<Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
		Ref<Material> m_Material;

		Ref<VertexArray> m_VertexArray;
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	};

}
