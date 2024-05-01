#include "VertexArray.h"


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererArrID);
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererArrID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elems = layout.GetElemnts();

	unsigned int offset = 0;
	for (unsigned int i = 0; i < elems.size(); i++)
	{
		const auto& elem = elems[i];
		
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, elem.count, elem.type, elem.normalaized, layout.GetStride(), (const void*)offset));

		offset += elem.count * VertexBufferElement::GetSizeOfType(elem.type);
	}
}


void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererArrID));
}
void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}