#version 450 core

out vec4 FragColor;

in VertexData
{
	vec3 Position;
	vec3 Normal;
	vec2 UV;
} In;

struct Material 
{
    sampler2D DiffuseTexture;
    sampler2D SpecularTexture;

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
uniform sampler2D UTexture;
uniform vec3 UCameraPosition;
uniform Material UMaterial;


void main()
{       
    vec3 MaterialDiffuse = vec3(texture2D(UMaterial.DiffuseTexture, In.UV)) * UMaterial.Diffuse;
    vec3 MaterialSpecular = vec3(texture2D(UMaterial.SpecularTexture, In.UV)) * UMaterial.Specular;

    vec3 Normal = normalize(In.Normal);
    vec3 LightDirection = normalize(ULight.Position);

    vec3 Ambient =
          ULight.Ambient 
        * MaterialDiffuse
        ;

    float DiffuseFactor = dot(Normal, LightDirection);
    DiffuseFactor = max(DiffuseFactor, 0.0);
    vec3 Diffuse = DiffuseFactor * MaterialDiffuse * ULight.Diffuse;

    vec3 ViewDirection = normalize(UCameraPosition - In.Position);
    vec3 ReflectDirection = reflect(-LightDirection, Normal);  
    float SpecularFactor = dot(ViewDirection, ReflectDirection);
    SpecularFactor = max(SpecularFactor, 0.0);
    SpecularFactor = pow(SpecularFactor, UMaterial.Shininess);

    vec3 Specular =
        MaterialSpecular * 
        SpecularFactor * 
        ULight.Specular 
        ;  

    vec3 Result = 
            Ambient + 
            Diffuse +
            Specular
        ;

    FragColor = vec4(Result, 1.0);
}
