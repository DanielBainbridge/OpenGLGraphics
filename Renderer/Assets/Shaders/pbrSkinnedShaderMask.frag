#version 460

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 Emission;
in vec2 _TexCoords;
in vec4 _Position;
in vec3 _Normal;
in vec3 _Tangent;
in vec3 _BiTangent;
flat in  ivec4 _BoneID;
in vec4 _Weights;



uniform int numLights;
uniform vec3 CameraPosition;


uniform vec3 AmbientColour; // ambient light colour
uniform vec3 LightColour; // light colour
uniform vec3 LightDirection; // light direction

//Tiling
uniform vec2 Tiling; // tiling value inversed cause artists
uniform vec2 UVOffset; // offset of the UV in coordinates
uniform vec2 NormalTiling;
uniform vec2 NormalUVOffset;
uniform vec2 MaskTiling; // this is because artists suck
uniform vec2 MaskUVOffset; // this is because artists suck
uniform vec2 EmissiveTiling;
uniform vec2 EmissiveUVOffset;
uniform float EmissiveIntensity;

const int MAX_LIGHTS = 4;
uniform vec3 PointLightColour[MAX_LIGHTS];
uniform vec3 PointLightPosition[MAX_LIGHTS];

uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D maskMap;
uniform sampler2D emissiveMap;

uniform int DisplayBoneIndex;


const float PI = 3.14159265359;

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
	return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0,1.0),5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
	float a = roughness * roughness;
	float a2 = a * a;
	float NdotH = max(dot(N,H), 0.0);
	float NdotH2 = NdotH * NdotH;
	
	float numerator = a2;
	float denomenator = (NdotH2 * (a2 - 1.0) + 1.0);
	denomenator = PI * denomenator * denomenator;
	
	return numerator / denomenator;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
	float r = (roughness + 1.0);
	float k = (r * r) / 8.0;
	
	float numerator = NdotV;
	float denomenator = NdotV * (1.0 - k) + k;
	return numerator / denomenator;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
	float NdotV = max(dot(N,V), 0.0);
	float NdotL = max(dot(N,L), 0.0);
	float ggx2 = GeometrySchlickGGX(NdotV, roughness);
	float ggx1 = GeometrySchlickGGX(NdotL, roughness);
	return ggx1 * ggx2;
}


void main()
{

	vec3 albedo = pow(texture(albedoMap, (_TexCoords * Tiling) + UVOffset).rgb, vec3(2.2));	
	vec3 normal = texture(normalMap, (_TexCoords * NormalTiling) + NormalUVOffset).rgb;
	float metallic = texture(maskMap, (_TexCoords * MaskTiling) + MaskUVOffset).r;	
	float ao = texture(maskMap, (_TexCoords * MaskTiling) + MaskUVOffset).g;
	float roughness = texture(maskMap, (_TexCoords * MaskTiling) + MaskUVOffset).b;
	
	vec3 emissive = texture(emissiveMap, (_TexCoords * EmissiveTiling) + EmissiveUVOffset).rgb;
	
	
	vec3 N = normalize(_Normal);
	vec3 V = (normalize(CameraPosition - _Position.xyz));
	

	vec3 Lo = vec3(0.0);
	
	
	{
		vec3 L = normalize(LightDirection);
		vec3 H = normalize(V + L);
		
		vec3 radiance = LightColour;
		
		vec3 F0 = vec3(0.04);
		F0 = mix(F0, albedo, metallic);
		vec3 F = fresnelSchlick(max(dot(H,V), 0.0), F0);
		
		float G = GeometrySmith(N, V, L, roughness);
		
		vec3 numerator = G * F;
		float denomenator = 4.0 * max(dot(N,V), 0.0) + 0.0001;
		vec3 specular = numerator / denomenator;
		
		vec3 kS = F;
		vec3 kD = vec3(1.0) - kS;
		
		kD *= 1.0 - metallic;
		
		float NdotL = max(dot(N,L), 0.0);
		Lo += (kD * albedo / PI + specular) * radiance * NdotL;	
	}
	
	
	//reflectance loop
	for(int i = 0; i < numLights; i++)
	{
		vec3 L = normalize(PointLightPosition[i] - _Position.xyz);
		vec3 H = normalize(V + L);
		
		float distance = length(PointLightPosition[i] - _Position.xyz);
		float attenuation = 1.0 / (distance * distance);
		vec3 radiance = PointLightColour[i] * attenuation;
		
		vec3 F0 = vec3(0.04);
		F0 = mix(F0, albedo, metallic);
		vec3 F = fresnelSchlick(max(dot(H,V), 0.0), F0);
		
		float NDF = DistributionGGX(N, H, roughness);
		float G = GeometrySmith(N, V, L, roughness);
		
		vec3 numerator = NDF * G * F;
		float denomenator = 4.0 * max(dot(N,V), 0.0) + 0.0001;
		vec3 specular = numerator / denomenator;
		
		vec3 kS = F;
		vec3 kD = vec3(1.0) - kS;
		
		kD *= 1.0 - metallic;
		
		float NdotL = max(dot(N,L), 0.0);
		Lo += (kD * albedo / PI + specular) * radiance * NdotL;		
	}	
	
	vec3 ambient = vec3(0.03) * albedo * ao;
	vec3 color = ambient * Lo;
	
	color = color / (color + vec3(1.0));
	color = pow(color, vec3(1.0/2.2));	
	
	FragColor = vec4(color, 1.0) + (vec4(emissive, 1.0) * EmissiveIntensity);
}