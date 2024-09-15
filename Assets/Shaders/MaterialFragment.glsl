#version 450 core

out vec4 FragColor;

in vec3 Position;
in vec3 Normal;
in vec2 UV;

struct Material 
{
    sampler2D DiffuseTexture;
    sampler2D SpecularTexture;

    vec3 Diffuse;
    vec3 Specular;
    float Shininess;
};

struct DirectionalLight
{
    vec3 Position;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

uniform DirectionalLight UDirectionalLight;
uniform sampler2D UTexture;
uniform vec3 UCameraPosition;
uniform Material UMaterial;


void main()
{       
    vec3 MaterialDiffuse = vec3(texture2D(UMaterial.DiffuseTexture, UV));
    vec3 MaterialSpecular = vec3(texture2D(UMaterial.SpecularTexture, UV));

    vec3 Normal = normalize(Normal);
    vec3 LightDirection = normalize(UDirectionalLight.Position - Position);

    vec3 Ambient =
          UDirectionalLight.Ambient 
        * MaterialDiffuse
        ;

    float DiffuseFactor = dot(Normal, LightDirection);
    DiffuseFactor = max(DiffuseFactor, 0.0);
    vec3 Diffuse = DiffuseFactor * MaterialDiffuse * UDirectionalLight.Diffuse;

    vec3 ViewDirection = normalize(UCameraPosition - Position);
    vec3 ReflectDirection = reflect(-LightDirection, Normal);  
    float SpecularFactor = dot(ViewDirection, ReflectDirection);
    SpecularFactor = max(SpecularFactor, 0.0);
    SpecularFactor = pow(SpecularFactor, UMaterial.Shininess);

    vec3 Specular =
        MaterialSpecular * 
        SpecularFactor * 
        UDirectionalLight.Specular 
        ;  

    vec3 Result = 
            Ambient + 
            Diffuse +
            Specular
        ;

    FragColor = vec4(Result, 1.0);
}
