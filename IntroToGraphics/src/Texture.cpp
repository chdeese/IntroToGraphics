#include "Texture.h"
#include "vendor/stb_image.h"

//sets default values and images 
Texture::Texture(const std::string& path) : m_rendererID(0), m_filePath(path), m_width(0), m_height(0), m_BPP(0)
{
	//loads our texture
	stbi_set_flip_vertically_on_load(1);
	m_localBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, 4);

	//creates and binds our texture spot
	glGenTextures(1, &m_rendererID);
	glBindTexture(GL_TEXTURE_2D, m_rendererID);

	//configure how our texture is drawn
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//set our texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_localBuffer) //free useless space
		stbi_image_free(m_localBuffer);
}

//deletes the textures
Texture::~Texture()
{
	glDeleteTextures(1, &m_rendererID);
}

//sets this texture as active and bind it to the renderer program
void Texture::bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_rendererID);
}

//sets the render program's texture to null
void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
