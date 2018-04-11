#version 330

// f0 ---> {0,0,0,1} -----> f50 {0.5, 0,0,1} ----> f100 ==> {1,0,0,1}
layout(location=0) out vec4 FragColor;

in vec2 v_FragPos;

//uniform float u_Time;

void main()
{
   
   ////원만들기
    //if((v_Color.r * v_Color.r) + (v_Color.g * v_Color.g) < 0.25f && (v_Color.r * v_Color.r) + (v_Color.g * v_Color.g) > 0.25f - 0.01f )
    //{   
    //    FragColor = vec4(1, 1, 1, 1);
    //}
    //else
    //{
    //    FragColor = vec4(0, 0, 0, 1);
    //}

    //점선
    //float dotted = sin(v_Color.r * 2.0 * 3.141592 * 30);
    //FragColor = vec4(1, 1, 1, 1) * dotted;

    //깜빡이는거
    //float center = (sin(u_Time) + 1.0) / 2.0;
    //FragColor = vec4(sin(u_Time), sin(u_Time), sin(u_Time), 1.0f);


    //튕기는거
    //float center = (sin(u_Time) + 1.0) / 2.0;
    //if(v_Color.r > center - 0.1f && v_Color.r < center + 0.1f)
    //{
    //    FragColor = vec4(1, 1, 1, 1);
    //}
    //else
    //{ 
    //    FragColor = vec4(0, 0, 0, 1);
    //}

    //sin 그리기
    //float value = sin(v_FragPos.x * 3.141592);
    ////lecture5
    //if(value > v_FragPos.y)
    //    FragColor = vec4(1);
    //else
    //    FragColor = vec4(0);
    FragColor = vec4(1);

}
