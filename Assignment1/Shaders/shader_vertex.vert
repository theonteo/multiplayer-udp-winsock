#version 430

layout (location = 0) in vec3 pos;
layout (location = 2) in vec3 aNormal;

//return vertex colour
out vec4 vCol;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

const int MAX_POINT_LIGHTS = 3;

//all structs
struct Light
{
	vec3 colour;
	float ambientIntensity;
	float diffuseIntensity;
};


struct PointLight
{
	Light base;
	vec3 position;
	float constant;
	float linear;
	float exponent;
};

struct DirectionalLight 
{
	Light base;
	vec3 direction;
};

//light count
uniform int pointLightCount;

//all lights
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];


//calculate diffuse 
vec4 CalcLightByDirection(Light light, vec3 direction)
{

	//calculate normal
	vec3 Normal = mat3(transpose(inverse(model))) * aNormal;
	
	
	//calculate ambient
	vec4 ambientColour = vec4(light.colour, 1.0f) * light.ambientIntensity;
	
	
	//calculate diffuse
	float diffuseFactor = 
	max(dot(normalize(Normal), normalize(direction)), 0.0f);
	
	vec4 diffuseColour = 
	vec4(light.colour * light.diffuseIntensity * diffuseFactor, 1.0f);

	//final output
	return (ambientColour  * (diffuseColour));
}

//calculate directional light value
vec4 CalcDirectionalLight()
{
	return CalcLightByDirection
	(directionalLight.base, directionalLight.direction);
}

//calculate point light value
vec4 CalcPointLight(PointLight pLight)
{
	vec3 direction =  (model * vec4(pos, 1.0)).xyz - pLight.position;
	float distance = length(direction);
	direction = normalize(direction);
	
	vec4 colour = CalcLightByDirection(pLight.base, direction);
	float attenuation = pLight.exponent * distance * distance +
						pLight.linear * distance +
						pLight.constant;
	
	return (colour / attenuation);
}

//loop through all point lights
vec4 CalcPointLights()
{
	vec4 totalColour = vec4(0, 0, 0, 0);
	for(int i = 0; i < pointLightCount; i++)
	{		
		totalColour += CalcPointLight(pointLights[i]);
	}
	
	return totalColour;
}

void main()
{
	vec4 finalColour = CalcDirectionalLight();
	
	finalColour += CalcPointLights();
	finalColour *= 10.0;
	
	gl_Position = projection * view * model * vec4(pos, 1.0);

	//final vertex colour
	vCol = finalColour;
	
}