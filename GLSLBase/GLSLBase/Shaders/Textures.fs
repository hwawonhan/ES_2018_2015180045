#version 330

uniform sampler2D uTexSampler;
uniform sampler2D uTexSampler1;
uniform float u_Time;

in vec2 vTexPos;

out vec4 FragColor;

void main()
{
   float tX = vTexPos.x;
   float tY = vTexPos.y;

   float grayScale = abs(sin(tY * 200 + u_Time));
  
   vec3 Color = texture(uTexSampler, vec2(tX, tY)).bgr;
   vec3 Color1 = texture(uTexSampler1, vec2(tX, tY)).bgr;

   float newX = tX * 2 * 3.141592;
   float newY = tY * 2 - 1;

   if(sin(newX) > newY)
   {
        FragColor = vec4(Color, 1);
   }
   else
   {
        FragColor = vec4(Color1, 1);
   }

   FragColor *= grayScale;
}
