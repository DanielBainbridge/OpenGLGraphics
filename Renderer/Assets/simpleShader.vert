#version 460

layout (location = 0) in vec4 Position;
layout (location = 1) in vec4 Normal;
layout (location = 2) in vec3 Colour;

uniform mat4 ProjectionMatrix;
uniform mat4 ModelMatrix;

//out vec3 _Colour;
out vec3 _Normal;
out vec4 _Position;

void main()
{
	_Position = ModelMatrix * Position;
	_Normal = (ModelMatrix * Normal).xyz;
	gl_Position = ProjectionMatrix * Position;
	//_Colour = Colour;
}