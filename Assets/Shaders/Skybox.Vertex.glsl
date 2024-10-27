#version 450 core

layout (location = 0) in vec3 APosition;
layout (location = 1) in vec3 ANormal;
layout (location = 2) in vec2 AUV;

out vec3 UVW;

layout(std140, binding = 0) uniform MainUniformBlock 
{
	mat4 Projection;
	mat4 View;
} UMainUniformBlock;

void main()
{	
	UVW = vec3(APosition.xy, APosition.z);

	vec4 Position = 
		  UMainUniformBlock.Projection 
		* mat4(mat3(UMainUniformBlock.View))
		* vec4(APosition, 1.0);

	gl_Position = Position.xyww;
}
