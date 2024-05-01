#pragma once
#include <iostream>

#include "Shader.h"

#include <GLErrors.h>

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Renderer
{
private:

public:
	static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

	static void DrawLines(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

	
	void Clear();
};