#pragma once

#include "Hazel/Renderer/Texture.h"

namespace Hazel {
	
	class AssetsManager
	{
	public:
		// if exists, return it, else load it and return it
		Ref<Texture> LoadTextureImpl(const std::string& filepath, const std::string& name);

		inline bool IsTextureExistImpl(const std::string& name) const
		{
			return m_Textures.find(name) != m_Textures.end();
		}

		inline Ref<Texture> GetTextureImpl(const std::string& name) const
		{
			return m_Textures.at(name);
		}
	public:
		static Ref<Texture> LoadTexture(const std::string& filepath, const std::string& name = "")
		{
			return s_Instance->LoadTextureImpl(filepath, name);
		}
		static bool IsTextureExist(const std::string& name)
		{
			return s_Instance->IsTextureExistImpl(name);
		}
		static Ref<Texture> GetTexture(const std::string& name)
		{
			return s_Instance->GetTextureImpl(name);
		}
	private:
		std::unordered_map<std::string, Ref<Texture>> m_Textures;
	private:  // statics
		static AssetsManager* s_Instance;
	};

}

