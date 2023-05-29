#include <Texture.h>
#include <iostream>


int Texture::TEXTURE_NUMBER = 0;

Texture::Texture(const char* path, GLenum target, GLenum internalformat, GLenum format, bool flipV)
	: m_Number(GL_TEXTURE0 + TEXTURE_NUMBER++), m_Target(target)
{
	glGenTextures(1, &m_ID);
	glActiveTexture(m_Number);
	glBindTexture(target, m_ID);

	stbi_set_flip_vertically_on_load(flipV);

	unsigned char* data = stbi_load(path, &m_Width, &m_Height, &m_Channels, 0);
	if (data)
	{
		// Set texture data to Texture object
		glTexImage2D(target, 0, internalformat, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(target);
		m_Loaded = true;
	}
	else
	{
		std::cout << "FAILED::TEXTURE::LOADING  --> " << path << std::endl;
	}
	// Free space
	stbi_image_free(data);
	glBindTexture(target, 0);
}

void Texture::Activate()
{
	glActiveTexture(m_Number);
}

void Texture::Bind()
{
	glBindTexture(m_Target, m_ID);
}

void Texture::Unbind()
{
	glBindTexture(m_Target, 0);
}

void Texture::GL_TexParameteri(GLenum pname, GLenum param)
{
	Activate();
	Bind();
	glTexParameteri(m_Target, pname, param);
	Unbind();
}


bool Texture::IsLoaded()
{
	return m_Loaded;
}

