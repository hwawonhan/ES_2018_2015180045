#version 330

in vec2 vTexPos;

out vec4 FragColor;

uniform float uTime;

uniform sampler2D uTexSampler;

void main()
{
    //vec2 newTexPos = vec2(vTexPos.x, uTime/6.0 + vTexPos.y/6.0);
    //FragColor = texture(uTexSampler, newTexPos);
    vec2 newTexPos = vec2(fract(vTexPos.x * 2), vTexPos.y/2.0);
    FragColor = texture(uTexSampler, newTexPos);
}
