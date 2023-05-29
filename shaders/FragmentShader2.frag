#version 330 core
in vec2 TexCoord;

out vec4 FragColor;
uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;
uniform float mixFactor;


void main()
{
 FragColor = mix(texture(ourTexture, TexCoord), texture(ourTexture2, TexCoord), mixFactor);
}