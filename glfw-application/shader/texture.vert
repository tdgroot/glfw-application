#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vCol;
layout(location = 2) in vec2 texCoord;

out vec3 color;
out vec2 v_TexCoord;

uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(vPos, 1.0);
	color = vCol;
	v_TexCoord = texCoord;
}