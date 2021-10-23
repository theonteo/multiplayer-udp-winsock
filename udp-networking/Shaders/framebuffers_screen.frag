#version 430


out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    vec4 px = texture2D(screenTexture,TexCoords);
   
	//gamma correct
	float gamma = 1.23;
    FragColor.rgb = pow(px.rgb, vec3(1.0/gamma));

}