#pragma once

#include "test.h"
#include "vertexarray.h"
#include "vertexbuffer.h"
#include "vertexbuffer_layout.h"
#include "indexbuffer.h"
#include "shader.h"
#include "texture.h"
#include "renderer.h"

#include <glm/glm.hpp>
#include <memory>

namespace test {
	class TestTexture : public Test
	{
	public:
		TestTexture();
		~TestTexture();
		
		void on_update(float delta) override;
		void on_render() override;
		void on_imgui_render() override;
	private:
		std::unique_ptr<VertexArray> vao;
		std::unique_ptr<VertexBuffer> vertex_buffer;
		std::unique_ptr<IndexBuffer> index_buffer;
		std::unique_ptr<Shader> shader;
		std::unique_ptr<Texture> texture;
		Renderer renderer;
		glm::mat4 proj, view;
		glm::vec3 translation_a, translation_b;
	};
}
