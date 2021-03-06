#pragma once

#include "renderer.h"

class Texture
{
private:
	unsigned int renderer_id;
	std::string filepath;
	unsigned char* local_buffer;
	int width, height, bpp;
public:
	Texture(const std::string& filepath);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

	inline int get_width() const { return width;  }
	inline int get_height() const { return height; }
};