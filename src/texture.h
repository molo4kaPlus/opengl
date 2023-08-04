#pragma once

#include "Renderer.h"
#define STB_IMAGE_IMPLEMENTATION

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Widh, m_Height, m_BPP;

public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidh() const { return m_Widh; }
	inline int GetHeight() const { return m_Height; }
};