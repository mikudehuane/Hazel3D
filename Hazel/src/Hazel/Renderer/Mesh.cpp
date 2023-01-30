#include "hzpch.h"
#include "Mesh.h"

namespace Hazel {

	void Mesh::SetupMesh()
	{
		m_VertexArray = Hazel::VertexArray::Create();
		
		m_VertexBuffer = Hazel::VertexBuffer::Create(
			reinterpret_cast<float*>(m_Vertices.data()),
			m_Vertices.size() * sizeof(Vertex)
		);
		m_VertexBuffer->SetLayout(Vertex::GetLayout());
		m_IndexBuffer = Hazel::IndexBuffer::Create(
			m_Indices.data(),
			m_Indices.size()
		);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_VertexArray->Unbind();
	}

}
