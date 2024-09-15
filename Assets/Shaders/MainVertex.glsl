#version 450 core

layout (location = 0) in vec3 InPos;
layout (location = 1) in vec3 InNormal;
layout (location = 2) in vec2 InUV;

out vec3 Pos;
out vec3 Normal;
out vec2 UV;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main()
{
	UV = InUV;
	Pos = vec3(model * vec4(InPos, 1.0));
	Normal = InNormal;
	gl_Position = proj * view * model * vec4(InPos, 1.0);
}
