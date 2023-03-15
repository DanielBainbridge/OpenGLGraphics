#version 460

out vec4 FragColour;

in vec3 _Colour;

void main()
{
	FragColour = vec4(_Colour, 1);
}
