#pragma once

#include "indexbuffer.h"
#include "shader.h"
#include "vertex.h"
#include "vertexarray.h"
#include "vertexbuffer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <string>

class Model
{
private:
	VertexArray* vao;
	Shader* shader;

	std::unique_ptr<IndexBuffer> index_buffer;
	std::unique_ptr<VertexBuffer> vertex_buffer;
	std::unique_ptr<glm::mat4> model;
public:
	Model(VertexArray* vao, Shader* shader, std::string modelName);
	~Model();
};
