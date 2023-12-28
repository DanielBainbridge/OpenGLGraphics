#version 460

layout (location = 0) in vec4 Position;
layout (location = 1) in vec4 Normal;
layout (location = 2) in vec2 TexCoords;
layout (location = 3) in vec4 Tangent;

uniform mat4 ProjectionMatrix;
uniform mat4 ModelMatrix;


out vec3 _Normal;
out vec4 _Position;
out vec2 _TexCoords;
out vec3 _Tangent;
out vec3 _BiTangent;


void main()
{
	_Position = ModelMatrix * Position;
	_Normal = (ModelMatrix * Normal).xyz;
	_TexCoords = TexCoords;
	_Tangent = (ModelMatrix * vec4(Tangent.xyz,0)).xyz;
	_BiTangent = cross(_Normal, _Tangent) * Tangent.w;
	gl_Position = ProjectionMatrix * Position;
}