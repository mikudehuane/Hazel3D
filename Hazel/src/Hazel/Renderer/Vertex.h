#pragma once

#include "glm/glm.hpp"

#include "Hazel/Renderer/Buffer.h"

namespace Hazel {
	
	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoord;

		static inline BufferLayout GetLayout()
		{
			return {
				{ Hazel::ShaderDataType::Float3, "a_Position" },
				{ Hazel::ShaderDataType::Float3, "a_Normal" },
				{ Hazel::ShaderDataType::Float2, "a_TexCoord" }
			};
		}
	};

}

