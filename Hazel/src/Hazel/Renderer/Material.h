#pragma once

#include "Hazel/Core/Core.h"
#include <Hazel/Renderer/Texture.h>
#include <Hazel/Renderer/Shader.h>

namespace Hazel {

	class Material
	{
	public:
		Material(Ref<Shader> shader);
		void SetTexture(Ref<Texture> texture, int slot);
	private:
		Ref<Shader> m_Shader;
	};

}
