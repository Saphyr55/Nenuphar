#version 450 core

layout (location = 0) in vec3 APosition;
layout (location = 1) in vec3 ANormal;
layout (location = 2) in vec2 AUV;

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
	Out.UV = AUV;
	Out.Position = vec3(UModel * vec4(APosition, 1.0));
	Out.Normal = mat3(transpose(inverse(UModel))) * ANormal;

	gl_Position = 
		  UMainUniformBlock.Projection 
		* UMainUniformBlock.View 
		* UModel
		* vec4(APosition, 1.0);
}
