# version 460

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform sampler2D bloomBlur;
uniform float exposure;

void main()
{             
    const float gamma = 1.0f;
    vec3 hdrColour = texture(screenTexture, TexCoords).rgb;
	vec3 bloomColour = texture(bloomBlur, TexCoords).rgb;
  
	hdrColour += bloomColour;
  
    // exposure tone mapping
    vec3 mapped = vec3(1.0) - exp(-hdrColour * exposure);
    // gamma correction 
    mapped = pow(mapped, vec3(1.0 / gamma));
  
    FragColor = vec4(mapped, 1.0);
}  