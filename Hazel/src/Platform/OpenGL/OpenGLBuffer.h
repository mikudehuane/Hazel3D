#pragma once

#include "Hazel/Renderer/Buffer.h"

namespace Hazel {
	
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override 
		{ 
			m_Layout = layout; 
			m_VertexCount = m_Size / layout.GetStride();
		}

		inline virtual uint32_t GetVertexCount() const override { return m_VertexCount; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Size;
		BufferLayout m_Layout;
		uint32_t m_VertexCount = 0;
	};
	
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual uint32_t GetCount() const { return m_Count; }
	private:
		uint32_t m_RendererID, m_Count;
	};
}
