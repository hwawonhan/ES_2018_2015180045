#version 330

layout(location=0) out vec4 FragColor;

uniform vec4 u_Color;
in vec2 f_vec2;

void main()
{
    FragColor = u_Color;
    //float dis1 = length(f_vec2 - vec2(-1,0));
    //float dis2 = length(f_vec2 - vec2(1,0));
    //float gray1 = clamp(dis1, 0, 1);
    //float gray2 = clamp(dis2, 0, 1);
    //FragColor = vec4(1 - floor(gray1 * gray2));
}


 