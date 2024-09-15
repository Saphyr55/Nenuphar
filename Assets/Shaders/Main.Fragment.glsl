#version 450 core

out vec4 FragColor;

in VertexData
{
	vec3 Position;
	vec3 Normal;
	vec2 UV;
} In;

void main()
{       
    FragColor = vec4(0.0);
}
