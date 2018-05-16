#version 330

uniform sampler2D uTexSampler;


in vec2 vTexPos;

out vec4 FragColor;

void main()
{
   float tX = fract(vTexPos.x * 3);
   float tY = fract(vTexPos.y * 3);

   vec4 Color = texture(uTexSampler, vec2(tX, tY)).bgra;

   FragColor = vec4(Color);

}
