#pragma once

#include <glad/glad.h>
#include <stb_image.h>

class Texture
{
public:
	Texture(const char* path, GLenum target, GLenum internalformat, GLenum format, bool flipV = false);
	~Texture(){};
	void Activate();
	void Bind();
	void Unbind();
	/// Set a texture parameter. This operation will leave the texture as ACTIVE!
	void GL_TexParameteri(GLenum pname, GLenum param);
	bool IsLoaded();

	static int TEXTURE_NUMBER;
	unsigned int m_ID;
	unsigned int m_Number;

private:
	GLenum m_Target; // Texture type GLenum (2D, 3D, ...)
	int m_Width;
	int m_Height;
	int m_Channels;
	bool m_Loaded = false;
};