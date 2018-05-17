#version 330

uniform sampler2D uTexSampler;


in vec2 vTexPos;

out vec4 FragColor;

void main()
{
   int repeat = 5;
   float sheer = 5;
   float tX = fract(fract(floor(vTexPos.y * repeat)/sheer) + fract(vTexPos.x * repeat));
   float tY = fract(vTexPos.y * repeat);

   vec4 Color = texture(uTexSampler, vec2(tX, tY));

   FragColor = vec4(Color);

}
