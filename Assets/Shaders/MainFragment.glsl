#version 450 core

out vec4 FragColor;


in vec3 Pos;
in vec3 Normal;
in vec2 UV;

uniform vec4 UColor;
uniform bool UIsTextured;
uniform sampler2D UTex;

void main() 
{
    if (UIsTextured)
    {
        FragColor = texture(UTex, UV);
    }
    else
    {
        FragColor = UColor;
    }
}
