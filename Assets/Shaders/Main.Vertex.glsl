#version 450 core

layout (location = 0) in vec3 InPosition;
layout (location = 1) in vec3 InNormal;
layout (location = 2) in vec2 InUV;

out VertexData
{
	vec3 Position;
	vec3 Normal;
	vec2 UV;
} Out;

layout(std140, binding = 0) uniform MainUniformBlock 
{
	mat4 Projection;
	mat4 View;
} UMainUniformBlock;

uniform mat4 UModel;

void main()
{
	Out.UV = InUV;
	Out.Position = vec3(UModel * vec4(InPosition, 1.0));
	Out.Normal = InNormal;
	
	gl_Position = 
		  UMainUniformBlock.Projection 
		* UMainUniformBlock.View 
		* UModel
		* vec4(InPosition, 1.0);
}
