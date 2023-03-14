#version 450

layout (location = 0) in vec2 Position;

uniform float setFloat;

void main()
{
	gl_Position = vec4(Position * 0.25 + (setFloat / 2.0), 0, 1);
}