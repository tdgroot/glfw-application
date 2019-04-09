#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "test_texture.h"

namespace test {
	TestTexture::TestTexture()
		: translation_a(0, 0, 0), translation_b(0, 0, 0)
	{
		const struct
		{
			float x, y, z;
			float r, g, b;
			float t0, t1;
		} vertices[12] = {
			{ -0.3f, -0.3f, 0.6f,	1.f, 0.f, 0.f,		0.0f, 0.0f, }, // Left
			{  0.3f, -0.3f, 0.6f,	0.0f, 1.0f, 0.f,	1.0f, 0.0f }, // Right
			{   0.f,  0.3f, 0.3f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f }, // Top
			{   0.f, -0.3f, 0.0f,	1.f, 1.f, 0.f,		0.0f, 1.0f }, // Back
		};

		static unsigned int indices[] = {
			0, 1, 2,
			1, 3, 2,
			3, 0, 2,
			0, 1, 3
		};

		vao = std::make_unique<VertexArray>();
		vertex_buffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
		VertexBufferLayout layout;
		layout.push<float>(3); // vertex xyz
		layout.push<float>(3); // vertex rgb
		layout.push<float>(2); // vertex t1t2

		vao->add_buffer(*vertex_buffer, layout);
		index_buffer = std::make_unique<IndexBuffer>(indices, 12);

		float ratio = 1280 / (float)720; // TODO: Fetch width and height dynamically.
		proj = glm::ortho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);
		view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		texture = std::make_unique<Texture>("res/image.png");
		shader = std::make_unique<Shader>("shader/texture.vert", "shader/texture.frag");
		shader->bind();
		shader->set_uniform1i("u_Texture", 0);
	}

	TestTexture::~TestTexture()
	{
	}

	void TestTexture::on_update(float delta)
	{
	}

	void TestTexture::on_render()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader->bind();
		texture->bind();

		// Initialize and calculate MVP (model view protection) matrix.
		// Model: translation, rotation and scale of object in space.
		// View: the view of the camera.
		// Projection: the projection matrix of our window

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translation_a);
			model = glm::rotate(model, (float)glfwGetTime()*1.5f, glm::vec3(1, 0, 0));
			model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0, 0, 1));

			glm::mat4 mvp = proj * view * model;
			shader->set_uniform_mat4f("MVP", 1, mvp);

			renderer.draw(*vao, *index_buffer, *shader);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translation_b);
			model = glm::rotate(model, (float)glfwGetTime()*1.5f, glm::vec3(1, 0, 0));
			model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0, 0, 1));

			glm::mat4 mvp = proj * view * model;
			shader->set_uniform_mat4f("MVP", 1, mvp);

			renderer.draw(*vao, *index_buffer, *shader);
		}
	}

	void TestTexture::on_imgui_render()
	{
		ImGui::SliderFloat3("Translation A", &translation_a.x, -1.0f, 1.0f);
		ImGui::SliderFloat3("Translation B", &translation_b.x, -1.0f, 1.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}