#version 330 core


out vec4 color;

in vec2 TexCoords;
in vec2 vertPos;

uniform sampler2D text;
uniform vec4 mainDiffuseColour;

void main()
{    


    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = mainDiffuseColour*sampled;
	 color.a*= (0.5f+(1-vertPos.y)*0.5f);
	if(color.a>0.97)color.a=0.97;

}  