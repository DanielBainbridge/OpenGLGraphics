#version 460

layout (location = 0) in vec4 Position;
layout (location = 1) in vec4 Normal;
layout (location = 2) in vec2 TexCoords;
layout (location = 3) in vec4 Tangent;
layout (location = 4) in ivec4 BoneID;
layout (location = 5) in vec4 Weights

uniform mat4 ProjectionMatrix;
uniform mat4 ModelMatrix;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 6;
uniform mat4 FinalBonesMatrices[MAX_BONES];


out vec3 _Normal;
out vec4 _Position;
out vec2 _TexCoords;
out vec3 _Tangent;
out vec3 _BiTangent;


void main()
{

	vec4 totalPosition = vec4(0.0f);
	
	for(int i = 0; i < MAX_BONE_INFLUENCE; i++)
	{
		if(BoneID[i] == -1)
		{
			continue;
		}
		if(BoneID[i] >= MAX_BONES)
		{
			totalPosition = Position;
			break;
		}
		vec4 localPosition = FinalBonesMatrices[BoneID[i]] * Position;
		totalPosition += localPosition * Weights[i];
		vec3 localNormal = mat3(FinalBonesMatrices[BoneID[i]]) * Normal;
	}

	_Position = ModelMatrix * Position;
	_Normal = (ModelMatrix * Normal).xyz;
	_TexCoords = TexCoords;
	_Tangent = (ModelMatrix * vec4(Tangent.xyz,0)).xyz;
	_BiTangent = cross(_Normal, _Tangent) * Tangent.w;
	gl_Position = ProjectionMatrix * totalPosition;
}