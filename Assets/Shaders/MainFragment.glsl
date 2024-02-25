#version 450 core

out vec4 FragColor;
in vec2 UV;

uniform sampler2D tex1;

void main() 
{
    FragColor = texture(tex1, UV);
}
