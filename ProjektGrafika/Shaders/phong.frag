#version 400
#define MAX_LIGHTS 5

in vec4 worldPosition;
in vec3 normalVector;

out vec4 fragColor;

struct Light
{
    vec3 position;
    vec3 direction;
    float cutoff;
    vec3 lightColor;
    int lightType;
};

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material material;
uniform Light lights[MAX_LIGHTS];
uniform int lightCount;
uniform vec3 cameraPosition;
//uniform vec3 lightPosition;
//uniform vec3 lightColor;
uniform vec3 objectColor;

vec3 pointLight(Material material, vec4 worldPosition, vec3 normalVector, vec3 lightPosition, vec3 lightColor);
vec3 spotlight(vec3 color, vec3 worldPos, vec3 normalVector, vec3 lightPosition, vec3 lightDirection, vec3 lightColor, float cutoff);
vec3 directional_light(vec3 color, vec3 worldPos, vec3 normalVector, vec3 lightDirection, vec3 lightColor);

void main()
{
	vec3 result = vec3(0.0, 0.0, 0.0);
	//Ambient part
	vec3 ambient = material.ambient * vec3(0.1, 0.1, 0.1);
	for(int i = 0;i<lightCount;i++)
	{
		result += (pointLight(material, worldPosition, normalVector, lights[i].position, lights[i].lightColor)) * objectColor;
	}
	
	fragColor = vec4(ambient + result,1.0);
}

vec3 pointLight(Material material,vec4 worldPosition, vec3 normalVector, vec3 lightPosition, vec3 lightColor)
{
	vec3 norm = normalize(normalVector);
	vec3 lightDir = normalize(lightPosition - worldPosition.xyz/worldPosition.w);
	float diff = max(dot(lightDir, norm), 0.0);
	vec3 diffuse =  lightColor * material.diffuse * diff;

	vec3 viewDir = normalize(cameraPosition - worldPosition.xyz/worldPosition.w);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
	float specularStrength = 0.5;
	vec3 specular = lightColor * material.specular * specularStrength * spec;
	if (diff <= 0.0)
	{
		specular = vec3(0.0);
	}

	float distance = length(lightPosition - worldPosition.xyz/worldPosition.w);
	float attenuation = 1.0 / (1.0 + 0.045 * distance + 0.0075 * (distance * distance));//constant, linear, quadratic costants in this order, for now for 100 distance

	return (diffuse + specular) * attenuation;
}

vec3 spotlight(vec3 color, vec3 worldPos, vec3 normalVector, vec3 lightPosition, vec3 lightDirection, vec3 lightColor, float cutoff)
{
	return vec3(1.0,1.0,1.0);
}

vec3 directional_light(vec3 color, vec3 worldPos, vec3 normalVector, vec3 lightDirection, vec3 lightColor)
{
	return vec3(1.0,1.0,1.0);
}