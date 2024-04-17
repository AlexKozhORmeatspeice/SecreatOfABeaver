#pragma once
#include "Renderer.h"
#include <map>

class Texture
{
private:
	std::map<std::string, GLint> param_map = 
	{ {"CLAMP", GL_CLAMP_TO_EDGE}, {"REPEAT", GL_REPEAT}};
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const std::string& path, std::string mode);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; };
	inline int GetHeight() const { return m_Height; };
};