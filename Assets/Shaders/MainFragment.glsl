#version 450 core

out vec4 FragColor;

in vec3 Pos;
in vec3 Normal;
in vec2 UV;

uniform vec4 UColor;
uniform sampler2D UTexture;

void main() 
{
    FragColor = texture2D(UTexture, UV) * UColor;
}
