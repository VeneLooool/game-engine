#version 330 core
out vec4 FragColor;	

struct Material {
   sampler2D diffuse;
   sampler2D specular;
   float shininess;   
};

struct DirLight {
   vec3 direction;
 
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

struct PointLight{
   vec3 position;

   float constant;
   float linear;
   float quadratic;
 
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

struct SpotLight {
   vec3 position;
   vec3 direction; 
   float cutOff;
   float outerCutOff;

   float constant;
   float linear;
   float quadratic;
 
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};
#define NR_POINT_LIGHTS 1

//in vec3 FragPos;
//in vec3 Normal;
//in vec2 TexCoords;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform vec3 lightPos;

uniform Material material;
uniform sampler2D shadowMap;
uniform PointLight pointLight[NR_POINT_LIGHTS];
uniform vec3 viewPos;
uniform DirLight dirLight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, fs_in.TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, fs_in.TexCoords));
    vec3 specular = spec * light.specular * vec3(texture(material.specular, fs_in.TexCoords));
    return(ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 halfDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfDir), 0.0), material.shininess);
	
    //vec3 reflectDir = reflect(-lightDir, normal);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, fs_in.TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, fs_in.TexCoords));
    vec3 specular = spec * light.specular * vec3(texture(material.specular, fs_in.TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return(ambient + diffuse + specular);
}

float ShadowCalculation(vec4 fragPosLightSpace)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    projCoords = projCoords * 0.5 + 0.5;

    float closestDepth = texture(shadowMap, projCoords.xy).r; 

    float currentDepth = projCoords.z;

    vec3 normal = normalize(fs_in.Normal);
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}

void main()
{
    vec3 norm = normalize(fs_in.Normal);
    vec3 viewDir  = normalize(viewPos - fs_in.FragPos);

    vec3 result = CalcDirLight(dirLight, norm, viewDir);

    for(int i=0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLight[i], norm, fs_in.FragPos, viewDir);

    float shadow = ShadowCalculation(fs_in.FragPosLightSpace);                      
    vec3 lighting = (pointLight[0].ambient + (1.0 - shadow) * (pointLight[0].diffuse + pointLight[0].specular)) * result;  

    FragColor = vec4(lighting, 1.0f);
}