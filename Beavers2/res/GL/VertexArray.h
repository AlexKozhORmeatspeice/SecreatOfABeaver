#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Render.h"

class VertexArray
{
private:
	unsigned int m_RendererArrID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};