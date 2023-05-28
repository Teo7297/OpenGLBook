#version 330 core
in vec4 vertexColor;
in vec4 vertexPosition;
in vec2 TexCoord;

out vec4 FragColor;
uniform vec4 uniformColor;
uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;


void main()
{
 //FragColor = vertexColor;
 //FragColor = vertexPosition;
 //FragColor = texture(ourTexture2, TexCoord);// * vertexColor;
 FragColor = mix(texture(ourTexture, TexCoord), texture(ourTexture2, TexCoord), 0.2f);
}