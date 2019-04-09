#pragma once

#include <glad/glad.h>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader
{
private:
	std::string vertex_file_path;
	std::string fragment_file_path;
	unsigned int renderer_id;
	std::unordered_map<std::string, int> uniform_location_cache;
public:
	Shader(const std::string& vertex_file_path, const std::string& fragment_file_path);
	~Shader();
	
	void bind() const;
	void unbind() const;

	void set_uniform1i(const std::string& name, int value);
	void set_uniform2i(const std::string& name, int v0, int v1);
	void set_uniform3f(const std::string& name, float v0, float v1, float v2);
	void set_uniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void set_uniform_mat4f(const std::string& name, const unsigned int count, glm::mat4& matrix);
private:
	unsigned int create_program();
	unsigned int compile_shader(const std::string& filepath, unsigned int type);
	int get_uniform_location(const std::string& name);
};