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

const int MAX_LIGHTS = 4;
uniform int numLights;
uniform vec3 PointLightColour[MAX_LIGHTS];
uniform vec3 PointLightPosition[MAX_LIGHTS];

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float SpecularPower;

uniform sampler2D diffuseTex;
uniform sampler2D specularTex;
uniform sampler2D normalTex;

out vec4 FragColour;

vec3 GetDiffuse(vec3 direction, vec3 colour, vec3 normal){
	return colour * max(0, dot(normal, -direction));
}
vec3 GetSpecular(vec3 direction, vec3 colour, vec3 normal, vec3 view){
	vec3 R = reflect(direction,normal);
	float specularTerm = pow(max(0,dot(R, view)), specularPower);
	if(dot(direction, normal) > 0){
		specularTerm = 0.0;
	}
	return specularTerm * colour;
}

void main()
{
	vec3 N = normalize(_Normal);
	vec3 T = normalize(_Tangent);
	vec3 B = normalize(_BiTangent);
	vec3 L = normalize(LightDirection);
	
	mat3 TBN = mat3(T,B,N);
	vec3 textureNormal = texture(normalTex, _TexCoords).rgb;
	N = TBN * (textureNormal * 2 - 1);
	
	//calc total diffuse
	vec3 diffuseTotal = GetDiffuse(L, LightColour, N);
	
	//calc total specular
	vec3 specularTotal = GetSpecular(L, LightColour, N, V)
	
	for(int i = 0; i < numLights; i++){
		vec3 direction = _Position - PointLightPosition[i];
		float distance = length(direction);
		direction = direction / distance;
		
		// attenuate the light intensity with inverse square law
		vec3 colour = PointLightColour[i]/(distance * distance);
		diffuseTotal += GetDiffuse(direction, colour, N);
		specularTotal += GetSpecular(direction, colour, N, V);
	}


	vec3 textureDiffuse = texture(diffuseTex, _TexCoords).rgb;
	vec3 textureSpecular = texture(specularTex, _TexCoords).rgb;
		
	//calculate lighting	
	vec3 diffuse = Kd * diffuseTotal * textureDiffuse;
	vec3 ambient = AmbientColour * Ka * textureDiffuse;
	vec3 specular = LightColour * Ks * specularTotal;
	
	FragColour = vec4(diffuse + ambient + specular, 1)  * (N,1);
}
