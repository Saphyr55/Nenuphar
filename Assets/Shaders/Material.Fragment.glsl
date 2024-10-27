#version 450 core

layout(location = 0) out vec4 FragColor;

in VertexData
{
	vec3 Position;
	vec3 Normal;
	vec2 UV;
} In;

const int MAX_MATERIAL_TEXTURES = 2;

struct Material 
{
    sampler2D Textures[MAX_MATERIAL_TEXTURES];
    int ArraySize;

    vec3 Diffuse;
    vec3 Specular;
    float Shininess;
};

struct Light
{
    vec3 Position;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

uniform Light ULight;
uniform Material UMaterial;

uniform vec3 UCameraPosition;

void main()
{      
    vec3 Ambient = ULight.Ambient;

    vec3 MaterialDiffuse = UMaterial.Diffuse;
    if (UMaterial.ArraySize >= 1)
    {
        vec4 DiffuseTexture = texture(UMaterial.Textures[0], In.UV);
        MaterialDiffuse *= vec3(DiffuseTexture);
        Ambient *= vec3(DiffuseTexture);
    }

    vec3 MaterialSpecular = UMaterial.Specular;
    if (UMaterial.ArraySize >= 2)
    {
        vec4 SpecularTexture = texture(UMaterial.Textures[1], In.UV);
        MaterialSpecular *= vec3(SpecularTexture);
    }

    vec3 Normal = normalize(In.Normal);
    vec3 LightDirection = normalize(ULight.Position - In.Position);

    float DiffuseFactor = dot(Normal, LightDirection);
    DiffuseFactor = max(DiffuseFactor, 0.0);
    vec3 Diffuse = DiffuseFactor * MaterialDiffuse * ULight.Diffuse;

    vec3 ViewDirection = normalize(UCameraPosition - In.Position);
    vec3 HalfwayDirection = normalize(LightDirection + ViewDirection);
    float SpecularFactor = dot(Normal, HalfwayDirection);
    SpecularFactor = max(SpecularFactor, 0.0);
    SpecularFactor = pow(SpecularFactor, UMaterial.Shininess);

    vec3 Specular =
        MaterialSpecular 
        * SpecularFactor 
        * ULight.Specular 
        ; 

    vec3 Result = 
          Ambient 
        + Diffuse
        + Specular
        ;

    FragColor = vec4(Result, 1.0);
}
