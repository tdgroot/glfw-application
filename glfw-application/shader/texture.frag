#version 330 core

in vec3 color;
in vec2 v_TexCoord;

out vec4 fragColor;

uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	if (texColor.a < 0.5)
		discard;
		
	fragColor =  texColor * vec4(color, 1.0);
}
