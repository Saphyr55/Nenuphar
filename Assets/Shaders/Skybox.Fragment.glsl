#version 450 core

layout(location = 0) out vec4 FragColor;

layout(location = 0) in vec3 UVW;

uniform samplerCube USkybox;

void main()
{             
    FragColor = texture(USkybox, UVW);
}  