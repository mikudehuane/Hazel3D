#pragma once

#include "Hazel/Core/Core.h"

#include <glm/glm.hpp>

namespace Hazel {

	class Texture
	{
	public:
		enum Type { Diffuse, Specular, Emission };
	public:
		virtual ~Texture() = default;
		
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;
		
		virtual void Bind(uint32_t slot = 0) const = 0;
		
		// texture setup
		virtual void SetTexWrapS(int param) = 0;
		virtual void SetTexWrapT(int param) = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(uint32_t width, uint32_t height, void* data = nullptr);
		static Ref<Texture2D> Create(const std::string& path);
		static Ref<Texture2D> CreateFlatColor(const glm::vec4& color);
	};

}

