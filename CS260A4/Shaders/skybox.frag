#version 430

in vec3 TexCoords;

out vec4 colour;

uniform samplerCube skybox;

void main()
{

vec4 finalColour=texture(skybox, TexCoords);

  float average = (finalColour.r + finalColour.g + finalColour.b) / 3.0;
    vec4 FragColor = vec4(average, average, average, 1.0)+vec4(0.5,0.5,0.5,0);
	
	
colour=finalColour/16.0;
	//colour = FragColor;
}