#include "test_object_renderer.h"

#include "vertex.h"

#include <GLFW/glfw3.h>

#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace test {
	TestObjectRenderer::TestObjectRenderer()
	{
		std::vector<Vertex> vertices;
		std::vector<float> normals;
		std::vector<unsigned int> vertex_indices;
		std::vector<unsigned int> texture_indices;
		std::vector<unsigned int> normal_indices;
		const char* file = "res/cup.obj";
		std::ifstream in(file);

		while (in.good()) {
			std::string line;
			std::getline(in, line);

			// Read in the obj file, following the format as described by:
			// - https://www.cs.cmu.edu/~mbz/personal/graphics/obj.html

			// Object name
			if (line.find("o ") == 0) {
				printf("Info: loading object %s from file %s\n", line.substr(2).c_str(), file);
			}

			// Vertices
			if (line.find("v ") == 0) {
				std::string input = line.substr(2);
				std::vector<std::string> fields;
				boost::split(fields, input, boost::is_any_of(" "));
				float x = stof(fields[0]);
				float y = stof(fields[1]);
				float z = stof(fields[2]);
				float r = sin((rand() % 100) / (float)100);
				float g = 0.0f;
				float b = cos((rand() % 100) / (float)100);

				vertices.push_back({
					x, y, z,
					r, g, b,
					0.0f, 0.0f, 0.0f
				});
			}

			if (line.find("vn ") == 0) {
				std::string token;
				std::istringstream token_stream(line.substr(3));
				while (std::getline(token_stream, token, ' ')) {
					float normal = stof(token);
					normals.push_back(normal);
				}
			}

			// Face
			if (line.find("f ") == 0) {
				std::string token;
				std::istringstream token_stream(line.substr(2));
				while (std::getline(token_stream, token, ' ')) {
					std::vector<std::string> fields;
					boost::split(fields, token, boost::is_any_of("/"));
					
					unsigned int vertex_index = stoi(fields[0]) - 1; // -1 because obj starts index with 1, while opengl expects starting index 0.
					vertex_indices.push_back(vertex_index);

					if (!fields[1].empty()) {
						unsigned int texture_index = stoi(fields[1]) - 1;
						texture_indices.push_back(texture_index);
					}

					if (!fields[2].empty()) {
						unsigned int normal_index = stoi(fields[2]) - 1;
						normal_indices.push_back(normal_index);
					}
				}
			}
		}

		// TODO: %I64u is Windows specific.
		printf("Info: parsed %I64u vertices\n", vertices.size());
		printf("Info: parsed %I64u normals\n", normals.size());
		printf("Info: parsed %I64u indices\n", vertex_indices.size());

		for (unsigned int i = 0; i < vertex_indices.size(); i++) {
			unsigned int vertex_index = vertex_indices[i];
			unsigned int normal_index = normal_indices[i] * 3;
			Vertex* vertex = &vertices[vertex_index];
			vertex->nx = normals[normal_index + 0];
			vertex->ny = normals[normal_index + 1];
			vertex->nz = normals[normal_index + 2];
		}

		vao = std::make_unique<VertexArray>();
		vertex_buffer = std::make_unique<VertexBuffer>(&vertices[0], sizeof(Vertex) * vertices.size());
		VertexBufferLayout layout;
		layout.push<float>(3); // vertex xyz
		layout.push<float>(3); // vertex rgb
		layout.push<float>(3); // vertex nxnynz

		vao->add_buffer(*vertex_buffer, layout);
		index_buffer = std::make_unique<IndexBuffer>(&vertex_indices[0], vertex_indices.size());

		float ratio = 1280 / (float)720; // TODO: Fetch width and height dynamically.
		proj = glm::ortho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);
		view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		shader = std::make_unique<Shader>("shader/default.vert", "shader/default.frag");
	}

	TestObjectRenderer::~TestObjectRenderer()
	{
	}

	void TestObjectRenderer::on_update(float delta)
	{
	}

	void TestObjectRenderer::on_render()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader->bind();

		// Initialize and calculate MVP (model view protection) matrix.
		// Model: translation, rotation and scale of object in space.
		// View: the view of the camera.
		// Projection: the projection matrix of our window

		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::rotate(model, (float)glfwGetTime()*1.5f, glm::vec3(1, 0, 0));
			model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0, 0, 1));

			glm::mat4 mvp = proj * view * model;
			shader->set_uniform_mat4f("MVP", 1, mvp);
			shader->set_uniform_mat4f("model", 1, model);

			renderer.draw(*vao, *index_buffer, *shader);
		}
	}

	void TestObjectRenderer::on_imgui_render()
	{
	}
}