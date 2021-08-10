#version 330 core


out vec4 color;

in vec2 TexCoords;

uniform sampler2D text;
uniform vec4 diffuseColour;

void main()
{    


    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = diffuseColour*sampled;
	
	if(color.a>0.97)color.a=0.97;

}  