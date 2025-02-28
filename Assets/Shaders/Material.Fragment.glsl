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

struct DirectionalLight
{
    vec3 Direction;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

// struct Skybox
// {
//     samplerCube SkyboxSampler;
//     bool IsTexture;
// };

// uniform Skybox USkybox;

uniform Material UMaterial;
uniform DirectionalLight UDirectionalLight;

uniform vec3 UCameraPosition;

vec4 DirectionalLightIntensity(DirectionalLight Light, vec3 Normal) 
{
    vec4 Ambient = vec4(Light.Ambient, 1.0);
    
    vec4 MaterialDiffuse = vec4(UMaterial.Diffuse, 1.0);
    if (UMaterial.ArraySize >= 1)
    {
        vec4 DiffuseTexture = texture(UMaterial.Textures[0], In.UV);
        MaterialDiffuse *= DiffuseTexture;
        Ambient *= DiffuseTexture;
        Ambient.a = DiffuseTexture.a;
    }

    vec3 MaterialSpecular = UMaterial.Specular;
    if (UMaterial.ArraySize >= 2)
    {
        vec4 SpecularTexture = texture(UMaterial.Textures[1], In.UV);
        MaterialSpecular *= vec3(SpecularTexture);
    }

    vec3 LightDirection = normalize(Light.Direction);
    
    float DiffuseFactor = dot(Normal, - LightDirection);
    DiffuseFactor = max(DiffuseFactor, 0.0);
    vec3 Diffuse = DiffuseFactor * vec3(MaterialDiffuse) * Light.Diffuse;
    
    vec3 ViewDirection = normalize(UCameraPosition - In.Position);
    vec3 HalfwayDirection = normalize(- LightDirection + ViewDirection);
    float SpecularFactor = dot(Normal, HalfwayDirection);
    SpecularFactor = max(SpecularFactor, 0.0);
    SpecularFactor = pow(SpecularFactor, UMaterial.Shininess);

    vec3 Specular = MaterialSpecular * SpecularFactor * Light.Specular; 

    vec4 Result = Ambient + vec4(Diffuse, 0.0) + vec4(Specular, 0.0);

    return Result;
}

void main()
{      
    vec3 Normal = normalize(In.Normal);
    vec4 Result = DirectionalLightIntensity(UDirectionalLight, Normal);
    
    // if (USkybox.IsTexture)
    // {   
    //     vec3 I = normalize(In.Position - UCameraPosition);
    //     vec3 R = reflect(I, Normal);
    //     Result *= texture(USkybox.SkyboxSampler, R).rgb;
    // }

    FragColor = Result;
}
