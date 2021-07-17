#version 430

layout (location = 0) in vec3 pos;
//layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 aNormal;


//out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;
out vec4 DirectionalLightSpacePos;
out vec4 ViewSpace;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 directionalLightTransform;

void main()
{

	gl_Position = projection * view * model * vec4(pos, 1.0);
	ViewSpace=gl_Position;
	
	DirectionalLightSpacePos 
	= directionalLightTransform * model * vec4(pos, 1.0);
	
	

	//TexCoord = tex;
	
	//calculate normal
	Normal = mat3(transpose(inverse(model))) * aNormal;
	
	//fragment position
	FragPos = (model * vec4(pos, 1.0)).xyz; 
}