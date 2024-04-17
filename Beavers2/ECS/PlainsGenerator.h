#pragma once
#include "Components.h"
class Tile: public Component {
	private:
		float side = 40.0f;
		float width;
		float height;
		Renderer renderer;
		IndexBuffer* ib;
		VertexBuffer* vb;
		VertexArray* va;
		Shader* shader_basic;
		Texture* texture;
		std::vector<float> vertices;
		std::vector<unsigned int> indexes;
		std::shared_ptr<PositionComponent> pos;
		glm::mat4 m_MVP;
	public: 
		Tile(float now_height, float now_width, const char* pathShader, const char* pathTexture);
		void update() override;
		void draw() override;
		void init() override;
};
