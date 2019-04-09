#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vCol;
layout(location = 2) in vec3 normal;

out vec3 color;
out vec3 v_FragPos;
out vec2 v_TexCoord;
out vec3 v_Normal;

uniform mat4 MVP;
uniform mat4 model;

void main()
{
	gl_Position = MVP * vec4(vPos, 1.0);
	v_FragPos = vec3(MVP * vec4(vPos, 1.0));
	color = vCol;
	//v_TexCoord = texCoord;
	v_Normal = mat3(transpose(inverse(MVP))) * normal;
}