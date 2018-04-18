#version 330

// f0 ---> {0,0,0,1} -----> f50 {0.5, 0,0,1} ----> f100 ==> {1,0,0,1}
layout(location=0) out vec4 FragColor;

uniform float u_Time;
uniform vec3 u_Points[4];

in vec2 v_Color;

void main()
{
    float finalColor = 0;

    for(int i = 0; i < 4; ++i)
    {
        vec2 segment = u_Points[i].xy - v_Color;
        float r = length(segment) * 3.141592 * u_Points[i].z - u_Time;
        float sinR = sin(r) * clamp((2 - length(segment)) * 0.5, 0, 1);
        sinR = pow(abs(sinR), 2);
        finalColor += sinR;
    }


   
    FragColor = vec4(finalColor, finalColor, finalColor, 1);
}


 