#version 330

// f0 ---> {0,0,0,1} -----> f50 {0.5, 0,0,1} ----> f100 ==> {1,0,0,1}
layout(location=0) out vec4 FragColor;


in vec2 v_Color;
in float f_Time;

void main()
{
    //원
    //if ((v_Color.x*v_Color.x)+(v_Color.y*v_Color.y) < 0.25 && (v_Color.x*v_Color.x)+(v_Color.y*v_Color.y) > 0.25 - 0.01)
    //    FragColor = vec4(1);
    //else
    //    FragColor = vec4(1,0,0,0);
    //깜빡이며 움직이기
    //float center = (sin(f_Time) + 1.0) / 2.0;
    //if(v_Color.r > center - 0.1f && v_Color.r < center + 0.1f)
    //{
    //    FragColor = vec4(sin(f_Time), sin(f_Time), sin(f_Time), 1.0f);
    //}
    //else
    //{ 
    //    FragColor = vec4(0, 0, 0, 1);
    //}

    //퍼저나가는 원
    float r = length(v_Color) * 3.141592 * 4 - f_Time;
    float sinR = (sin(r) + 1)/2 * (1 - length(v_Color));
    FragColor = vec4(sinR);
}

 