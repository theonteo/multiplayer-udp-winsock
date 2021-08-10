#version 330 core


out vec4 color;

in vec2 TexCoords;

uniform sampler2D theTexture;
uniform vec4 diffuseColour;

void main()
{    
	color = texture(theTexture,TexCoords);
	if(color.a<0.5f) discard;
	color *= diffuseColour;
}  