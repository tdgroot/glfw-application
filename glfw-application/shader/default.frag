#version 330 core

in vec3 color;
in vec3 v_FragPos;
in vec2 v_TexCoord;
in vec3 v_Normal;

out vec4 fragColor;

uniform sampler2D u_Texture;
uniform vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

void main()
{
	vec3 lightPos = vec3(1.0, 5.0, -5.0);
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(lightPos - v_FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = diff * vec4(1.0, 1.0, 1.0, 1.0);
	fragColor = (ambient + diffuse) * vec4(color, 1.0);
}
