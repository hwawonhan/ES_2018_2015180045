#version 330

// f0 ---> {0,0,0,1} -----> f50 {0.5, 0,0,1} ----> f100 ==> {1,0,0,1}
layout(location=0) out vec4 FragColor;

uniform vec4 u_Color;

varying vec4 v_Color;

//uniform float u_Time;

void main()
{
    FragColor = v_Color;
    ////�������
    //if((v_Color.r * v_Color.r) + (v_Color.g * v_Color.g) < 0.25f && (v_Color.r * v_Color.r) + (v_Color.g * v_Color.g) > 0.25f - 0.01f )
    //{   
    //    FragColor = vec4(1, 1, 1, 1);
    //}
    //else
    //{
    //    FragColor = vec4(0, 0, 0, 1);
    //}

    //����
    //float dotted = sin(v_Color.r * 2.0 * 3.141592 * 30);
    //FragColor = vec4(1, 1, 1, 1) * dotted;

    //�����̴°�
    //float center = (sin(u_Time) + 1.0) / 2.0;
    //FragColor = vec4(sin(u_Time), sin(u_Time), sin(u_Time), 1.0f);


    //ƨ��°�
    //float center = (sin(u_Time) + 1.0) / 2.0;
    //if(v_Color.r > center - 0.1f && v_Color.r < center + 0.1f)
    //{
    //    FragColor = vec4(1, 1, 1, 1);
    //}
    //else
    //{ 
    //    FragColor = vec4(0, 0, 0, 1);
    //}
}
