#version 330

in vec2 vTexPos;
in float vAlpa;

out vec4 FragColor;

uniform sampler2D uTexture;

void main()
{
    FragColor = texture(uTexture, vTexPos);
    FragColor.a *= vAlpa;
}
