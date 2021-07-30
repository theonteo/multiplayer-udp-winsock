#version 430

//get from vertex shader
in vec4 vCol;

//tex coord next time
//in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 DirectionalLightSpacePos;
in vec4 ViewSpace;

//output
out vec4 colour;

//max lights
const int MAX_POINT_LIGHTS = 4;
const int MAX_SPOT_LIGHTS = 3;

//all structs
struct Light
{
	vec3 colour;
	float ambientIntensity;
	float diffuseIntensity;
};

struct DirectionalLight 
{
	Light base;
	vec3 direction;
};

struct PointLight
{
	Light base;
	vec3 position;
	float constant;
	float linear;
	float exponent;
};

struct SpotLight
{
	PointLight base;
	vec3 direction;
	float edge;
};

struct Material
{
	float specularIntensity;
	float shininess;
};

//material properties
uniform Material material;

//light count
uniform int pointLightCount;
uniform int spotLightCount;


//all lights
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

//diffuse colour
uniform vec3 diffuseColour;

//diffuse texture
uniform sampler2D theTexture;

//shadow map texture
uniform sampler2D directionalShadowMap;

//cubemap texture
uniform samplerCube theTextureCubeMap;

//eye position
uniform vec3 eyePosition;


//calculate shadow value of directional light
float CalcDirectionalShadowFactor(DirectionalLight light)
{

	vec3 projCoords = 
	(DirectionalLightSpacePos.xyz / DirectionalLightSpacePos.w)* 0.5+0.5;
	
	//calculate bias
	float bias = 
	max(0.0005 * (1.0 - dot(normalize(Normal), 
	normalize(directionalLight.direction))), 0.0005);

	vec2 texelSize = 1.0 / textureSize(directionalShadowMap, 0);
	
	
	//accumulate shadow value - pcf
	float shadow = 0.0;
	for(int x = -1; x <= 1; ++x)
	{
		for(int y = -1; y <= 1; ++y)
		{
			float pcfDepth = 
			texture(directionalShadowMap,
			projCoords.xy + vec2(x,y) * texelSize).r;
			
			shadow += projCoords.z - bias > pcfDepth ? 1.0 : 0.0;
		}
	}
	//divide by the total loop num
	shadow /= 9.0;
	
	if(projCoords.z > 1.0)
		shadow = 0.0;

	return shadow;
}

//calculate diffuse / ambient / specular / reflection
vec4 CalcLightByDirection(Light light, vec3 direction, float shadowFactor)
{
	vec3 I = normalize(FragPos- eyePosition);
	vec3 R = reflect(I, normalize(Normal));
	
	//cubemap value
	vec4 cubemapcolor = vec4(texture(theTextureCubeMap, R).rgb, 1.0) * 0.05;

	//ambient value
	vec4 ambientColour = vec4(diffuseColour,1.0f) * vec4(light.colour, 1.0f) * light.ambientIntensity;
	
	//diffuse value
	float diffuseFactor = 
	max(dot(normalize(Normal), normalize(direction)), 0.0f);
	
	vec4 diffuseColour = 
	vec4(diffuseColour,1.0f) * vec4(light.colour * light.diffuseIntensity * diffuseFactor, 1.0f);
	
	vec4 specularColour = vec4(0, 0, 0, 0);
	
	if(diffuseFactor > 0.0f)
	{
		//specular value
		vec3 fragToEye = normalize(eyePosition - FragPos);
		vec3 reflectedVertex = normalize(reflect(direction, normalize(Normal)));
		
		float specularFactor = dot(fragToEye, reflectedVertex);
		if(specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor, material.shininess);
			
			specularColour = vec4(light.colour *
			material.specularIntensity * specularFactor, 1.0f);
		}
	}
	
	//final output
	return (ambientColour + (1.0 - shadowFactor) 
	* (diffuseColour + specularColour + cubemapcolor));
}

vec4 CalcDirectionalLight()
{
	float shadowFactor = CalcDirectionalShadowFactor(directionalLight);
	return CalcLightByDirection
	(directionalLight.base, directionalLight.direction, shadowFactor);
}

vec4 CalcPointLight(PointLight pLight)
{
	vec3 direction = FragPos - pLight.position;
	float distance = length(direction);
	
	direction = normalize(direction);
	
	vec4 colour = CalcLightByDirection(pLight.base, direction, 0.0f);
	
	//point light attenuation
	float attenuation = pLight.exponent * distance * distance +
						pLight.linear * distance +
						pLight.constant;
	
	return (colour / attenuation);
}

vec4 CalcSpotLight(SpotLight sLight)
{
	vec3 rayDirection = normalize(FragPos - sLight.base.position);
	float slFactor = dot(rayDirection, sLight.direction);
	
	//within spotlight angle
	if(slFactor > sLight.edge)
	{
		//uses point light attenuation
		vec4 colour = CalcPointLight(sLight.base);
		
		
		return colour * (1.0f - (1.0f - slFactor)*(1.0f/(1.0f - sLight.edge)));
		
	} else {
		return vec4(0, 0, 0, 0);
	}
}

//loop point light counts
vec4 CalcPointLights()
{
	vec4 totalColour = vec4(0, 0, 0, 0);
	for(int i = 0; i < pointLightCount; i++)
	{		
		totalColour += CalcPointLight(pointLights[i]);
	}
	
	return totalColour;
}

//loop spotlight counts
vec4 CalcSpotLights()
{
	vec4 totalColour = vec4(0, 0, 0, 0);
	for(int i = 0; i < spotLightCount; i++)	
		totalColour += CalcSpotLight(spotLights[i]);
	
	return totalColour;
}

void main()
{
	
	vec4 finalColour = CalcDirectionalLight();
	finalColour += CalcPointLights();
	finalColour += CalcSpotLights();
	
	//texture next time
	//vec4 texDiffuse = texture(theTexture, TexCoord) ;
	//vec4 outputColour= texDiffuse *finalColour;
	
	//final output
	colour =  finalColour;
}