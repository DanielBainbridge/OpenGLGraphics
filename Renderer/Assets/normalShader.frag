#version 460



//in vec3 _Colour;
in vec3 _Normal;
in vec4 _Position;
in vec2 _TexCoords;
in vec3 _Tangent;
in vec3 _BiTangent;

uniform vec3 CameraPosition;

uniform vec3 AmbientColour; // ambient light colour
uniform vec3 LightColour; // light colour
uniform vec3 LightDirection; // light direction

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float SpecularPower;

uniform sampler2D diffuseTex;
uniform sampler2D specularTex;
uniform sampler2D normalTex;




out vec4 FragColour;

void main()
{
	vec3 N = normalize(_Normal);
	vec3 T = normalize(_Tangent);
	vec3 B = normalize(_BiTangent);
	vec3 L = normalize(LightDirection);
	
	mat3 TBN = mat3(T,B,N);
	vec3 textureNormal = texture(normalTex, _TexCoords).rgb;
	N = TBN * (textureNormal * 2 - 1);
	
	//calc lambert term
	float lambertTerm = max(0, min(1, dot(N, -L)));
	
	//calc view + reflection vector
	vec3 V = normalize(CameraPosition - _Position.xyz);
	vec3 R = reflect(L,N);
	float debugVal = 1.0;

	//calc specular term
	float specularTerm = pow(max(0, dot(R,V)), SpecularPower);
	
	vec3 textureDiffuse = texture(diffuseTex, _TexCoords).rgb;
	vec3 textureSpecular = texture(specularTex, _TexCoords).rgb;
	
	
	if(dot(L,N) > 0){
		specularTerm = 0.0;
	}
	
	
	//calc diffuse
	vec3 diffuse = LightColour * Kd * lambertTerm * textureDiffuse;
	vec3 ambient = AmbientColour * Ka * textureDiffuse;
	vec3 specular = LightColour * Ks * specularTerm;
	
	FragColour = vec4(diffuse + ambient + specular, 1)  * (N,1);
}
