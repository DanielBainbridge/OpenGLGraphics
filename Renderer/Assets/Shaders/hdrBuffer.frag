# version 460

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

uniform float exposure;

void main()
{             
    const float gamma = 2.2f;
    vec3 hdrColour = texture(screenTexture, TexCoords).rgb;
  
    // exposure tone mapping
    vec3 mapped = vec3(1.0) - exp(-hdrColour * exposure);
    // gamma correction 
    mapped = pow(mapped, vec3(1.0 / gamma));
  
    FragColor = vec4(mapped, 1.0);
}  