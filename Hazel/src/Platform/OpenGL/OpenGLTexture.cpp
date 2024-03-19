#include "hzpch.h"
#include "OpenGLTexture.h"
#include "Hazel/Core/Constants.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace Hazel {
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, void* data)
		: m_Path(""), m_Width(width), m_Height(height), m_Channels(4)
	{
		Init();
		if (data)
		{
			SetData(data, m_Width * m_Height * m_Channels);
		}
	}
	
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(false);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		HZ_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;
		m_Channels = channels;

		Init();

		SetData(data, m_Width * m_Height * m_Channels);
		//glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		HZ_CORE_ASSERT(size == m_Width * m_Height * m_Channels, "Data must be entire texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

	void OpenGLTexture2D::SetTexWrapS(int param)
	{
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GetGLParam(param));
	}

	void OpenGLTexture2D::SetTexWrapT(int param)
	{
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GetGLParam(param));
	}

	void OpenGLTexture2D::Init()
	{
		if (m_Channels == 4)
		{
			m_InternalFormat = GL_RGBA8;
			m_DataFormat = GL_RGBA;
		}
		else if (m_Channels == 3)
		{
			m_InternalFormat = GL_RGB8;
			m_DataFormat = GL_RGB;
		}

		HZ_CORE_ASSERT(m_InternalFormat & m_DataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	int OpenGLTexture2D::GetGLParam(int param) const
	{
		switch (param)
		{
			case HZ_REPEAT: return GL_REPEAT;
			case HZ_MIRRORED_REPEAT: return GL_MIRRORED_REPEAT;
			case HZ_CLAMP_TO_EDGE: return GL_CLAMP_TO_EDGE;
			case HZ_CLAMP_TO_BORDER: return GL_CLAMP_TO_BORDER;
			case HZ_NEAREST: return GL_NEAREST;
			case HZ_LINEAR: return GL_LINEAR;
			case HZ_NEAREST_MIPMAP_NEAREST: return GL_NEAREST_MIPMAP_NEAREST;
			case HZ_LINEAR_MIPMAP_NEAREST: return GL_LINEAR_MIPMAP_NEAREST;
			case HZ_NEAREST_MIPMAP_LINEAR: return GL_NEAREST_MIPMAP_LINEAR;
			case HZ_LINEAR_MIPMAP_LINEAR: return GL_LINEAR_MIPMAP_LINEAR;
		}
		HZ_CORE_ASSERT(0, "Unsupported Param");
		return 0;
	}

}
