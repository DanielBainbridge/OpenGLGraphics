#version 460



//in vec3 _Colour;
in vec3 _Normal;
in vec4 _Position;
in _TexCoords;

uniform vec3 CameraPosition;

uniform vec3 AmbientColour; // ambient light colour
uniform vec3 LightColour; // light colour
uniform vec3 LightDirection; // light direction

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float SpecularPower;

uniform sampler2D diffuseTex;




out vec4 FragColour;

void main()
{
	vec3 N = normalize(_Normal);
	vec3 L = normalize(LightDirection);
	
	//calc lambert term
	float lambertTerm = max(0, min(1, dot(N, -L)));
	
	//calc view + reflection vector
	vec3 V = normalize(CameraPosition - _Position.xyz);
	vec3 R = reflect(L,N);
	
	//calc specular term
	float specularTerm = pow(max(0, dot(R,V)), SpecularPower);
	
	vec3 textureColour = texture(diffuseTex, _TexCoords).rgb;
	
	//calc diffuse
	vec3 diffuse = LightColour * Kd * lambertTerm * textureColour;
	vec3 ambient = AmbientColour * Ka * textureColour;
	vec3 specular = LightColour * Ks * specularTerm;
	
	FragColour = vec4(diffuse + ambient + specular, 1);
}
