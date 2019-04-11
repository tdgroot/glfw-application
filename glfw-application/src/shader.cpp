#include <iostream>

#include "file.h"
#include "shader.h"

Shader::Shader(const std::string& vertex_file_path, const std::string& fragment_file_path)
	: vertex_file_path(vertex_file_path), fragment_file_path(fragment_file_path), renderer_id(0)
{
	renderer_id = create_program();
}

Shader::~Shader()
{
	unbind();
	glDeleteProgram(renderer_id);
}

unsigned int Shader::create_program()
{
	GLuint program = glCreateProgram();

	GLuint vs = compile_shader(vertex_file_path, GL_VERTEX_SHADER);
	GLuint fs = compile_shader(fragment_file_path, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

unsigned int Shader::compile_shader(const std::string& filepath, unsigned int type)
{
	unsigned int id = glCreateShader(type);

	const std::string shader_source = file_get_contents(filepath.c_str());
	const char* shader_source_ptr = shader_source.c_str();

	glShaderSource(id, 1, &shader_source_ptr, NULL);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		printf("Error: failed to compile %s shader:\n", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
		printf("%s \n", message);
		glDeleteShader(id);
		return 0;
	}

	return id;
}

void Shader::bind() const
{
	glUseProgram(renderer_id);
}

void Shader::unbind() const
{
	glUseProgram(0);
}

void Shader::set_uniform1i(const std::string & name, int value)
{
	glUniform1i(get_uniform_location(name), value);
}

void Shader::set_uniform2i(const std::string & name, int v0, int v1)
{
	glUniform2i(get_uniform_location(name), v0, v1);
}

void Shader::set_uniform3f(const std::string& name, float v0, float v1, float v2)
{
	glUniform3f(get_uniform_location(name), v0, v1, v2);
}

void Shader::set_uniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(get_uniform_location(name), v0, v1, v2, v3);
}

void Shader::set_uniform_mat4f(const std::string & name, const unsigned int count, glm::mat4& matrix)
{
	glUniformMatrix4fv(get_uniform_location(name), count, GL_FALSE, &matrix[0][0]);
}

int Shader::get_uniform_location(const std::string& name)
{
	if (uniform_location_cache.find(name) != uniform_location_cache.end())
		return uniform_location_cache[name];

	int location = glGetUniformLocation(renderer_id, name.c_str());

	if (location == -1)
		printf("Warning: %s does not exist!\n", name.c_str());
	else
		printf("Info: fetched location for uniform %s\n", name.c_str());

	uniform_location_cache[name] = location;

	return location;
}