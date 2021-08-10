#version 430


layout (location = 0) in vec3 vVertexPosition;

uniform mat4 projection;

uniform mat4 model;

uniform mat4 view;

void main() 
{
	gl_Position = projection* view * model * vec4( vVertexPosition, 1.0);
}