#pragma once
#include "Components.h"
class Tile: public Component {
	private:
		float side = 40.0f;
		float width;
		float height;

		IndexBuffer* ib;
		VertexBuffer* vb;
		VertexArray* va;
		Shader* shader_basic;
		Texture* texture;

		std::vector<float> vertices;
		std::vector<unsigned int> indexes;

		Transform* pos;
		glm::mat4 m_MVP;
	public: 
		Tile(float now_width, float now_height, const char* pathShader, const char* pathTexture);
		void update() override;
		void firstDraw() override;
		void init() override;
};
