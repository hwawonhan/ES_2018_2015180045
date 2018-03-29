#version 330

// f0 ---> {0,0,0,1} -----> f50 {0.5, 0,0,1} ----> f100 ==> {1,0,0,1}
layout(location=0) out vec4 FragColor;

uniform vec4 u_Color;

in vec4 v_Color;

uniform float u_Time;

void main()
{
    float center = (sin(u_Time) + 1.0) / 2.0;
    if(v_Color.r > center - 0.1f && v_Color.r < center + 0.1f)
    {
        FragColor = vec4(1, 1, 1, 1);
    }
    else
    { 
        FragColor = vec4(0, 0, 0, 1);
    }
}
